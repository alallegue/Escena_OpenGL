#include "Autopista.h"

/* Se compone de dos tableros de b*h*p cubos aplastados para tener poco grosor*/
Autopista::Autopista(int b, int h, int p) : ObjetoCompuesto(2) {
	hijos[0] = new Tablero(b, h, p, true);
	hijos[0]->getColor()->setColor(0.2, 0.2, 0.2);
	hijos[0]->getMTA()->traslada(new PV3D(0, 0, -2*p, 0));
	hijos[0]->getMTA()->escala(new PV3D(1, 0.1, 1, 0));
	hijos[1] = new Tablero(b, h, p, true);
	hijos[1]->getColor()->setColor(0.2, 0.2, 0.2);
	hijos[1]->getMTA()->traslada(new PV3D(0, 0, 2*p, 0));
	hijos[1]->getMTA()->escala(new PV3D(1, 0.1, 1, 0));

}