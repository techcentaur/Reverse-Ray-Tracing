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

double getNormal(Vector const &vec){
	
}


Vector Sphere::getIntersection(Ray &ray){
	double A =  ray.direction.lengthSquare();
	double B = 2*ray.direction.dot(ray.origin - center);
	double C = (ray.origin - center).lengthSquare() - radius*radius;

	double discriminant = B*B - 4*A*C;

	if (discriminant < 0) return -1;
	else {
		discriminant = sqrt(discriminant);
		double t0 = ((-1*B) + discriminant)/(2*A);
		double t1 = ((-1*B) + discriminant)/(2*A);		
	}

	double tMin = min(t0, t1);	
	Vector point_1 = ray.origin + ray.direction*tMin;

	return point_1;
}


void Sphere::print(){
	cout<<"Radius: "<<radius<<endl;
	cout<<"Center: "<<center.print();
}
