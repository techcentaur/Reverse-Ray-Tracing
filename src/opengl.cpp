#include <cmath>
#include <chrono>
#include <iostream>
#include "vector.h"
// use full path if linux don't manully look into /usr/include
#include "/usr/include/GL/glut.h"
#include "object.h"
#include "ray.h"

using namespace std;


// Define constants
#define WINWIDTH 600
#define WINHEIGHT 400
#define NUM_OBJECTS 2

// A buffer to place pixels to display
float* pixelBuffer = new float[WINWIDTH * WINHEIGHT * 3];



void displayPixels(void){
	/*
	displayPixels the pixelbuffer
	*/

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_DOUBLEBUFFER);
	glDrawPixels(WINWIDTH, WINHEIGHT, GL_RGB, GL_FLOAT, pixelBuffer);
	glutSwapBuffers();
	glFlush();
}

void reshapeViewport(int w, int h){
	/*
	reshape the view window
	*/

	glViewport(0, 0, (GLsizei)w, (GLsizei)h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(-10, 10, -10, 10, -10, 10);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


void keyboardEvents(unsigned char key, int x, int y){
	/*
	Handle keyboard events
	*/

	switch (key) {
		case 'q':
		case 'Q':
			exit(0);

		default:
			break;
	}
}

int main(int argc, char **argv){
	cout << "[*] Ray-Tracing OpenGL implementation" << endl;
	cout << "[.] Q to quit" << endl;
	
	// Initialise glut
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(WINWIDTH, WINHEIGHT);

	// create a named window
	glutCreateWindow("Ray Tracing");

	// display the initial pixel buffer
	glutDisplayFunc(displayPixels);
	// change the window shape
	glutReshapeFunc(reshapeViewport);

	// turn on the keyboard events
	glutKeyboardFunc(keyboardEvents);

	// start the main loop
	glutMainLoop();

	return 0;
}
