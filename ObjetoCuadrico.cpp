#include "ObjetoCuadrico.h"


ObjetoCuadrico::ObjetoCuadrico() : Objeto3D() {
	q = gluNewQuadric();
	
}

void ObjetoCuadrico::dibuja() {}