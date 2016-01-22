#include "Cara.h"


Cara::Cara(int vertices, VerticeNormal** normales) {
	this->numVertices = vertices;
	this->arrayVN = normales;
}

int Cara::getNumeroVertices() {
	return this->numVertices;
}
int Cara::getIndiceNormalK(int i) {
	return this->arrayVN[i]->getIndiceNormal();
}
int Cara::getIndiceVerticeK(int i) {
	return this->arrayVN[i]->getIndiceVertice();
}

