#define _USE_MATH_DEFINES

#include "Quesito.h"
#include <math.h>


//Constructor por defecto
Quesito::Quesito(){}

//Constructor con parámetros
Quesito::Quesito(int nQ, float z, float x) {
	this->cortes = nQ; //capas
	this->x = z; //radio
	this->y = x; //altura
	this->idxVertice = 0;
	this->idxCara = 0;
	this->idxNormal = 0;
	this->pPerfil = 2; //nº puntos del perfil

	this->numVertices = (cortes * pPerfil) + 2; // cortes * puntosPerfil + 2 vertices especiales
	this->numCaras = cortes + 2; //(cortes - 1) + 3 (dos caras y una tapa) 
	this->numNormales = numCaras;

	//creación de los arrays
	this->vertice = new PV3D*[numVertices];
	this->normal = new PV3D*[numNormales];
	this->cara = new Cara*[numCaras];

	caraRedonda();

	//Vértices especiales en el eje Y
	vertice[idxVertice] = new PV3D(0, 0, 0, 1);
	idxVertice++;
	vertice[idxVertice] = new PV3D(0, y, 0, 1);

	caraDelantera();
	caraTrasera();
	tapa();

}

void Quesito::caraRedonda() {
	/*	Construcción del lateral redondo */
	PV3D** perfil = new PV3D*[pPerfil]; //perfil en XY
	//Construir perfil
	perfil[0] = new PV3D(x, 0.0f, 0.0f, 1);
	perfil[1] = new PV3D(x, y, 0.0f, 1);

	//Colocar el perfil original en la tabla de vertices
	for (int j = 0; j < pPerfil; j++) {
		vertice[idxVertice] = perfil[j]->clona();
		idxVertice++;
	}

	//Construcción de los vértices
	for (int i = 1; i < cortes; i++) {
		//59 grados por pieza
		double rads = 60 * M_PI / 180;
		double theta = i * rads / (double)cortes; //Pasar grados a radianes
		double c = cos(theta);
		double s = sin(theta);
		//R_y es la matriz de rotación sobre el eje Y
		for (int j = 0; j < pPerfil; j++) {
			//Transformar el punto j-ésimo del perfil original
			double x = c * perfil[j]->getX() + s * perfil[j]->getZ();
			double z = ((-s) * perfil[j]->getX()) + c * perfil[j]->getZ();
			PV3D* p = new PV3D(x, perfil[j]->getY(), z, 1);
			vertice[idxVertice] = p;
			idxVertice++;
		}
	}

	//Construcción de las caras y las normales
	int verticesR = cortes * pPerfil;
	for (int i = 0; i < cortes - 1; i++) {
		for (int j = 0; j < pPerfil - 1; j++) {
			int indice = (i * pPerfil) + j;
			VerticeNormal** vn = new VerticeNormal*[4];
			vn[0] = new VerticeNormal(indice, idxNormal);
			vn[1] = new VerticeNormal((indice + pPerfil) % verticesR, idxNormal);
			vn[2] = new VerticeNormal((indice + 1 + pPerfil) % verticesR, idxNormal);
			vn[3] = new VerticeNormal(indice + 1, idxNormal);
			this->cara[idxCara] = new Cara(4, vn);
			PV3D* v = CalculoVectorNormalPorNewell(this->cara[idxCara]);
			this->normal[idxNormal] = v;

			idxCara++;
			idxNormal++;
		}
	}

}

void Quesito::caraDelantera() {
	//Construcción de la cara delantera
	VerticeNormal** vn = new VerticeNormal*[4];
	vn[0] = new VerticeNormal(idxVertice, idxNormal);
	vn[1] = new VerticeNormal(idxVertice - 1, idxNormal);
	vn[2] = new VerticeNormal(0, idxNormal);
	vn[3] = new VerticeNormal(1, idxNormal);

	cara[idxCara] = new Cara(4, vn);
	PV3D* v = CalculoVectorNormalPorNewell(cara[idxCara]);
	normal[idxNormal] = v;
	idxCara++;
	idxNormal++;

}

/*
Construcción de la cara trasera a partir de los últimos
vertices calculados en la revolución
*/
void Quesito::caraTrasera() {
	VerticeNormal** vn = new VerticeNormal*[4];
	vn[0] = new VerticeNormal(idxVertice - 2, idxNormal);
	vn[1] = new VerticeNormal(idxVertice - 3, idxNormal);
	vn[2] = new VerticeNormal(idxVertice - 1, idxNormal);
	vn[3] = new VerticeNormal(idxVertice, idxNormal);

	cara[idxCara] = new Cara(4, vn);
	PV3D* v = CalculoVectorNormalPorNewell(cara[idxCara]);
	normal[idxNormal] = v;
	idxCara++;
	idxNormal++;

}

void Quesito::tapa() {
	//Construcción de la tapa
	VerticeNormal** vn = new VerticeNormal*[cortes + 1];
	//El primer vértice es el vértice especial superior
	vn[0] = new VerticeNormal(idxVertice, idxNormal);
	for (int i = 0; i < cortes; i++) {
		vn[i + 1] = new VerticeNormal(2 * i + 1, idxNormal);
	}
	
	cara[idxCara] = new Cara(cortes + 1, vn);
	PV3D* v = CalculoVectorNormalPorNewell(cara[idxCara]);
	normal[idxNormal] = v;
	idxCara++;
	idxNormal++;

}

