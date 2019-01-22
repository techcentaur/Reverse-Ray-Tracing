#include <iostream>
#include <cmath>
#include <algorithm>
#include <tuple>

#include "vector.h"
#include "sphere.h"
#include "ray.h"

using namespace std;

Sphere::Sphere(){
	radius = 1;
	Vector3f v(0.f, 0.f, 0.f);
	center = v;
}

Sphere::Sphere(float r, Vector3f &vec){
	radius = r; center = vec;
}
Sphere::~Sphere(){}

tuple<Vector3f, int> Sphere::getIntersection(Ray3f &ray, float &t0){
	float A =  ray.direction.lengthSquare();
	float B = ray.direction.dot(ray.origin - center)*2.f;
	float C = (ray.origin - center).lengthSquare() - radius*radius;

	float discriminant = B*B - 4*A*C;
	float t1;

	Vector3f v(0, 0, 0);

	if (discriminant < 0) make_tuple(v, -1);
	else {
		discriminant = sqrt(discriminant);
		t0 = ((-1*B) + (-1)*discriminant)/(2*A);
		t1 = ((-1*B) + discriminant)/(2*A);		
	}

	if(t0 < 0) t0 = t1;
	if(t0 < 0) return make_tuple(v, -1);

	float tMin = min(t0, t1);	
	Vector3f point = ray.origin + ray.direction*tMin;

	return make_tuple(point, 0);
}
