#ifndef OBJECT_H
#define OBJECT_H 

#include <tuple>
#include <vector>
#include "vector.h"
#include "ray.h"
#include "material.h"

using namespace std;

class Object{

public:
	Material material;
	
	Object(Material &m);
	virtual bool getIntersection(Ray3f &ray, float &t, Vector3f &nVector) = 0;
	virtual void print() = 0;
	virtual Vector3f getNormalOnIntersectionPoint(Vector3f &point, Ray3f &ray) = 0;

};

class Sphere : public Object {

public:
	float radius;
	Vector3f center;
	Vector3f intersectionPointIfRefracted;

	Sphere();	
	Sphere(float radius, Vector3f &vec, Material &m);

	bool getIntersection(Ray3f &ray, float &t, Vector3f &nVector);
	Vector3f getNormalOnIntersectionPoint(Vector3f &point, Ray3f &ray);

	void print();
};

class Plane : public Object {

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
	tuple<float, Vector3f> distanceAlongRay(Ray3f &ray);

	void translation(const Vector3f &transform);
	void rotateAboutX(float angle);
	void rotateAboutY(float angle);
	void rotateAboutZ(float angle);

	void print();
};

#endif