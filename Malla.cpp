#include "Malla.h"

Malla::Malla() {
	relleno = true;
}

Malla::Malla(bool relleno) {
	relleno = relleno;
}

Malla::Malla(int nVertices, PV3D** vertices, int nNormales, PV3D** normales, int nCaras, Cara** caras) : Objeto3D() {
	this->numVertices = nVertices;
	this->vertice = vertices;
	this->numNormales = nNormales;
	this->normal = normales;
	this->numCaras = nCaras;
	this->cara = caras;
	relleno = true;
}

void Malla::dibuja() {
	for (int i = 0; i < numCaras; i++) {
		glLineWidth(1.0);
		if (relleno) glBegin(GL_POLYGON); //o glBegin(GL_LINE_LOOP);
		else glBegin(GL_LINE_LOOP);
		// Aplicar el color asignado al Objeto3D
		color->colorea();
		for (int j = 0; j < cara[i]->getNumeroVertices(); j++) {
			int iN = cara[i]->getIndiceNormalK(j);
			int iV = cara[i]->getIndiceVerticeK(j);
			glNormal3f(normal[iN]->getX(), normal[iN]->getY(), normal[iN]->getZ());
			//Si hubiera coordenadas de textura, aquí se suministrarían
			//las coordenadas de textura del vértice j con glTexCoor2f(…);
			glVertex3f(vertice[iV]->getX(), vertice[iV]->getY(), vertice[iV]->getZ());
		}
		glEnd();
	}
}

/*
Dibuja el vector normal de cada cara de la malla
*/
void Malla::dibujaNormales() {
	int l = 2;
	for (int i = 0; i < numCaras; i++) {
		int vertcara = cara[i]->getNumeroVertices();
		GLfloat vx = 0, vy = 0, vz = 0;

		for (int j = 0; j < vertcara; j++) {
			int idV = cara[i]->getIndiceVerticeK(j);
			GLfloat x = vx + vertice[idV]->getX();
			GLfloat y = vy + vertice[idV]->getY();
			GLfloat z = vz + vertice[idV]->getZ();
			vx = x;
			vy = y;
			vz = z;
		}
		vx /= vertcara;
		vy /= vertcara;
		vz /= vertcara;
		glBegin(GL_LINES);
		glColor3f(0.0, 0.5, 1.0);
		glVertex3f(vx, vy, vz);
		glVertex3f(vx + (l*normal[i]->getX()), vy + (l*normal[i]->getY()), vz + (l*normal[i]->getZ()));
		glEnd();
	}

}

/*
Calcula el vector normal de una cara respecto a los vértices de la malla
*/
PV3D* Malla::CalculoVectorNormalPorNewell(Cara* c) {
	PV3D* n = new PV3D(0, 0, 0, 0);
	for (int i = 0; i < c->getNumeroVertices(); i++) {
		PV3D* vertActual = this->vertice[c->getIndiceVerticeK(i)];
		PV3D* vertSiguiente = this->vertice[c->getIndiceVerticeK((i + 1) % c->getNumeroVertices())];
		GLfloat x = n->getX() + ((vertActual->getY() - vertSiguiente->getY()) * (vertActual->getZ() + vertSiguiente->getZ()));
		GLfloat y = n->getY() + ((vertActual->getZ() - vertSiguiente->getZ()) * (vertActual->getX() + vertSiguiente->getX()));
		GLfloat z = n->getZ() + ((vertActual->getX() - vertSiguiente->getX()) * (vertActual->getY() + vertSiguiente->getY()));
		n->setX(x);
		n->setY(y);
		n->setZ(z);
	}

	n->normaliza();
	return n;
}

