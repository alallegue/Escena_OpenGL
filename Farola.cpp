#include "Farola.h"

/* Se compone de un cilindro y una esfera */
Farola::Farola() : ObjetoCompuesto(2) {
	hijos[0] = new Cilindro(0.2, 0.2, 7);
	hijos[0]->getColor()->setColor(0, 1, 0);
	hijos[0]->getMTA()->rota(-90, new PV3D(1, 0, 0, 0));
	hijos[1] = new Esfera(0.8);
	hijos[1]->getColor()->setColor(1, 1, 0);
	hijos[1]->getMTA()->traslada(new PV3D(0, 7, 0, 0));

}