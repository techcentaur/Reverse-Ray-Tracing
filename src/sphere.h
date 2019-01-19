#ifndef SPHERE_H
#define SPHERE_H
#include <vector> 
#include "vector.h"

class Sphere{

public:
	double radius;
	Vector center;

	Sphere();
	Sphere(double, Vector &vec);

	vector<Vector> intersection(Ray &ray)
	void represent();

};

#endif