#ifndef CAMARA_H
#define CAMARA_H

#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <GL/freeglut.h>
//#include <GL/glut.h>

#include "PV3D.h"


class Camara {
protected: 
	PV3D *eye, *look, *up, *u, *v, *n;
	GLdouble xRight, xLeft, yTop, yBot, N, F;
	int width, height;
	void setCamara();
	void matrizVista();
	void matrizProyec();
	float* matrizFrenet(float t, float *matriz);

public:
	Camara();
	~Camara();
	Camara(PV3D* eye, PV3D* look, PV3D* up);
	void recorridoEje(GLfloat x, GLfloat y, GLfloat z);
	void giraX();
	void giraY();
	void giraZ();
	void roll(int a);
	void yaw(int a);
	void pitch(int a);
	void lateral();
	void frontal();
	void cenital();
	void esquina();
	void ortogonal();
	void perspectiva();
	void circuito(GLfloat t);
	void lookAt(PV3D* p);

};

#endif