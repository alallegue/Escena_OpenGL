#include "VerticeNormal.h"
	

VerticeNormal::VerticeNormal(int iVertice, int iNormal) {
	this->indiceVertice = iVertice;
	this->indiceNormal = iNormal;
}

int VerticeNormal::getIndiceVertice() {
	return this->indiceVertice;
}

int VerticeNormal::getIndiceNormal() {
	return this->indiceNormal;
}
