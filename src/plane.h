#ifndef PLANE_H
#define PLANE_H

#include <iostream>
#include "vector.h"
#include "ray.h"
#include "material.h"
#include "color.h"
#include <tuple>
#include <vector>

class Plane{

public:
	Vector3f point;
	Vector3f normal;
	Material material;
	vector<float> bounds;

	Plane();
	Plane(const Plane &p);
	Plane(Vector3f &p, Vector3f &n, Material &m, vector<float> b);
	Plane(Vector3f &p1, Vector3f &p2, Vector3f &p3, Material &m, vector<float> b);

	bool getIntersection(Ray3f &ray, float &param);
	Vector3f getNormalOnIntersectionPoint(Vector3f &point, Ray3f &ray);

	void translation(const Vector3f &vec);
	void rotateAboutX(float angle);
	void rotateAboutY(float angle);
	void rotateAboutZ(float angle);

	void print();
};

#endif
