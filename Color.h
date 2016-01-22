#ifndef COLOR_H
#define COLOR_H


#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <GL/freeglut.h>
//#include <GL/glut.h>


class Color {
protected:
	float r, g, b;

public:
	Color();
	Color(float red, float green, float blue);
	void setColor(float red, float green, float blue);
	void setColor(Color c);
	void colorea();
	
};

#endif