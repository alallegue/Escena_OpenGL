#include "Esfera.h"


Esfera::Esfera(double radio) {
	r = radio;
	gluQuadricDrawStyle(q, GLU_FILL);
}

void  Esfera::dibuja() {
	color->colorea();
	gluSphere(q, r, 20, 20);

}