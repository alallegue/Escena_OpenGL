#include "Escena.h"


/* Se compone de un tablero, una autopista, dos farolas y un coche.
	El tablero sirve como base de la escena para poder apreciar
	el movimiento del coche y que el resto de elementos queden ubicados y no flotando. 
	El coche se puede mover por teclado y la cámara sigue su movimiento. */
Escena::Escena():ObjetoCompuesto(5) {
	int n = 0;
	hijos[n] = new Tablero(30, 1, 16, false);
	hijos[n]->getColor()->setColor(0, 0, 0);
	hijos[n]->getMTA()->traslada(new PV3D(-20, 0, 16, 0));
	hijos[n]->getMTA()->escala(new PV3D(1, 0.001, 1, 0));
	n++;
	hijos[n] = new Autopista(30, 1, 3);
	hijos[n]->getMTA()->traslada(new PV3D(-20, 0, 5, 0));
	n++;
	hijos[n] = new Farola();
	hijos[n]->getMTA()->traslada(new PV3D(0, 0, 3, 0));
	n++;
	hijos[n] = new Farola();
	hijos[n]->getMTA()->traslada(new PV3D(20, 0, 3, 0));
	n++;
	coche = new Coche();
	hijos[n] = coche;
	cochePos = new PV3D(1, 1.6, -2, 0);
	hijos[n]->getMTA()->traslada(cochePos);

}

PV3D* Escena::mueveCoche(float a) {
	// Mover el coche
	coche->getMTA()->traslada(new PV3D(a, 0, 0, 0));
	// Actualizar la posición del coche para que lo siga la cámara
	float np = cochePos->getX() + a;
	cochePos->setX(np);
	// Girar las ruedas del coche
	coche->giraRuedas(-a * 50);
	return cochePos->clona();
}
