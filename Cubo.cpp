#include "Cubo.h"

Cubo::Cubo() {
	relleno = true;
	construyeNewell();
}

Cubo::Cubo(bool relleno) : Malla(relleno){
	this->relleno = relleno;
	construyeNewell();
}

void Cubo::construyeManual() {
	float l = 1.0f;
	this->numVertices = 8;
	this->vertice = new PV3D*[this->numVertices];
	this->vertice[0] = new PV3D(l, l, l, 1);
	this->vertice[1] = new PV3D(l, l, -l, 1);
	this->vertice[2] = new PV3D(-l, l, -l, 1);
	this->vertice[3] = new PV3D(-l, l, l, 1);
	this->vertice[4] = new PV3D(l, -l, l, 1);
	this->vertice[5] = new PV3D(l, -l, -l, 1);
	this->vertice[6] = new PV3D(-l, -l, -l, 1);
	this->vertice[7] = new PV3D(-l, -l, l, 1);

	this->numNormales = 6;
	this->normal = new PV3D*[numNormales];
	this->normal[0] = new PV3D(1.0f, 0.0f, 0.0f, 0);	//Normal dcha frontal
	this->normal[1] = new PV3D(0.0f, 0.0f, -1.0f, 0);	//Normal dcha trasera
	this->normal[2] = new PV3D(-1.0f, 0.0f, 0.0f, 0);	//Normal izq trasera
	this->normal[3] = new PV3D(0.0f, 0.0f, 1.0f, 0);	//Normal izq frontal
	this->normal[4] = new PV3D(0.0f, -1.0f, 0.0f, 0);	//Normal inferior
	this->normal[5] = new PV3D(0.0f, 1.0f, 0.0f, 0);	//Normal superior

	VerticeNormal** arrayVN1 = new VerticeNormal*[4];	//Cara superior
	arrayVN1[0] = new VerticeNormal(2, 5);
	arrayVN1[1] = new VerticeNormal(3, 5);
	arrayVN1[2] = new VerticeNormal(0, 5);
	arrayVN1[3] = new VerticeNormal(1, 5);

	VerticeNormal** arrayVN2 = new VerticeNormal*[4];	//Cara inferior
	arrayVN2[0] = new VerticeNormal(6, 4);
	arrayVN2[1] = new VerticeNormal(5, 4);
	arrayVN2[2] = new VerticeNormal(4, 4);
	arrayVN2[3] = new VerticeNormal(7, 4);

	VerticeNormal** arrayVN3 = new VerticeNormal*[4];	//Cara dcha frontal
	arrayVN3[0] = new VerticeNormal(0, 0);
	arrayVN3[1] = new VerticeNormal(4, 0);
	arrayVN3[2] = new VerticeNormal(5, 0);
	arrayVN3[3] = new VerticeNormal(1, 0);

	VerticeNormal** arrayVN4 = new VerticeNormal*[4];	//Cara dcha trasera
	arrayVN4[0] = new VerticeNormal(6, 1);
	arrayVN4[1] = new VerticeNormal(5, 1);
	arrayVN4[2] = new VerticeNormal(1, 1);
	arrayVN4[3] = new VerticeNormal(2, 1);

	VerticeNormal** arrayVN5 = new VerticeNormal*[4];	//Cara izq trasera
	arrayVN5[0] = new VerticeNormal(7, 2);
	arrayVN5[1] = new VerticeNormal(6, 2);
	arrayVN5[2] = new VerticeNormal(2, 2);
	arrayVN5[3] = new VerticeNormal(3, 2);

	VerticeNormal** arrayVN6 = new VerticeNormal*[4];	//Cara izq frontal
	arrayVN6[0] = new VerticeNormal(4, 3);
	arrayVN6[1] = new VerticeNormal(0, 3);
	arrayVN6[2] = new VerticeNormal(3, 3);
	arrayVN6[3] = new VerticeNormal(7, 3);

	this->numCaras = 6;
	this->cara = new Cara*[this->numCaras];
	this->cara[0] = new Cara(4, arrayVN1);
	this->cara[1] = new Cara(4, arrayVN2);
	this->cara[2] = new Cara(4, arrayVN3);
	this->cara[3] = new Cara(4, arrayVN4);
	this->cara[4] = new Cara(4, arrayVN5);
	this->cara[5] = new Cara(4, arrayVN6);
}

