#include "Objeto3D.h"

Objeto3D::Objeto3D() {
	// Inicializar matriz de transformación afin
	mT = new TAfin();
	// Inicializar un color por defecto (verde)
	color = new Color(0, 1, 0);
}

TAfin* Objeto3D::getMTA() {
	return mT;
}

void Objeto3D::dibuja() {}

Color* Objeto3D::getColor() {
	return color;
}

void Objeto3D::setColor(Color* c) {
	this->color = c;
}