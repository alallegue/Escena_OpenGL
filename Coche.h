#ifndef COCHE_H
#define COCHE_H

#include "ObjetoCompuesto.h"
#include "Cubo.h"
#include "Ficha.h"
//Faros...

/* Compuesto por un cubo como chasis y 4 fichas como ruedas */
class Coche : public ObjetoCompuesto {
public:
	Coche();
	void giraRuedas(double a);

};

#endif