#ifndef OBJETOCUADRICO_H
#define OBJETOCUADRICO_H

#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <GL/freeglut.h>
//#include <GL/glut.h>
#include "Objeto3D.h"

class ObjetoCuadrico : public Objeto3D {
protected:
	GLUquadricObj *q;

public:
	ObjetoCuadrico();
	void dibuja();

};


#endif