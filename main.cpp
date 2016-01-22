#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>

#include <GL/freeglut.h>
#include <GL/glut.h>

#include "Camara.h"
#include "Escena.h"

#include <iostream>
using namespace std;

// Freeglut parameters
// Flag telling us to keep processing events
// bool continue_in_main_loop= true; //(**)

// Viewport size
int WIDTH = 500, HEIGHT = 500;

// Viewing frustum parameters
GLdouble xRight = 10, xLeft = -xRight, yTop = 10, yBot = -yTop, N = 1, F = 1000;

//Parámetros de rotación
GLfloat ROTACION = 2;
GLfloat RZ = 0.5f; //Variable para cambiar la rotación de las figuras
GLfloat RY = 0.0f;
GLfloat RX = 0.0f;
bool RELLENO = true;
bool NORM = false;

//Parámetros de escena
GLdouble incrX = 0.5, incrY = 0.5;
bool EMBALDOSAR = false;
int NCOL = 2;
bool ORTOGONAL = true;

// Parametros desembaldosado
int pWIDTH = WIDTH, pHEIGHT = HEIGHT;
GLdouble pxRight = xRight, pxLeft = xLeft, pyTop = yTop, pyBot = yBot, pN = N, pF = F;


//Objetos de la escena
Camara *camara;
Escena *escena;



void buildSceneObjects() {
	escena = new Escena();
	camara = new Camara(new PV3D(100.0, 100.0, 100.0, 1), new PV3D(0.0, 0.0, 0.0, 1), new PV3D(0, 1, 0, 0));

}

void dibujaEjes() {
	// Drawing axes
	glBegin(GL_LINES);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(0, 0, 0);
	glVertex3f(20, 0, 0);

	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 20, 0);

	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 20);
	glEnd();
}

void drawScene() {
	//Rotaciones
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glRotatef(RX, 1.0f, 0, 0);
	glRotatef(RY, 0, 1, 0);
	glRotatef(RZ, 0, 0, 1);

	// Dibujar escena
	escena->dibuja();

	glPopMatrix();
}

void preEmbaldosar() {
	pWIDTH = WIDTH;
	pHEIGHT = HEIGHT;
	pxRight = xRight;
	pxLeft = xLeft;
	pyTop = yTop;
	pyBot = yBot;
	pN = N;
	pF = F;
}

void desembaldosar() {
	WIDTH = pWIDTH;
	HEIGHT = pHEIGHT;
	xRight = pxRight;
	xLeft = pxLeft;
	yTop = pyTop;
	yBot = pyBot;
	N = pN;
	F = pF;
}

