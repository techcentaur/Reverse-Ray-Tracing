#include <stdlib.h>
#include <math.h>
#include <vector>

// use full path if linux don't manully look into /usr/include: Somehow didn't work for me
#include "/usr/include/GL/glut.h"

// import ray tracing helper header files
#include "color.h"
#include "object.h"
#include "vector.h"
#include "ray.h"
#include "material.h"
#include "light.h"
#include "tracer.h"
#include "camera.h"

#include <iostream>
using namespace std;

// angle of rotation for the camera direction
float angle = 0.0f;

// actual vector representing the camera's direction
float lx=10.0f,lz=0.0f;

// XZ position of the camera
float x=10.0f, z=1.0f;

// the key states. These variables will be zero
//when no key is being presses
float deltaAngle = 0.0f;
float deltaMove = 0;


/* Global variables for ray tracing */
vector<Object*> objects;
vector<Light*> lights;
Camera cam;
vector<Vector3f> intersectionPoints;

void readObjects();

void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0)
		h = 1;
	float ratio =  w * 1.0 / h;

	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);

	// Reset Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(cam.fov, (cam.width/cam.height), 0.1f, 100.0f);

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
}

void drawIntersectionPoints(){
    glColor3f(0.9f, 0.9f, 0.9f);

	for(int i=4; i<intersectionPoints.size()-1; i++){
		Vector3f temp = intersectionPoints.at(i);
		Vector3f temp2 = intersectionPoints.at(i+1);
		glBegin(GL_LINES);
			glVertex3f(temp.x, temp.y, temp.z);
			glVertex3f(temp2.x, temp2.y, temp2.z);
		glEnd();	
	}
}

void drawCameraPlane(){
    glColor3f(0.9f, 0.9f, 0.9f);
    glTranslatef(10.0f, 1.75f, 1.0f);
    glBegin(GL_QUADS);
        glVertex3f(0.0f,0.1f,0.1f);
        glVertex3f(0.0f,0.1f,-0.1f);
        glVertex3f(0.0f,-0.1f,-0.1f);
        glVertex3f(0.0f,-0.1f,0.1f);
    glEnd();

    glTranslatef(-10.0f, -1.75f, -1.0f);
}

