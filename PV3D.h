#ifndef	PV3D_H
#define PV3D_H

#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>

#include <GL/freeglut.h>
//#include <GL/glut.h>

#include <iostream>
using namespace std;

class PV3D {
private:
	GLfloat x, y, z;
	int pv; //0 vector | 1 punto

public:
	PV3D(GLfloat x, GLfloat y, GLfloat z, int pv);
	void normaliza();
	PV3D* clona();
	GLfloat productoEscalar(PV3D* v);
	PV3D* productoVectorial(PV3D* v);
	GLfloat getX();
	GLfloat getY();
	GLfloat getZ();
	void setX(GLfloat x);
	void setY(GLfloat y);
	void setZ(GLfloat z);


};


#endif