#ifndef ESCENA_H
#define ESCENA_H

#include "ObjetoCompuesto.h"
#include "PV3D.h"
#include "Tablero.h"
#include "Coche.h"
#include "Autopista.h"
#include "Farola.h"

/* Es un ObjetoCompuesto que tiene una lista de Objeto3D */
class Escena : public ObjetoCompuesto {
protected:
	PV3D* cochePos;
	Coche* coche;

public:
	Escena();
	PV3D* mueveCoche(float a);

};


#endif