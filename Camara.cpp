#define _USE_MATH_DEFINES

#include "Camara.h"
#include <math.h>

Camara::Camara() {
	eye = new PV3D(100.0, 100.0, 100.0, 1);
	look = new PV3D(0.0, 0.0, 0.0, 1);
	up = new PV3D(0, 1, 0, 0);
}

Camara::~Camara() {}

Camara::Camara(PV3D* eye, PV3D* look, PV3D* up) {
	//Inicializar parámetros de cámara
	this->eye = eye;	//posición del ojo
	this->look = look;	//dónde mira
	this->up = up;		//inclinación

	//Definir la matriz de vista
	setCamara();

	//Inicializar las dimensiones del volumen de vista
	xRight = 10, xLeft = -xRight, yTop = 10, yBot = -yTop, N = 1, F = 1000;

	//Definir la matriz de proyección
	matrizProyec();

}

/*Definir la cámara
Determinar el sistema de coordenadas de la cámara */
void Camara::setCamara(){
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(eye->getX(), eye->getY(), eye->getZ(), look->getX(), look->getY(), look->getZ(), up->getX(), up->getY(), up->getZ());

	u = new PV3D(0, 0, 0, 0);
	v = new PV3D(0, 0, 0, 0);
	n = new PV3D(0, 0, 0, 0);

	n->setX(eye->getX() - look->getX());
	n->setY(eye->getY() - look->getY());
	n->setZ(eye->getZ() - look->getZ());
	n->normaliza();

	GLfloat ux = up->productoVectorial(n)->getX();
	GLfloat uy = up->productoVectorial(n)->getY();
	GLfloat uz = up->productoVectorial(n)->getZ();
	u->setX(ux);
	u->setY(uy);
	u->setZ(uz);
	u->normaliza();

	v->setX(n->productoVectorial(u)->getX());
	v->setY(n->productoVectorial(u)->getY());
	v->setZ(n->productoVectorial(u)->getZ());

	matrizVista();
}

/*Matriz de coordenadas globales a coordenadas de cámara*/
void Camara::matrizVista(){
	GLfloat m[16];
	PV3D ev(eye->getX(), eye->getY(), eye->getZ(), 0);
	m[0] = u->getX();
	m[1] = v->getX();
	m[2] = n->getX();
	m[3] = 0;
	m[4] = u->getY();
	m[5] = v->getY();
	m[6] = n->getY();
	m[7] = 0;
	m[8] = u->getZ();
	m[9] = v->getZ();
	m[10] = n->getZ();
	m[11] = 0;
	m[12] = -ev.productoEscalar(u);
	m[13] = -ev.productoEscalar(v);
	m[14] = -ev.productoEscalar(n);
	m[15] = 1.0;

	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(m);
}

/*Matriz de proyección*/
void Camara::matrizProyec(){
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(xLeft, xRight, yBot, yTop, N, F);
}

/*Mueve la cámara a lo largo de los ejes*/
void Camara::recorridoEje(GLfloat x, GLfloat y, GLfloat z) {
	GLfloat nx = eye->getX() + x;
	GLfloat ny = eye->getY() + y;
	GLfloat nz = eye->getZ() + z;

	eye->setX(nx);
	eye->setY(ny);
	eye->setZ(nz);

	setCamara();
}

/*Rota la cámara alrededor del eje X con un movimiento circular*/
void Camara::giraX() {
	GLfloat r = std::sqrt(std::pow(eye->getY(), 2) + std::pow(eye->getZ(), 2));
	GLfloat a = std::atan2(eye->getY(), eye->getZ()) - 0.1;
	eye->setY(r * sin(a));
	eye->setZ(r * cos(a));
	setCamara();
}

/*Rota la cámara alrededor del eje Y con un movimiento circular*/
void Camara::giraY() {
	GLfloat r = std::sqrt(std::pow(eye->getX(), 2) + std::pow(eye->getZ(), 2));
	GLfloat a = std::atan2(eye->getX(), eye->getZ()) - 0.1;
	eye->setX(r * sin(a));
	eye->setZ(r * cos(a));
	setCamara();
}

/*Rota la cámara alrededor del eje Z con un movimiento circular*/
void Camara::giraZ() {
	GLfloat r = std::sqrt(std::pow(eye->getX(), 2) + std::pow(eye->getY(), 2));
	GLfloat a = std::atan2(eye->getX(), eye->getY()) - 0.1;
	eye->setX(r * sin(a));
	eye->setY(r * cos(a));
	setCamara();
}

/*Movimiento de cámara roll*/
void Camara::roll(int a) {
	GLfloat ra = a * M_PI / 180;
	GLfloat c = cos(ra);
	GLfloat s = sin(ra);
	PV3D *uP = u->clona();
	PV3D *vP = v->clona();

	u->setX(c*uP->getX() + s*vP->getX());
	u->setY(c*uP->getY() + s*vP->getY());
	u->setZ(c*uP->getZ() + s*vP->getZ());
	v->setX(-s*uP->getX() + c*vP->getX());
	v->setY(-s*uP->getY() + c*vP->getY());
	v->setZ(-s*uP->getZ() + c*vP->getZ());

	//Actualizar sólo la matriz de vista
	matrizVista();
}

