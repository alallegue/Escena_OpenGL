#ifndef QUESITO_H
#define QUESITO_H

#include "Malla.h"

class Quesito : public Malla {
protected:
	int cortes; //nº veces en que se divide la parte circular
	GLfloat x, y; // radio y altura
	int pPerfil;
	int idxVertice; //indice del array de vertices a rellenar
	int idxCara;
	int idxNormal;
	void caraRedonda();
	void caraDelantera();
	void caraTrasera();
	void tapa();

public:
	Quesito();
	Quesito(int nQ, float x, float y);
	
};

#endif