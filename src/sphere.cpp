#include <iostream>
#include "sphere.h"
#include <cmath>
#include <vector> 

using namespace std;

Sphere::Sphere(){
	radius = 1;
	center = Vector(0, 0, 0);
}

Sphere::Sphere(double r, Vector &vec){
	radius = r;
	center = vec;
}

vector<Vector> intersection(Ray &ray){
	
}

void Vector::represent(){
	cout<<"Radius: "<<radius<<endl;
	cout<<"Center: "<<"("<<center.x<<","<<center.y<<","<<center.z<<")"<<endl;
}

