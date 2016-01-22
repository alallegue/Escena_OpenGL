#ifndef OBJETO3D_H
#define OBJETO3D_H

#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <GL/freeglut.h>
//#include <GL/glut.h>
#include "TAfin.h"
#include "Color.h"

class Objeto3D {
protected:
	TAfin* mT;
	Color* color;

public:
	Objeto3D();
	virtual void dibuja();
	TAfin* getMTA();
	Color* getColor();
	void setColor(Color* c);

};


#endif
