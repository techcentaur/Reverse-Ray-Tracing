#include <GL/glut.h>
#include "sphere.h"

GLdouble radius=1;
    
Sphere::Sphere(){
    radius = 1;
    centerX = 0.0;
    centerY = 0.0;
    centerZ = -3.0;
    
    // this->init();

    this->translate(this->centerX, this->centerX, this->centerX);
    this->rotate(0.0, 0.0, 0.0);
    this->scale(1.0, 1.0, 1.0);

    // this->display();

    void reshape(int x, int y);

    // glutDisplayFunc(display);
    // glutReshapeFunc(reshape);
 
}

void Sphere::init(){
    glMatrixMode(GL_MODELVIEW);
    // clear the drawing buffer.
    glClear(GL_COLOR_BUFFER_BIT);
    // clear the identity matrix.
    glLoadIdentity();
}

void Sphere::translate(float x, float y, float z){
    // camera looks in -z direction.  
    glTranslatef(x,y,z);
}

void Sphere::rotate(float x, float y, float z){ 
    GLfloat xRotate = 0.0;
    GLfloat yRotate = 0.0;
    GLfloat zRotate = 0.0;

    // rotation about X axis
    glRotatef(xRotate,x,0.0,0.0);
    // rotation about Y axis
    glRotatef(yRotate,0.0,y,0.0);
    // rotation about Z axis
    glRotatef(zRotate,0.0,0.0,z);
}

void Sphere::scale(float x, float y, float z){ 
    // scaling transfomation 
    glScalef(1.0,1.0,1.0);
}