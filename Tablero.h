#ifndef TABLERO_H
#define TABLERO_H

#include "ObjetoCompuesto.h"
#include "Cubo.h"


class Tablero : public ObjetoCompuesto {
protected:
	int b, h, p;
	bool relleno;

public:
	Tablero(int base, int altura, int profundidad, bool relleno);

};

#endif