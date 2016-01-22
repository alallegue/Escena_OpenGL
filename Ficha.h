#ifndef FICHA_H
#define FICHA_H

#include "ObjetoCompuesto.h"
#include "Quesito.h"

class Ficha : public ObjetoCompuesto {
protected:
	int nQ; //nº veces en que se divide la parte circular
	float z, x; // radio y altura
	bool relleno;
	bool normales;

public:
	Ficha(int nQ, float z, float x, bool relleno, bool normales);

};

#endif