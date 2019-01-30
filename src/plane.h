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
	Plane(Vector3f &p, Vector3f &n, Material &m);
	Plane(Vector3f &p1, Vector3f &p2, Vector3f &p3, Material &m);

	void translation(const Vector3f &transform);
	void rotateAboutX(float angle);
	void rotateAboutY(float angle);
	void rotateAboutZ(float angle);

	bool getIntersection(Ray3f &ray, float &param);
	tuple<float, Vector3f> distanceAlongRay(Ray3f &ray);

	void print();
};

#endif
