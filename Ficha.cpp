#include "Ficha.h"


/* Se compone de 6 quesitos */
Ficha::Ficha(int nQ, float z, float x, bool relleno, bool normales) : ObjetoCompuesto(6) {
	// Grados a rotar cada quesito para colocarlo
	int rot = 60;

	for (int i = 0; i < 6; i++) {
		hijos[i] = new Quesito(nQ, z, x);
		// Asignar el mismo color establecido a todos los quesitos
		hijos[i]->setColor(this->getColor());
		// Colocar el quesito en su sitio
		hijos[i]->getMTA()->rota(rot*i, new PV3D(0, 1, 0, 0));
	}

}