void drawSnowMan() {
    for(int i=0; i<objects.size(); i++){

    	glColor3f(0.3f, 0.8f, 0.9f);

    	glTranslatef(10.0f, 0.75f, 0.0f);
    	glutWireSphere(1.0f, 40, 40);

        glColor3f(0.3f, 0.8f, 0.1f);

        glTranslatef(-10.0f, -0.75f, -0.0f);
        glTranslatef(13.0f, 0.75f, 0.0f);
        glutWireSphere(1.0f, 40, 40);

        glColor3f(0.3f, 0.2f, 0.9f);
        glTranslatef(-13.0f, -0.75f, 0.0f);
        glTranslatef(7.0f, 0.75f, 0.0f);
        glutWireSphere(1.0f, 40, 40);

        glColor3f(0.5f, 0.8f, 0.9f);
        glTranslatef(-7.0f, -0.75f, -0.0f);
        glTranslatef(10.0f, 0.75f, 3.0f);
        glutWireSphere(1.0f, 40, 40);

        glTranslatef(-10.0f, -0.75f, -3.0f);
        
        glColor3f(1.0f, 0.1f, 0.1f);   
        glutWireSphere(0.05f, 40, 40);

        // [*] Vector: (0, 0, 1)
        // [*] Vector: (1, 0, 1)
        // [*] Vector: (1, 0.75, 1)
        // [*] Vector: (0, 0.75, 1)
        // [*] Vector: (10, 1.75, 1)
        // [*] Vector: (10.0715, -0.138762, 0.452753)
        // [*] Vector: (10.0285, 2.31128, 2.17287)
        // [*] Vector: (10.0584, 0.448467, 0.951665)
    }


    // for(int i=0; i<objects.size(); i++){
    //     glColor3f(float(objects.at(i)->material.r), float(objects.at(i)->material.r), float(objects.at(i)->material.r));
        
    //     glTranslatef(float(objects.at(i)->center.x), float(objects.at(i)->center.y), float(objects.at(i)->center.z));
    //     glutWireSphere(float(objects.at(i)->radius), 40, 40);

    //     glTranslatef(float(-1*(objects.at(i)->center.x)), float(-1*(objects.at(i)->center.y)), float(-1*(objects.at(i)->center.z)));
    // }


// 	glColor3f(0.1f, 0.5f, 0.5f);
// // Draw Head
// 	glTranslatef(0.0f, 1.0f, 0.0f);
// 	glutWireSphere(0.25f,20,20);

	// glPushMatrix();
	// glColor3f(0.0f,0.0f,0.0f);
	// glTranslatef(0.05f, 0.10f, 0.18f);
	// glutWireSphere(0.05f,10,10);
	// glTranslatef(-0.1f, 0.0f, 0.0f);
	// glutWireSphere(0.05f,10,10);
	// glPopMatrix();

// Draw Cone
	// glColor3f(0.9f, 0.1f , 0.5f);
	// glRotatef(0.1f, 1.0f, 0.0f, 0.0f);
	// glutWireCone(0.2f,0.5f,10,2);
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

void renderScene(void) {

	if (deltaMove)
		computePos(deltaMove);
	if (deltaAngle)
		computeDir(deltaAngle);

    glClearColor(0.2f, 0.7f, 0.7f, 1.0f);
	// Clear Color and Depth Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Reset transformations
	glLoadIdentity();
	// Set the camera
	gluLookAt(	x, 1.75f, z,  //position
				x+lx, 1.0f,  z+lz, //lookat
				0.0f, 1.0f,  0.0f); //view up

// Draw ground

	// glColor3f(0.9f, 0.9f, 0.9f);
	// glBegin(GL_QUADS);
	// 	glVertex3f(-100.0f, 0.0f, -100.0f);
	// 	glVertex3f(-100.0f, 0.0f,  100.0f);
	// 	glVertex3f( 100.0f, 0.0f,  100.0f);
	// 	glVertex3f( 100.0f, 0.0f, -100.0f);
	// glEnd();

	glPushMatrix();
	drawSnowMan();
	glPopMatrix();

    drawIntersectionPoints();
    drawCameraPlane();

	glutSwapBuffers();
}


void pressKey(int key, int xx, int yy) {

	switch (key) {
		case GLUT_KEY_LEFT : deltaAngle = -0.01f; break;
		case GLUT_KEY_RIGHT : deltaAngle = 0.01f; break;
		case GLUT_KEY_UP : deltaMove = 0.2f; break;
		case GLUT_KEY_DOWN : deltaMove = -0.2f; break;
	}
}

void releaseKey(int key, int x, int y) {

	switch (key) {
		case GLUT_KEY_LEFT :deltaAngle = 0.0f; break;
		case GLUT_KEY_RIGHT : deltaAngle = 0.0f; break;
		case GLUT_KEY_UP : deltaMove = 0.0f; break;
		case GLUT_KEY_DOWN : deltaMove = 0.0f; break;
	}
}

void keyboardEvents(unsigned char key, int x, int y){
	switch (key) {
		case 'q':
			exit(0);
		case 'Q':
			exit(0);
		default:
			break;
	}
}


void getIntersectionPoints(int i, int j){
	// get intersection points from ray tracer
    Tracer rayTracer;

    // read input file (in format) and get intersection points from ray tracing
    readObjects();
    intersectionPoints = rayTracer.getIntersectionPointsOfARay(objects, lights, cam, i, j);
}



int main(int argc, char **argv) {
	cout << "[*] Ray-Tracing OpenGL implementation" << endl;
	cout << "[.] Press Q to quit" << endl;

	getIntersectionPoints(27, 535);

    // init GLUT and create window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(200, 200);
    glutInitWindowSize(cam.width, cam.height);
    glutCreateWindow("Ray Tracing in OpenGL");

    // fill intersection points
    /*
    (i. j) are the probes on the pixel
    */


	// register callbacks
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutIdleFunc(renderScene);
	glutKeyboardFunc(keyboardEvents);

	// for keyboard movements
	glutSpecialFunc(pressKey);
	glutIgnoreKeyRepeat(1);
	glutSpecialUpFunc(releaseKey);

	// OpenGL init
	glEnable(GL_DEPTH_TEST);

	// enter GLUT event processing cycle
	glutMainLoop();

	return 1;
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