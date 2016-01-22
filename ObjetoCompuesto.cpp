#include "ObjetoCompuesto.h"

ObjetoCompuesto::ObjetoCompuesto(int numObjetos) {
	numHijos = numObjetos;
	hijos = new Objeto3D*[numHijos];

}

/* Dibuja cada objeto del objeto compuesto */
void ObjetoCompuesto::dibuja() {
	for (int i = 0; i < numHijos; i++) {
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glMultMatrixf(hijos[i]->getMTA()->getMatriz());
		hijos[i]->dibuja();
		glPopMatrix();
	}

}