#ifndef SPHERE_H
#define SPHERE_H 
#include "vector.h"

class Sphere{

public:
	double radius;
	Vector center;

	Sphere();
	Sphere(double, Vector &vec);

	Vector intersection(Ray &ray);
	void represent();

};

#endif