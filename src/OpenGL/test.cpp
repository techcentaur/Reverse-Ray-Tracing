#include <GL/glut.h>

GLfloat xRotated = 90.0;
GLfloat yRotated = 95.0;
GLfloat zRotated;
GLdouble radius = 1;

void displaySphere()
{   
    glMatrixMode(GL_MODELVIEW);
    // clear the drawing buffer.
    glClear(GL_COLOR_BUFFER_BIT);
    // clear the identity matrix.
    glLoadIdentity();

    // camera looks in -z direction.  
    glTranslatef(3.0,4.0,-10.0);


    glRotatef(xRotated,1.0,0.0,0.0);
    // rotation about Y axis
    glRotatef(yRotated,0.0,1.0,0.0);
    // rotation about Z axis
    glRotatef(zRotated,0.0,0.0,1.0);


    glColor3f(1.0, 0.2, 0.1);
    // built-in (glut library) function , draw you a sphere.
    glutSolidSphere(radius,200,200);
    
    // Flush buffers to screen 
    glFlush();        
    // sawp buffers called because we are using double buffering 
    glutSwapBuffers();
}

void displayCube()
{
    glMatrixMode(GL_MODELVIEW);
    // clear the drawing buffer.
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    
    glTranslatef(0.0,0.0,-10.0);
    
    glRotatef(xRotated,1.0,0.0,0.0);
    // rotation about Y axis
    glRotatef(yRotated,0.0,1.0,0.0);
    // rotation about Z axis
    glRotatef(zRotated,0.0,0.0,1.0);
    
    glBegin(GL_QUADS);        // Draw The Cube Using quads
    glColor3f(0.0f,1.0f,0.0f);    // Color Blue
    glVertex3f( 1.0f, 1.0f,-1.0f);    // Top Right Of The Quad (Top)
    glVertex3f(-1.0f, 1.0f,-1.0f);    // Top Left Of The Quad (Top)
    glVertex3f(-1.0f, 1.0f, 1.0f);    // Bottom Left Of The Quad (Top)
    glVertex3f( 1.0f, 1.0f, 1.0f);    // Bottom Right Of The Quad (Top)
    glColor3f(1.0f,0.5f,0.0f);    // Color Orange
    glVertex3f( 1.0f,-1.0f, 1.0f);    // Top Right Of The Quad (Bottom)
    glVertex3f(-1.0f,-1.0f, 1.0f);    // Top Left Of The Quad (Bottom)
    glVertex3f(-1.0f,-1.0f,-1.0f);    // Bottom Left Of The Quad (Bottom)
    glVertex3f( 1.0f,-1.0f,-1.0f);    // Bottom Right Of The Quad (Bottom)
    glColor3f(1.0f,0.0f,0.0f);    // Color Red    
    glVertex3f( 1.0f, 1.0f, 1.0f);    // Top Right Of The Quad (Front)
    glVertex3f(-1.0f, 1.0f, 1.0f);    // Top Left Of The Quad (Front)
    glVertex3f(-1.0f,-1.0f, 1.0f);    // Bottom Left Of The Quad (Front)
    glVertex3f( 1.0f,-1.0f, 1.0f);    // Bottom Right Of The Quad (Front)
    glColor3f(1.0f,1.0f,0.0f);    // Color Yellow
    glVertex3f( 1.0f,-1.0f,-1.0f);    // Top Right Of The Quad (Back)
    glVertex3f(-1.0f,-1.0f,-1.0f);    // Top Left Of The Quad (Back)
    glVertex3f(-1.0f, 1.0f,-1.0f);    // Bottom Left Of The Quad (Back)
    glVertex3f( 1.0f, 1.0f,-1.0f);    // Bottom Right Of The Quad (Back)
    glColor3f(0.0f,0.0f,1.0f);    // Color Blue
    glVertex3f(-1.0f, 1.0f, 1.0f);    // Top Right Of The Quad (Left)
    glVertex3f(-1.0f, 1.0f,-1.0f);    // Top Left Of The Quad (Left)
    glVertex3f(-1.0f,-1.0f,-1.0f);    // Bottom Left Of The Quad (Left)
    glVertex3f(-1.0f,-1.0f, 1.0f);    // Bottom Right Of The Quad (Left)
    glColor3f(1.0f,0.0f,1.0f);    // Color Violet
    glVertex3f( 1.0f, 1.0f,-1.0f);    // Top Right Of The Quad (Right)
    glVertex3f( 1.0f, 1.0f, 1.0f);    // Top Left Of The Quad (Right)
    glVertex3f( 1.0f,-1.0f, 1.0f);    // Bottom Left Of The Quad (Right)
    glVertex3f( 1.0f,-1.0f,-1.0f);    // Bottom Right Of The Quad (Right)
    
    glEnd();            // End Drawing The Cube
    
    glFlush();

    glutSwapBuffers();

}

void reshapeSphere(int x, int y)
{
    if (y == 0 || x == 0) return;   
    glMatrixMode(GL_PROJECTION);  
    glLoadIdentity(); 
    
    // Angle of view:40 degrees
    // Near clipping plane distance: 0.5
    // Far clipping plane distance: 20.0
    gluPerspective(40.0,(GLdouble)x/(GLdouble)y,0.5,20.0);
    
    glMatrixMode(GL_MODELVIEW);
    
    glViewport(0,0,x,y);  //Use the whole window for rendering
}

void reshapeCube(int x, int y)
{
    if (y == 0 || x == 0) return;  //Nothing is visible then, so return
    //Set a new projection matrix
    glMatrixMode(GL_PROJECTION);  
    glLoadIdentity();
    
    // Angle of view:40 degrees
    // Near clipping plane distance: 0.5
    // Far clipping plane distance: 20.0
    gluPerspective(40.0,(GLdouble)x/(GLdouble)y,0.5,20.0);
    
    glMatrixMode(GL_MODELVIEW);
    
    glViewport(0,0,x,y);  //Use the whole window for rendering
}
 

int main (int argc, char **argv)
{
    glutInit(&argc, argv); 
    glutInitWindowSize(350,350);
    glutCreateWindow("Solid Sphere");
    
    void displaySphere();
    void reshapeSphere(int x, int y);
 
    void displayCube();
    void reshapeCube(int x, int y);
    
    glutReshapeFunc(reshapeSphere);
    glutDisplayFunc(displaySphere);
 
    glutDisplayFunc(displayCube);
    glutReshapeFunc(reshapeCube);

    glutMainLoop();
    return 0;
}
