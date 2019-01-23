#include <iostream>
#include <cmath>
#include <algorithm>
#include <tuple>

#include "vector.h"
#include "sphere.h"
#include "ray.h"

using namespace std;

Sphere::Sphere(){
}

Sphere::Sphere(float r, Vector3f &vec, Material &m){
	radius = r; center = vec; material = m;
}

tuple<Vector3f, bool> Sphere::getIntersection(Ray3f &ray, float &t0){
	// float A =  ray.direction.lengthSquare();
	// float B = ray.direction.dot(ray.origin - center)*2.f;
	// float C = (ray.origin - center).lengthSquare() - radius*radius;

	// float discriminant = B*B - 4*A*C;
	// float t1;

	Vector3f v(0, 0, 0);

	// if (discriminant < 0) return make_tuple(v, false);
	// discriminant = sqrt(discriminant);
	// t0 = ((-1*B) + (-1)*discriminant)/(2*A);
	// t1 = ((-1*B) + discriminant)/(2*A);		


	// if(t0 < 0) t0 = t1;
	// if(t0 < 0) return make_tuple(v, false);

	// float tMin = min(t0, t1);	
	// Vector3f point = ray.origin + ray.direction*tMin;

	Vector3f l = center - ray.origin;
	float tca = l.dot(ray.direction);
	float d2 = l.dot(l) - tca*tca;
	if(d2>radius*radius) return make_tuple(v, false);
	float thc = sqrtf(radius*radius - d2);
	t0 = tca-thc;
	float t1 = tca + thc;
	if(t0>0) t0 = t1;
	if(t0<0) return make_tuple(v, false);

	return make_tuple(v, true);
}

void Sphere::print(){
	cout<<"[*] Sphere: \n";
	cout<<"Center: "; center.print();
	cout<<"Radius: "<<radius<<"\n";
	cout<<"Material: "; material.print();
}