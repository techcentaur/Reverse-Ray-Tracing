#ifndef OBJECT_H
#define OBJECT_H 

#include <tuple>
#include "vector.h"
#include "ray.h"
#include "material.h"

using namespace std;

class Object{

public:
	Material material;
	
	Object(Material &m);
	virtual bool getIntersection(Ray3f &ray, float &t) = 0;
	virtual void print() = 0;
};

class Sphere : public Object {

public:
	float radius;
	Vector3f center;

	Sphere();	
	Sphere(float radius, Vector3f &vec, Material &m);

	bool getIntersection(Ray3f &ray, float &t);
	void print();
};

#endif