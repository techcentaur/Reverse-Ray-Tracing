#include <cmath>
#include <chrono>
#include <iostream>
#include "vector.h"
// #include "object.h"
// #include "light."

// use full path if linux don't manully look into /usr/include
#include "/usr/include/GL/glut.h"

using namespace std;

/* Define global variables */

// Angle of rotation for the camera direction
float angle=0.0;
// Vector representing camera direction
float lx=0.0f, lz=-1.0f;
// XZ position of the camera
float x=0.0f, z=5.0f;

// key states: No key press -> set variable value to zero
float deltaAngle = 0.0f;
float deltaMove = 0;

int xOrigin = -1;


void drawSphere2()
{
	glTranslatef(0.0f ,0.75f, 0.0f);
	glutSolidSphere(0.75f,20,20);

	glTranslatef(0.0f, 1.0f, 0.0f);
	glutSolidSphere(0.25f,20,20);
}

void drawSphere(){
	glutSolidSphere(0.25f,20,20);
}

void display(void)
{
    glClearColor(1,1,1,1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glutSolidSphere(0.5, 100, 100);
    glFlush();
}

void myReshape(GLsizei w, GLsizei h)
{
	// set the viewport to window
    glViewport(0, 0, w, h);
    // use projection matrix
    glMatrixMode(GL_PROJECTION);
    // reset matrix
    glLoadIdentity();

    // get orthographic matrix
    glOrtho (-1.5, 1.5, -1.5*(GLfloat)480/(GLfloat)640, 
            1.5*(GLfloat)480/(GLfloat)640, -10.0, 10.0);
    	
    // get back to model view
    glMatrixMode(GL_MODELVIEW);
    //glViewport(0,0,w,h);  //Use the whole window for rendering
    glLoadIdentity();
}



void keyboardEvents(unsigned char key, int x, int y){
	switch (key) {
		case 'q':
		case 'Q':
			exit(0);

		default:
			break;
	}
}

void computePos(float deltaMove) {

	x += deltaMove * lx * 0.1f;
	z += deltaMove * lz * 0.1f;
}

void computeDir(float deltaAngle) {

	angle += deltaAngle;
	lx = sin(angle);
	lz = -cos(angle);
}

void pressKey(int key, int xx, int yy) {

	switch (key) {
		case GLUT_KEY_LEFT : deltaAngle = -0.01f; break;
		case GLUT_KEY_RIGHT : deltaAngle = 0.01f; break;
		case GLUT_KEY_UP : deltaMove = 0.5f; break;
		case GLUT_KEY_DOWN : deltaMove = -0.5f; break;
	}
}

void releaseKey(int key, int x, int y) {

	switch (key) {
		case GLUT_KEY_LEFT :
		case GLUT_KEY_RIGHT : deltaAngle = 0.0f;break;
		case GLUT_KEY_UP :
		case GLUT_KEY_DOWN : deltaMove = 0;break;
	}
}


void renderScene(){
	if (deltaMove)
		computePos(deltaMove);
	if (deltaAngle)
		computeDir(deltaAngle);


	// clear color and depth buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// reset transformations
	glLoadIdentity();

	// camera position to look at 
	gluLookAt(	x, 1.0f, z,
			x+lx, 1.0f,  z+lz,
			0.0f, 1.0f,  0.0f);

	// draw ground
	glColor3f(0.9f, 0.9f, 0.9f);
	glBegin(GL_QUADS);
		glVertex3f(-100.0f, 0.0f, -100.0f);
		glVertex3f(-100.0f, 0.0f, 100.0f);
		glVertex3f(100.0f, 0.0f, 100.0f);
		glVertex3f(100.0f, 0.0f, -100.0f);
	glEnd();

	drawSphere2();

	glutSwapBuffers();

}

void mouseButton(int button, int state, int x, int y) {

	// only start motion if the left button is pressed
	if (button == GLUT_LEFT_BUTTON) {

		// when the button is released
		if (state == GLUT_UP) {
			angle += deltaAngle;
			xOrigin = -1;
		}
		else  {// state = GLUT_DOWN
			xOrigin = x;
		}
	}
}
void mouseMove(int x, int y) {

	// this will only be true when the left button is down
	if (xOrigin >= 0) {

		// update deltaAngle
		deltaAngle = (x - xOrigin) * 0.001f;

		// update camera's direction
		lx = sin(angle + deltaAngle);
		lz = -cos(angle + deltaAngle);
	}
}


int main(int argc, char **argv){
	cout << "[*] Ray-Tracing OpenGL implementation" << endl;
	cout << "[.] Press Q to quit" << endl;

	// Init the window
	glutInit(&argc,argv);
	// Window size and position
    glutInitWindowSize (1000, 800);
    glutInitWindowPosition (200, 200);

    // single buffer display mode
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGBA |GLUT_DEPTH);
    glutCreateWindow("Ray tracing");

    // register callbacks
    glutDisplayFunc(display);
    glutReshapeFunc (myReshape);
	glutIdleFunc(renderScene);

	// register call back for keyboard and mouse movements
	glutKeyboardFunc(keyboardEvents);
	glutSpecialFunc(pressKey);

	glutIgnoreKeyRepeat(1);
	glutSpecialUpFunc(releaseKey);

	// mouse controls
	glutMouseFunc(mouseButton);
	glutPassiveMotionFunc(mouseMove);

	glEnable(GL_DEPTH_TEST);

    // main loop
    glutMainLoop();

}