void Cubo::construyeNewell() {
	float l = 1.0f;
	this->numVertices = 8;
	this->vertice = new PV3D*[this->numVertices];
	this->vertice[0] = new PV3D(l, l, l, 1);
	this->vertice[1] = new PV3D(l, l, -l, 1);
	this->vertice[2] = new PV3D(-l, l, -l, 1);
	this->vertice[3] = new PV3D(-l, l, l, 1);
	this->vertice[4] = new PV3D(l, -l, l, 1);
	this->vertice[5] = new PV3D(l, -l, -l, 1);
	this->vertice[6] = new PV3D(-l, -l, -l, 1);
	this->vertice[7] = new PV3D(-l, -l, l, 1);

	VerticeNormal** arrayVN1 = new VerticeNormal*[4];	//Cara superior
	arrayVN1[0] = new VerticeNormal(2, 5);
	arrayVN1[1] = new VerticeNormal(3, 5);
	arrayVN1[2] = new VerticeNormal(0, 5);
	arrayVN1[3] = new VerticeNormal(1, 5);

	VerticeNormal** arrayVN2 = new VerticeNormal*[4];	//Cara inferior
	arrayVN2[0] = new VerticeNormal(6, 4);
	arrayVN2[1] = new VerticeNormal(5, 4);
	arrayVN2[2] = new VerticeNormal(4, 4);
	arrayVN2[3] = new VerticeNormal(7, 4);

	VerticeNormal** arrayVN3 = new VerticeNormal*[4];	//Cara dcha frontal
	arrayVN3[0] = new VerticeNormal(0, 0);
	arrayVN3[1] = new VerticeNormal(4, 0);
	arrayVN3[2] = new VerticeNormal(5, 0);
	arrayVN3[3] = new VerticeNormal(1, 0);

	VerticeNormal** arrayVN4 = new VerticeNormal*[4];	//Cara dcha trasera
	arrayVN4[0] = new VerticeNormal(6, 1);
	arrayVN4[1] = new VerticeNormal(5, 1);
	arrayVN4[2] = new VerticeNormal(1, 1);
	arrayVN4[3] = new VerticeNormal(2, 1);

	VerticeNormal** arrayVN5 = new VerticeNormal*[4];	//Cara izq trasera
	arrayVN5[0] = new VerticeNormal(7, 2);
	arrayVN5[1] = new VerticeNormal(6, 2);
	arrayVN5[2] = new VerticeNormal(2, 2);
	arrayVN5[3] = new VerticeNormal(3, 2);

	VerticeNormal** arrayVN6 = new VerticeNormal*[4];	//Cara izq frontal
	arrayVN6[0] = new VerticeNormal(4, 3);
	arrayVN6[1] = new VerticeNormal(0, 3);
	arrayVN6[2] = new VerticeNormal(3, 3);
	arrayVN6[3] = new VerticeNormal(7, 3);

	this->numCaras = 6;
	this->cara = new Cara*[this->numCaras];
	this->cara[0] = new Cara(4, arrayVN1);
	this->cara[1] = new Cara(4, arrayVN2);
	this->cara[2] = new Cara(4, arrayVN3);
	this->cara[3] = new Cara(4, arrayVN4);
	this->cara[4] = new Cara(4, arrayVN5);
	this->cara[5] = new Cara(4, arrayVN6);

	this->numNormales = 6;
	this->normal = new PV3D*[numNormales];
	for (int i = 0; i < numCaras; i++) {
		PV3D* v = CalculoVectorNormalPorNewell(this->cara[i]);
		this->normal[i] = v;
	}

}