void initGL() {
	glClearColor(0.6f, 0.7f, 0.8f, 1.0);
	glEnable(GL_LIGHTING);

	glEnable(GL_COLOR_MATERIAL);
	glMaterialf(GL_FRONT, GL_SHININESS, 0.1f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glShadeModel(GL_SMOOTH);

	//Crear los objetos a dibujar
	buildSceneObjects();

	// Light0
	glEnable(GL_LIGHT0);
	GLfloat d[] = { 1.0, 1.0, 1.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, d);
	GLfloat a[] = { 0.3f, 0.3f, 0.3f, 1.0 };
	glLightfv(GL_LIGHT0, GL_AMBIENT, a);
	GLfloat p[] = { 25.0, 25.0, 0.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, p);
}


void embaldosar(int nCol) {
	GLdouble SVAratio = (xRight - xLeft) / (yTop - yBot);
	GLdouble w = (GLdouble)WIDTH / (GLdouble)nCol;
	//La altura de cada puerto se calcula proporcionalmente
	GLdouble h = w / SVAratio;
	int vista = 0;
	for (GLint c = 0; c < nCol; c++) {
		GLdouble currentH = 0;
		while ((currentH + h) <= HEIGHT){
			glViewport((GLint)(c*w), (GLint)currentH, (GLint)w, (GLint)h);
			switch (vista) {
			case 0:
				camara->lateral();
				break;
			case 1:
				camara->frontal();
				break;
			case 2:
				camara->cenital();
				break;
			case 3:
				camara->esquina();
				break;
			}
			vista++;
			drawScene(); //dibujar la escena
			dibujaEjes();
			currentH += h;
		}
	}
}

void resize(int newWidth, int newHeight) {
	WIDTH = newWidth;
	HEIGHT = newHeight;
	GLdouble RatioViewPort = (float)WIDTH / (float)HEIGHT;
	glViewport(0, 0, WIDTH, HEIGHT);

	GLdouble SVAWidth = xRight - xLeft;
	GLdouble SVAHeight = yTop - yBot;
	GLdouble SVARatio = SVAWidth / SVAHeight;
	if (SVARatio >= RatioViewPort) {
		GLdouble newHeight = SVAWidth / RatioViewPort;
		GLdouble yMiddle = (yBot + yTop) / 2.0;
		yTop = yMiddle + newHeight / 2.0;
		yBot = yMiddle - newHeight / 2.0;
	}
	else {
		GLdouble newWidth = SVAHeight*RatioViewPort;
		GLdouble xMiddle = (xLeft + xRight) / 2.0;
		xRight = xMiddle + newWidth / 2.0;
		xLeft = xMiddle - newWidth / 2.0;
	}

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (ORTOGONAL)
		glOrtho(xLeft, xRight, yBot, yTop, N, F);
	else
		glFrustum(xLeft, xRight, yBot, yTop, N, F);
}

void actualiza() {
	glViewport(0, 0, WIDTH, HEIGHT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//Ortogonal o perspectiva
	if (ORTOGONAL)
		glOrtho(xLeft, xRight, yBot, yTop, N, F);
	else //Perspectiva
		glFrustum(xLeft, xRight, yBot, yTop, N, F);
}

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (EMBALDOSAR) embaldosar(NCOL); //modo embaldosado
	else actualiza();

	dibujaEjes();
	drawScene();

	glFlush();
	glutSwapBuffers();
}

void zoom(bool aumentar) {
	double f;
	aumentar ? f = 2 : f = -1.5;

	double centroX = (xRight - xLeft) / 2;
	double centroY = (yTop - yBot) / 2;
	double nw = centroX / f;
	double nh = centroY / f;

	xLeft += (nw / 2);
	xRight -= (nw / 2);
	yTop -= (nh / 2);
	yBot += (nh / 2);
}

void key(unsigned char key, int x, int y) {
	bool need_redisplay = true;
	switch (key) {
	case 'a':
		RX -= ROTACION;
		cout << "Rotacion -X" << endl;
		break;
	case 'z':
		RX += ROTACION;
		cout << "Rotacion X" << endl;
		break;
	case 'G':
		RELLENO = true;
		cout << "MODO RELLENO" << endl;
		break;
	case 'H':
		RELLENO = false;
		cout << "MODO ARMAZON" << endl;
		break;
	case 'J':
		NORM = true;
		cout << "MOSTRAR NORMALES" << endl;
		break;
	case 'K':
		NORM = false;
		cout << "OCULTAR NORMALES" << endl;
		break;
	case 's':
		yTop += incrY;
		yBot += incrY;
		actualiza();
		cout << "Centro abajo" << endl;
		break;
	case 'x':
		yTop -= incrY;
		yBot -= incrY;
		actualiza();
		cout << "Centro arriba" << endl;
		break;
	case 'd':
		xLeft -= incrX;
		xRight -= incrX;
		actualiza();
		cout << "Centro derecha" << endl;
		break;
	case 'c':
		xLeft += incrX;
		xRight += incrX;
		actualiza();
		cout << "Centro izquierda" << endl;
		break;
	case 'p':
		preEmbaldosar();
		EMBALDOSAR = true;
		cout << "Embaldosar" << endl;
		break;
	case 'o':
		EMBALDOSAR = false;
		desembaldosar();
		cout << "Desembaldosar" << endl;
		break;
	case 't':
		zoom(true);
		actualiza();
		cout << "Aumentar zoom" << endl;
		break;
	case 'y':
		zoom(false);
		actualiza();
		cout << "Alejar zoom" << endl;
		break;
	case '1':
		camara->giraX();
		cout << "Camara gira X" << endl;
		break;
	case '2':
		camara->giraY();
		cout << "Camara gira Y" << endl;
		break;
	case '3':
		camara->giraZ();
		cout << "Camara gira Z" << endl;
		break;
	case '4':
		camara->lateral();
		cout << "Camara lateral" << endl;
		break;
	case '5':
		camara->frontal();
		cout << "Camara frontal" << endl;
		break;
	case '6':
		camara->cenital();
		cout << "Camara cenital" << endl;
		break;
	case '7':
		camara->esquina();
		cout << "Camara esquina" << endl;
		break;
	case 'e':
		camara->recorridoEje(-5, 0, 0);
		cout << "Camara recorrido X izq" << endl;
		break;
	case 'r':
		camara->recorridoEje(5, 0, 0);
		cout << "Camara recorrido X der" << endl;
		break;
	case 'f':
		camara->recorridoEje(0, -5, 0);
		cout << "Camara recorrido Y izq" << endl;
		break;
	case 'g':
		camara->recorridoEje(0, 5, 0);
		cout << "Camara recorrido Y der" << endl;
		break;
	case 'v':
		camara->recorridoEje(0, 0, -5);
		cout << "Camara recorrido Z izq" << endl;
		break;
	case 'b':
		camara->recorridoEje(0, 0, 5);
		cout << "Camara recorrido Z der" << endl;
		break;
	case ',':
		//Ajustar el zoom
		xRight = 10;
		xLeft = -10;
		yTop = 10;
		yBot = -10;
		ORTOGONAL = true;
		camara->ortogonal();
		cout << "Camara ortogonal" << endl;
		break;
	case '.':
		//Ajustar el zoom
		xRight = 0.1;
		xLeft = -0.1;
		yTop = 0.1;
		yBot = -0.1;
		ORTOGONAL = false;
		camara->perspectiva();
		cout << "Camara perspectiva" << endl;
		break;
	case 'u':
		camara->roll(-5);
		cout << "Roll -" << endl;
		break;
	case 'i':
		camara->roll(5);
		cout << "Roll +" << endl;
		break;
	case 'j':
		camara->yaw(-5);
		cout << "Yaw -" << endl;
		break;
	case 'k':
		camara->yaw(5);
		cout << "Yaw +" << endl;
		break;
	case 'n':
		camara->pitch(-2);
		cout << "Pitch -" << endl;
		break;
	case 'm':
		camara->pitch(2);
		cout << "Pitch +" << endl;
		break;
	case 'q':
		camara->circuito(-0.5);
		cout << "Retrocede camara interior" << endl;
		break;
	case 'A':
		camara->lookAt(escena->mueveCoche(0.3));
		cout << "Avanzar coche" << endl;
		break;
	case 'Z':
		camara->lookAt(escena->mueveCoche(-0.3));
		cout << "Retroceder coche" << endl;
		break;
	case 27:  /* Escape key */
		//continue_in_main_loop = false; // (**)
		//Freeglut's sentence for stopping glut's main loop (*)
		glutLeaveMainLoop();
		break;
	default:
		need_redisplay = false;
		break;
	}

	if (need_redisplay)
		glutPostRedisplay();
}

void SpecialInput(int key, int x, int y) {
	bool need_redisplay = true;

	switch (key) {
	case GLUT_KEY_UP:
		RZ += ROTACION;
		cout << "arriba" << endl;
		break;
	case GLUT_KEY_DOWN:
		RZ -= ROTACION;
		cout << "abajo" << endl;
		break;
	case GLUT_KEY_LEFT:
		RY -= ROTACION;
		cout << "izquierda" << endl;
		break;
	case GLUT_KEY_RIGHT:
		RY += ROTACION;
		cout << "derecha" << endl;
		break;
	default:
		need_redisplay = false;
		break;
	}

	if (need_redisplay)
		glutPostRedisplay();
}

int main(int argc, char *argv[]) {
	cout << "Starting console..." << endl;

	int my_window; // my window's identifier

	// Initialization
	glutInitWindowSize(WIDTH, HEIGHT);
	glutInitWindowPosition(140, 140);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInit(&argc, argv);

	// Window construction
	my_window = glutCreateWindow("Freeglut 3D-project");

	// Callback registration
	glutReshapeFunc(resize);
	glutKeyboardFunc(key);
	glutSpecialFunc(SpecialInput);
	glutDisplayFunc(display);

	// OpenGL basic setting
	initGL();

	// Freeglut's main loop can be stopped executing (**)
	// while (continue_in_main_loop) glutMainLoopEvent();

	// Classic glut's main loop can be stopped after X-closing the window,
	// using the following freeglut's setting (*)
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);

	// Classic glut's main loop can be stopped in freeglut using (*)
	glutMainLoop();

	// We would never reach this point using classic glut
	//system("PAUSE");

	return 0;
}
