#include "Cilindro.h"

Cilindro::Cilindro(double radioBase, double radioTop, double altura) {
	baseR = radioBase;
	topR = radioTop;
	h = altura;
	gluQuadricDrawStyle(q, GLU_FILL);
}

void Cilindro::dibuja() {
	color->colorea();
	gluCylinder(q, baseR, topR, h, 10, 10);

}
