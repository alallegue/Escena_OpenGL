#include "Tablero.h"

/* Construye un tablero formado por base*altura*profundidad cubos */
Tablero::Tablero(int base, int altura, int profundidad, bool relleno) : ObjetoCompuesto(base*altura*profundidad) {
	this->relleno = relleno;
	b = base;
	h = altura;
	p = profundidad;

	int n = 0;
	for (int i = 0; i < h; i++) { //Y
		for (int j = 0; j < p; j++) { //Z
			for (int k = 0; k < b; k++) { //X
				hijos[n] = new Cubo(relleno);
				hijos[n]->setColor(this->getColor());
				hijos[n]->getMTA()->traslada(new PV3D(2*k, 2*i, -2*j, 0));
				n++;
			}
		}
	}

}
