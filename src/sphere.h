#ifndef SPHERE_H
#define SPHERE_H 

#include <tuple>
#include "vector.h"
#include "ray.h"

class Sphere{

public:
	float radius;
	Vector3f center;

	Sphere();
	~Sphere();
	
	Sphere(float radius, Vector3f &vec);

	tuple<Vector3f, int> getIntersection(Ray3f &ray, float &t);

	void print();

};

#endif