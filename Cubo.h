#ifndef CUBO_H
#define CUBO_H

#include "Malla.h"

class Cubo : public Malla {
public:
	Cubo();
	Cubo(bool r);

private:
	void construyeManual();
	void construyeNewell();
};

#endif