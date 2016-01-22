#ifndef MALLA_H
#define MALLA_H

#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <GL/freeglut.h>
//#include <GL/glut.h>
#include "PV3D.h"
#include "Cara.h"
#include <iostream>
#include "Objeto3D.h"

using namespace std;


class Malla : public Objeto3D {
protected:
	int numVertices;
	PV3D** vertice;
	int numNormales; //=numCaras, frecuentemente
	PV3D** normal;
	int numCaras;
	Cara** cara;
	bool relleno;

public:
	Malla();
	Malla(bool relleno);
	Malla(int nVertices, PV3D** vertices, int nNormales, PV3D** normales, int nCaras, Cara** caras);
	void dibuja();
	void dibujaNormales();
	PV3D* CalculoVectorNormalPorNewell(Cara* c);

};

#endif