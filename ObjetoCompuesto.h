#ifndef OBJETOCOMPUESTO_H
#define OBJETOCOMPUESTO_H

#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <GL/freeglut.h>
//#include <GL/glut.h>
#include "Objeto3D.h"

/* Se compone de uno o varios Objeto3D  y se encarga
	de mandar dibujar cada uno de ellos.
	Es a su vez un Objeto3D */
class ObjetoCompuesto : public Objeto3D {
protected:
	int numHijos;
	Objeto3D** hijos;

public:
	ObjetoCompuesto(int numObjetos);
	void dibuja();

};

#endif