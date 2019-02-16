#include <GLFW/glfw3.h>
#include <glad

// void displayMe(void)
// {
//     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//     glBegin(GL_TRIANGLES);
//         glColor3f(1, 0, 0);
//         glVertex2f(0.5, 0.0);
        
//         glColor3f(0, 1, 0);
//         glVertex2f(0.5, 0.0);
        
//         glColor3f(0, 0, 1);
//         glVertex2f(0.0, 0.5);
//     glEnd();

//     glutSwapBuffers();

//     glFlush();
// }
 
int main(int argc, char** argv)
{
    // define the function's prototype
    typedef void (*GL_GENBUFFERS) (GLsizei, GLuint*);
    // find the function and assign it to a function pointer
    // GL_GENBUFFERS glGenBuffers  = (GL_GENBUFFERS)wglGetProcAddress("glGenBuffers");
    // function can now be called as normal
    unsigned int buffer;
    // glGenBuffers(1, &buffer);

    return 0;
    // glutInit(&argc, argv);
    // glutInitDisplayMode(GLUT_SINGLE | GLUT_DOUBLE | GLUT_RGBA);
    // glutInitWindowPosition(100, 100);
    // glutInitWindowSize(400, 300);
    // glutCreateWindow("Hello world!");
    
    // glutDisplayFunc(displayMe);
    
    // glutMainLoop();
    // return 0;
}
