#ifndef CARA_H
#define CARA_H

#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <GL/freeglut.h>
//#include <GL/glut.h>

#include "VerticeNormal.h"
#include <iostream>
using namespace std;


class Cara {
private:
	int numVertices;
	VerticeNormal** arrayVN;
	
public:
	Cara(int vertices, VerticeNormal** normales);
	int getNumeroVertices();
	int getIndiceNormalK(int i);
	int getIndiceVerticeK(int i);
};

#endif