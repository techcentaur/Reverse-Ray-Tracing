#ifndef SPHERE_H
#define SPHERE_H 

#include <tuple>
#include "vector.h"
#include "ray.h"
#include "material.h"

class Sphere{

public:
	float radius;
	Vector3f center;
	Material material;

	Sphere();	
	Sphere(float radius, Vector3f &vec, Material &m);

	tuple<Vector3f, bool> getIntersection(Ray3f &ray, float &t);

	void print();

};

#endif