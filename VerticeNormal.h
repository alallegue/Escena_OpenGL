#ifndef VERTICENORMAL_H
#define VERTICENORMAL_H

#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>

#include <GL/freeglut.h>
//#include <GL/glut.h>

#include <iostream>
using namespace std;


class VerticeNormal {
private:
	int indiceVertice, indiceNormal;

public: 
	VerticeNormal(int iVertice, int iNormal);
	int getIndiceVertice();
	int getIndiceNormal();
};

#endif;