#include "Color.h"

Color::Color() {}

/* Constructor con un color inicial */
Color::Color(float red, float green, float blue) {
	r = red;
	g = green;
	b = blue;

}

/* Cambiar el color actual */
void Color::setColor(float red, float green, float blue) {
	r = red;
	g = green;
	b = blue;

}

/* Colorear el objeto con el color actualmente asignado */
void Color::colorea() {
	glColor3f(r, g, b);

}

