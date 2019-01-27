#ifndef PLANE_H
#define PLANE_H

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

	bool getIntersection(Ray3f &ray);
	tuple<float, Vector3f> distanceAlongRay(Ray3f &ray);

	void print();
};

#endif
