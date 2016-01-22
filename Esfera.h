#ifndef ESFERA_H
#define ESFERA_H

#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <GL/freeglut.h>
//#include <GL/glut.h>
#include "ObjetoCuadrico.h"

class Esfera : public ObjetoCuadrico {
protected:
	double r;

public:
	Esfera(double radio);
	void dibuja();
};


#endif