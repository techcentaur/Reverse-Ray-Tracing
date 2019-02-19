#include <cmath>
#include <chrono>
#include <iostream>
#include "vector.h"

#include "color.h"
#include "object.h"
#include "vector.h"
#include "ray.h"
#include "material.h"
#include "light.h"
#include "tracer.h"
#include "camera.h"

// use full path if linux don't manully look into /usr/include
#include "/usr/include/GL/glut.h"

using namespace std;

/* Define global variables */
#define WINWIDTH 1000
#define WINHEIGHT 800

float* pixelBuffer = new float[WINWIDTH * WINHEIGHT * 3];


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



/* Global variables for ray tracing */
vector<Object*> objects;
vector<Light*> lights;
Camera cam;



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
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_DOUBLEBUFFER);
	
	glDrawPixels(WINWIDTH, WINHEIGHT, GL_RGB, GL_FLOAT, pixelBuffer);
	
	glutSwapBuffers();
    
    glFlush();
}

void myReshape(int w, int h)
{
	// set the viewport to window
    glViewport(0, 0, w, h);
    // use projection matrix
    glMatrixMode(GL_PROJECTION);
    // reset matrix
    glLoadIdentity();

    // get orthographic matrix
    // glOrtho (-1.5, 1.5, -1.5*(GLfloat)480/(GLfloat)640, 
    //         1.5*(GLfloat)480/(GLfloat)640, -10.0, 10.0);

	glOrtho(-10, 10, -10, 10, -10, 10);
    	
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

void drawInPixelBuffer(int x, int y, double r, double g, double b){
	// write in pixel buffer

	pixelBuffer[(y*WINWIDTH + x) * 3] = (float)r;
	pixelBuffer[(y*WINWIDTH + x) * 3 + 1] = (float)g;
	pixelBuffer[(y*WINWIDTH + x) * 3 + 2] = (float)b;
}


void renderScene(){
	if (deltaMove)
		computePos(deltaMove);
	if (deltaAngle)
		computeDir(deltaAngle);

    int width = WINWIDTH;
    int height = WINHEIGHT;
    int superSamplingRays = cam.superSampling;
    int fieldOfView = cam.fov;

    Tracer rayTracer;

    for(int i=height-1; i>=0; i--){
        for(int j=0; j<width; j++){
            Color3f col(0.f, 0.f, 0.f);
            for(int s=0; s<superSamplingRays; s++){
                float x = float(j + drand48()) / float(width);
                float y = float(i + drand48()) / float(height);

                Ray3f newRay = cam.getRay(x, y);
                col += (rayTracer.RayCasting(newRay, objects, lights, 0));
            }
            col /= float(superSamplingRays);
            drawInPixelBuffer(j, i, col.r, col.g, col.b);
        }
    }
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

void readObjects();

int main(int argc, char **argv){
	cout << "[*] Ray-Tracing OpenGL implementation" << endl;
	cout << "[.] Press Q to quit" << endl;

	// Init the window
	glutInit(&argc,argv);
	// Window size and position
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(WINWIDTH, WINHEIGHT);

    // glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGBA |GLUT_DEPTH);
    glutCreateWindow("Ray tracing");

    // register callbacks
    glutDisplayFunc(display);
    glutReshapeFunc(myReshape);
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

	/* get objects */
	cout<<objects.size()<<endl;
	readObjects();
	cout<<objects.size()<<endl;	

	// renderScene();

    // main loop
    glutMainLoop();

	delete[] pixelBuffer;

	return 0;
}

void readObjects(){
    string sName = "./inputsample";

    ifstream ifs;
    ifs.open(sName, ios::in);
    if(!ifs.is_open()) {
        cout<<"Error opening file"<<endl;
    }

    while(ifs.good()){
        string type;
        ifs>>type;
        if(type == "LIGHTS") {
            while(ifs.good()){
                ifs>>type;
                if(type=="LIGHT"){
                    Vector3f pos;
                    float intensity;
                    ifs>>pos.x>>pos.y>>pos.z>>intensity;
                    Light *l1 = new Light(pos, intensity);
                    lights.push_back(l1);
                }
                else{
                    break;
                }
            }
        }
        if(type=="CAMERA"){
            Vector3f lookFrom, lookAt, viewUp;
            float fov, height, width, sSampling, recursionDepth;
            while(ifs.good()){
                ifs>>type;
                if(type == "LOOKFROM"){
                    ifs>>lookFrom.x>>lookFrom.y>>lookFrom.z;
                }
                else if(type == "LOOKAT") {
                    ifs>>lookAt.x>>lookAt.y>>lookAt.z;
                }
                else if(type == "VIEWUP") {
                    ifs>>viewUp.x>>viewUp.y>>viewUp.z;
                }
                else if(type == "DIMENSIONS") {
                    ifs>>width>>height;
                }
                else if(type == "FOV") {
                    ifs>>fov;
                }
                else if(type == "SUPERSAMPLING") {
                    ifs>>sSampling;
                }
                else if(type == "RECURSION_DEPTH") {
                    ifs>>recursionDepth;
                }
                else{
                    break;
                }
            }
            cam.formCamera(lookFrom, lookAt, viewUp, fov, width, height, sSampling, recursionDepth);
        }
        if(type == "OBJECT") {
            while(ifs.good()){
                ifs>>type;
                if(type == "SPHERE"){
                    Vector3f origin;
                    Color3f color;
                    float sRE, sRC, dRC, reflecC, refracC, rI, radius;
                    while(ifs.good()){
                        ifs>>type;
                        if(type=="COLOR"){
                            ifs>>color.r>>color.g>>color.b;
                        }
                        else if(type=="SPECULAR_REFLECTION_EXPONENT"){
                            ifs>>sRE;
                        }
                        else if(type=="SPECULAR_REFLECTION_COEFF"){
                            ifs>>sRC;
                        }
                        else if(type=="DIFFUSE_REFLECTION_COEFF"){
                            ifs>>dRC;
                        }
                        else if(type=="REFLECTION_COEFF"){
                            ifs>>reflecC;
                        }
                        else if(type=="REFRACTION_COEFF"){
                            ifs>>refracC;
                        }
                        else if(type=="REFRACTIVE_INDEX"){
                            ifs>>rI;
                        }
                        else if(type=="ORIGIN"){
                            ifs>>origin.x>>origin.y>>origin.z;
                        }
                        else if(type=="RADIUS"){
                            ifs>>radius;
                        }
                        else {
                            break;
                        }
                    }
                    Material m;
                    m.fillColor(color, sRE, sRC, dRC, reflecC, refracC, rI);
                    Object *s = new Sphere(radius, origin, m);
                    objects.push_back(s);
                }
                else if(type == "CONE"){
                    Vector3f center, upVector;
                    Color3f color;
                    float sRE, sRC, dRC, reflecC, refracC, rI, alpha, height;
                    while(ifs.good()){
                        ifs>>type;
                        if(type=="COLOR"){
                            ifs>>color.r>>color.g>>color.b;
                        }
                        else if(type=="SPECULAR_REFLECTION_EXPONENT"){
                            ifs>>sRE;
                        }
                        else if(type=="SPECULAR_REFLECTION_COEFF"){
                            ifs>>sRC;
                        }
                        else if(type=="DIFFUSE_REFLECTION_COEFF"){
                            ifs>>dRC;
                        }
                        else if(type=="REFLECTION_COEFF"){
                            ifs>>reflecC;
                        }
                        else if(type=="REFRACTION_COEFF"){
                            ifs>>refracC;
                        }
                        else if(type=="REFRACTIVE_INDEX"){
                            ifs>>rI;
                        }
                        else if(type=="CENTER"){
                            ifs>>center.x>>center.y>>center.z;
                        }
                        else if(type=="UPVECTOR"){
                            ifs>>upVector.x>>upVector.y>>upVector.z;
                        }
                        else if(type=="ALPHA"){
                            ifs>>alpha;
                        }
                        else if(type=="HEIGHT"){
                            ifs>>height;
                        }
                        else {
                            break;
                        }
                    }
                    Material m;
                    m.fillColor(color, sRE, sRC, dRC, reflecC, refracC, rI);
                    Object* c = new Cone(center, upVector, alpha, height, m);
                    objects.push_back(c);
                }
                else if(type == "PLANE"){
                    Vector3f point1, point2, point3;
                    Color3f color;
                    float sRE, sRC, dRC, reflecC, refracC, rI;
                    while(ifs.good()){
                        ifs>>type;
                        if(type=="COLOR"){
                            ifs>>color.r>>color.g>>color.b;
                        }
                        else if(type=="SPECULAR_REFLECTION_EXPONENT"){
                            ifs>>sRE;
                        }
                        else if(type=="SPECULAR_REFLECTION_COEFF"){
                            ifs>>sRC;
                        }
                        else if(type=="DIFFUSE_REFLECTION_COEFF"){
                            ifs>>dRC;
                        }
                        else if(type=="REFLECTION_COEFF"){
                            ifs>>reflecC;
                        }
                        else if(type=="REFRACTION_COEFF"){
                            ifs>>refracC;
                        }
                        else if(type=="REFRACTIVE_INDEX"){
                            ifs>>rI;
                        }
                        else if(type=="POINT1"){
                            ifs>>point1.x>>point1.y>>point1.z;
                        }
                        else if(type=="POINT2"){
                            ifs>>point2.x>>point2.y>>point2.z;
                        }
                        else if(type=="POINT3"){
                            ifs>>point3.x>>point3.y>>point3.z;
                        }
                        else {
                            break;
                        }
                    }
                    Material m;
                    m.fillColor(color, sRE, sRC, dRC, reflecC, refracC, rI);
                    Object* p = new Plane(point1, point2, point3, m);
                    objects.push_back(p);
                }
                else if(type == "BOX"){
                    Color3f color;
                    Vector3f translate, scale;
                    float sRE, sRC, dRC, reflecC, refracC, rI;
                    while(ifs.good()){
                        ifs>>type;
                        if(type=="COLOR"){
                            ifs>>color.r>>color.g>>color.b;
                        }
                        else if(type=="SPECULAR_REFLECTION_EXPONENT"){
                            ifs>>sRE;
                        }
                        else if(type=="SPECULAR_REFLECTION_COEFF"){
                            ifs>>sRC;
                        }
                        else if(type=="DIFFUSE_REFLECTION_COEFF"){
                            ifs>>dRC;
                        }
                        else if(type=="REFLECTION_COEFF"){
                            ifs>>reflecC;
                        }
                        else if(type=="REFRACTION_COEFF"){
                            ifs>>refracC;
                        }
                        else if(type=="REFRACTIVE_INDEX"){
                            ifs>>rI;
                        }
                        else if(type=="TRANSLATE"){
                            ifs>>translate.x>>translate.y>>translate.z;
                        }
                        else if(type=="SCALE"){
                            ifs>>scale.x>>scale.y>>scale.z;
                        }
                        else {
                            break;
                        }
                    }
                    Material m;
                    m.fillColor(color, sRE, sRC, dRC, reflecC, refracC, rI);
                    Object* b = new Box(translate, scale, m);
                    objects.push_back(b);
                }
                else{
                    break;
                }
            }
        }
        if(type == "CUT"){
            break;
        }
    }

}