#ifndef CILINDRO_H
#define CILINDRO_H

#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <GL/freeglut.h>
//#include <GL/glut.h>
#include "ObjetoCuadrico.h"
#include "Color.h"

class Cilindro : public ObjetoCuadrico {
protected:
	double baseR;
	double topR;
	double h;
	Color *c;

public:
	Cilindro(double radioBase, double radioTop, double altura);
	void dibuja();
};


#endif