/*Movimiento de cámara yaw*/
void Camara::yaw(int a) {
	GLfloat ra = a * M_PI / 180;
	GLfloat c = cos(ra);
	GLfloat s = sin(ra);
	PV3D *uP = u->clona();
	PV3D *nP = n->clona();

	u->setX(c*uP->getX() - s*nP->getX());
	u->setY(c*uP->getY() - s*nP->getY());
	u->setZ(c*uP->getZ() - s*nP->getZ());

	n->setX(s*uP->getX() + c*nP->getX());
	n->setY(s*uP->getY() + c*nP->getY());
	n->setZ(s*uP->getZ() + c*nP->getZ());

	//Actualizar sólo la matriz de vista
	matrizVista();
}

/*Movimiento de cámara pitch*/
void Camara::pitch(int a) {
	GLfloat ra = a * M_PI / 180;
	GLfloat c = cos(ra);
	GLfloat s = sin(ra);
	PV3D *vP = v->clona();
	PV3D *nP = n->clona();

	v->setX(c*vP->getX() + s*nP->getX());
	v->setY(c*vP->getY() + s*nP->getY());
	v->setZ(c*vP->getZ() + s*nP->getZ());

	n->setX(-s*vP->getX() + c*nP->getX());
	n->setY(-s*vP->getY() + c*nP->getY());
	n->setZ(-s*vP->getZ() + c*nP->getZ());

	//Actualizar sólo la matriz de vista
	matrizVista();
}

/*Muestra la escena desde el lado derecho*/
void Camara::lateral() {
	eye->setX(200);
	eye->setY(0);
	eye->setZ(0);
	setCamara();
}

/*Muestra la escena desde el lado izquierdo*/
void Camara::frontal() {
	eye->setX(0);
	eye->setY(0);
	eye->setZ(200);
	setCamara();
}

/*Muestra la escena desde arriba*/
void Camara::cenital() {
	eye->setX(0);
	eye->setY(200);
	eye->setZ(0);
	//Cambiar la inclinación de la cámara
	up->setX(1);
	up->setY(0);
	up->setZ(0);
	setCamara();
	//Recuperar la inclinación
	up->setX(0);
	up->setY(1);
	up->setZ(0);
}

/*Muestra la escena desde un punto opuesto al rincón*/
void Camara::esquina() {
	eye->setX(200);
	eye->setY(200);
	eye->setZ(200);
	setCamara();
}

/*Muestra la escena en modo ortogonal*/
void Camara::ortogonal() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(xLeft, xRight, yBot, yTop, N, F);

}

/*Muestra la escena en modo perspectiva*/
void Camara::perspectiva() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(xLeft, xRight, yBot, yTop, N, F);
	gluPerspective(45, 1.33, N, F);
}

/**/
float* Camara::matrizFrenet(float t, float *matriz) {
	//Derivadas calculadas en papel
	PV3D* C = new PV3D(3 * cos(t), 3 * sin(2 * t), 3 * sin(t), 1);
	PV3D* Cp = new PV3D((-3) * sin(t), 6 * cos(2 * t), 3 * cos(t), 1);
	PV3D* Cs = new PV3D((-3) * cos(t), (-12)*sin(2 * t), (-3)*sin(t), 1);
	//Componentes de la matriz
	PV3D* T = Cp->clona();
	T->normaliza();
	PV3D* B = Cp->productoVectorial(Cs);
	B->normaliza();
	PV3D* N = B->productoVectorial(T);
	//Rellenar la matriz
	matriz[0] = N->getX();
	matriz[1] = N->getY();
	matriz[2] = N->getZ();
	matriz[3] = 0.0;
	matriz[4] = B->getX();
	matriz[5] = B->getY();
	matriz[6] = B->getZ();
	matriz[7] = 0.0;
	matriz[8] = T->getX();
	matriz[9] = T->getY();
	matriz[10] = T->getZ();
	matriz[11] = 0.0;
	matriz[12] = C->getX();
	matriz[13] = C->getY();
	matriz[14] = C->getZ();
	matriz[15] = 1.0;

	return matriz;
}


//Construcción del circuito y del coche que lo recorre
void Camara::circuito(GLfloat t) {
	float matriz[16];
	matrizFrenet(t, matriz);

	eye->setX(200);
	eye->setY(0);
	eye->setZ(0);
	setCamara();
	
	/*
	glMatrixMode(GL_MODELVIEW);
	glColor3f(0.6, 0.4, 0.2);
	glPushMatrix();
	matrizVista();
	glMultMatrixf(matriz);
	

	//Rotar 90º sobre el eje Y y sobre el eje X
	//glRotatef(90, 0, 1, 0);
	//glRotatef(90, 1, 0, 0);
	//Cambiar el coche a un tamaño menor
	//glScaled(0.5, 0.5, 0.5);
	
	glPopMatrix();
	*/
}

/* Apuntar la cámara al punto p */
void Camara::lookAt(PV3D* p) {
	look->setX(p->getX());
	look->setY(p->getY());
	look->setZ(p->getZ());

	setCamara();
}

