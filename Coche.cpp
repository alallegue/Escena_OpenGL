#include "Coche.h"

Coche::Coche() : ObjetoCompuesto(5) {
	int n = 0;
	hijos[n] = new Cubo();
	hijos[n]->getColor()->setColor(1, 0, 0);
	n++;
	hijos[n] = new Ficha(20, 0.5, 0.5, true, false);
	hijos[n]->getColor()->setColor(0.3, 0.3, 0.3);
	hijos[n]->getMTA()->traslada(new PV3D(-0.8, -1, 1, 0));
	hijos[n]->getMTA()->rota(90, new PV3D(1, 0, 0, 0));
	n++;
	hijos[n] = new Ficha(20, 0.5, 0.5, true, false);
	hijos[n]->getColor()->setColor(0.3, 0.3, 0.3);
	hijos[n]->getMTA()->traslada(new PV3D(0.8, -1, 1, 0));
	hijos[n]->getMTA()->rota(90, new PV3D(1, 0, 0, 0));
	n++;
	hijos[n] = new Ficha(20, 0.5, 0.5, true, false);
	hijos[n]->getColor()->setColor(0.3, 0.3, 0.3);
	hijos[n]->getMTA()->traslada(new PV3D(-0.8, -1, -1, 0));
	hijos[n]->getMTA()->rota(-90, new PV3D(1, 0, 0, 0));
	n++;
	hijos[n] = new Ficha(20, 0.5, 0.5, true, false);
	hijos[n]->getColor()->setColor(0.3, 0.3, 0.3);
	hijos[n]->getMTA()->traslada(new PV3D(0.8, -1, -1, 0));
	hijos[n]->getMTA()->rota(-90, new PV3D(1, 0, 0, 0));
	n++;

}

/* Gira todas las ruedas del coche un ángulo 'a' */
void Coche::giraRuedas(double a) {
	hijos[1]->getMTA()->rota(a, new PV3D(0, 1, 0, 0));
	hijos[2]->getMTA()->rota(a, new PV3D(0, 1, 0, 0));
	hijos[3]->getMTA()->rota(-a, new PV3D(0, 1, 0, 0));
	hijos[4]->getMTA()->rota(-a, new PV3D(0, 1, 0, 0));

}