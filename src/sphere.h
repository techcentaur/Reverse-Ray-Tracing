#ifndef SPHERE_H
#define SPHERE_H 
#include "vector.h"

class Sphere{

public:
	double radius;
	Vector center;

	Sphere();
	Sphere(double, Vector &vec);

	double getNormal(Vector const &vec);
	Vector getIntersection(Ray &ray);

	void print();

};

#endif