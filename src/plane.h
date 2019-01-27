#ifndef PLANE_H
#define PLANE_H

<<<<<<< HEAD
#include <iostream>
#include "vector.h"
#include "ray.h"
#include "material.h"
#include "color.h"
#include <tuple>

class Plane{

public:
	Vector3f point;
	Vector3f normal;
	Material material;

	Plane();
	Plane(Vector3f &p1, Vector3f &p2, Vector3f &p3, Material &m);
=======
#include "vector.h"
class Plane{

public:
	double distance; //distance from origin
	Vector3f normal; //in normalized form
>>>>>>> d5d83672d1c6227363bb2c8763466fdda444ef50

	bool getIntersection(Ray3f &ray);
	tuple<float, Vector3f> distanceAlongRay(Ray3f &ray);

	void print();
};

<<<<<<< HEAD
=======
};
>>>>>>> d5d83672d1c6227363bb2c8763466fdda444ef50
#endif
