#include "TAfin.h"

/* Inicializa la matriz de transformación afin*/
TAfin::TAfin() {
	for (int i = 0; i < 16; i++){
		matriz[i] = 0;
	}
	matriz[0] = 1;
	matriz[5] = 1;
	matriz[10] = 1;
	matriz[15] = 1;

}

/* Aplicar una traslación a la matriz de transformación afin*/
void TAfin::traslada(PV3D* v) {
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glTranslatef(v->getX(), v->getY(), v->getZ());
	GLfloat m1[16];
	glGetFloatv(GL_MODELVIEW_MATRIX, m1);
	glPopMatrix();
	postMultiplica(m1);
}

/* Aplicar una rotación a la matriz de transformación afin*/
void TAfin::rota(float a, PV3D* v) {
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glRotatef(a, v->getX(), v->getY(), v->getZ());
	GLfloat m1[16];
	glGetFloatv(GL_MODELVIEW_MATRIX, m1);
	glPopMatrix();
	postMultiplica(m1);
}

/* Aplicar una escalación a la matriz de transformación afin*/
void TAfin::escala(PV3D* v){
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glScalef(v->getX(), v->getY(), v->getZ());
	GLfloat m1[16];
	glGetFloatv(GL_MODELVIEW_MATRIX, m1);
	glPopMatrix();
	postMultiplica(m1);
}

/* Postmultiplicar la matriz de transformación afin por otra matriz*/
void TAfin::postMultiplica(GLfloat* m1) {
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadMatrixf(matriz);
	glMultMatrixf(m1);
	glGetFloatv(GL_MODELVIEW_MATRIX, matriz);
	glPopMatrix();

}

/* Obtener la matriz de transformación afin*/
GLfloat* TAfin::getMatriz() {
	return matriz;
}
