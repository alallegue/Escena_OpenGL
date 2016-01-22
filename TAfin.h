#ifndef TAFIN_H
#define TAFIN_H

#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <GL/freeglut.h>
//#include <GL/glut.h>
#include "PV3D.h"


class TAfin {
protected:
	GLfloat matriz[16];

public:
	TAfin();
	void traslada(PV3D* v);
	void rota(float a, PV3D* v);
	void escala(PV3D* v);
	void postMultiplica(GLfloat* m);
	GLfloat* getMatriz();

};


#endif