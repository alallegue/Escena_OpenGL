#include "PV3D.h"


PV3D::PV3D(GLfloat x, GLfloat y, GLfloat z, int pv) {
	this->x = x;
	this->y = y;
	this->z = z;
	this->pv = pv; //0 vector | 1 punto
}

void PV3D::normaliza() {
	GLfloat mod = sqrt(x*x + y*y + z*z);
	this->x = x / mod;
	this->y = y / mod;
	this->z = z / mod;
}

PV3D* PV3D::clona() {
	return new PV3D(this->x, this->y, this->z, this->pv);
}

GLfloat PV3D::productoEscalar(PV3D* v) {
	return (this->x * v->getX()) + (this->y * v->getY()) + (this->z * v->getZ());
}

PV3D* PV3D::productoVectorial(PV3D* v) {
	GLfloat i = (this->y * v->getZ()) - (this->z * v->getY());
	GLfloat j = (this->z * v->getX()) - (this->x * v->getZ());
	GLfloat k = (this->x * v->getY()) - (this->y * v->getX());

	return new PV3D(i, j, k, 0);
}	
	
GLfloat PV3D::getX() {
	return x;
}

GLfloat PV3D::getY() {
	return y;
}

GLfloat PV3D::getZ() {
	return z;
}

void PV3D::setX(GLfloat x) {
	this->x = x;
}

void PV3D::setY(GLfloat y) {
	this->y = y;
}

void PV3D::setZ(GLfloat z) {
	this->z = z;
}


