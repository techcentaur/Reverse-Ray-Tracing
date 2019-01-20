#include <iostream>
#include "sphere.h"
#include <cmath>
#include <algorithm>

using namespace std;

Sphere::Sphere(){
	radius = 1;
	center = Vector(0, 0, 0);
}

Sphere::Sphere(double r, Vector &vec){
	radius = r;
	center = vec;
}

Vector Sphere::intersection(Ray &ray){
	double A =  ray.direction.lengthSquare();
	double B = 2*(ray.direction.x*(ray.origin.x - center.x) + ray.direction.y*(ray.origin.y - center.y) + ray.direction.z*(ray.origin.z - center.z));
	double C = pow((ray.origin.x - center.x), 2) + pow((ray.origin.y - center.y), 2) + pow((ray.origin.z - center.z), 2);

	double t0 = ((-1*B) + (-1*sqrt(B*B - 4*A*C)))/(2*A);
	double t1 = ((-1*B) + (sqrt(B*B - 4*A*C)))/(2*A);
	
	double tMin = min(t0, t1);
	Vector point_1 = ray.origin + ray.direction*tMin;
}

void Sphere::print(){
	cout<<"Radius: "<<radius<<endl;
	cout<<"Center: "<<center.print();
}
