#include <iostream>
#include <vector>
#include <cmath>
#include <iostream>
#include <vector>
#include <cmath>
// #include <GL/glut.h>
#include "vector.h"
#include "transformation.h"

using namespace std;
 
void displayMe(void)
{
    // glClear(GL_COLOR_BUFFER_BIT);
    // glBegin(GL_POLYGON);
    //     glVertex3f(0.5, 0.0, 0.5);
    //     glVertex3f(0.5, 0.0, 0.0);
    //     glVertex3f(0.0, 0.5, 0.0);
    //     glVertex3f(0.0, 0.0, 0.5);
    // glEnd();
    // glFlush();
}
 
int main(int argc, char** argv)
{
    // glutInit(&argc, argv);
    // glutInitDisplayMode(GLUT_SINGLE);
    // glutInitWindowSize(400, 300);
    // glutInitWindowPosition(100, 100);
    // glutCreateWindow("Hello world!");
    // glutDisplayFunc(displayMe);
    // glutMainLoop();


    Vector3f c(1.f,1.f,1.f);
    
    Transformation t;
    Vector3f rxy(t.shearingXAboutY(c,1));
    Vector3f rxy_(t.shearingXAboutY(c,-1));
    Vector3f ryz(t.shearingYAboutZ(c,2));

    rxy.print();
    rxy_.print();
    ryz.print();

    return 0;
}
