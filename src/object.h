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
	virtual bool getIntersection(Ray3f &ray, float &t) = 0;
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

	bool getIntersection(Ray3f &ray, float &t);
	Vector3f getNormalOnIntersectionPoint(Vector3f &point, Ray3f &ray);

	void print();
};

class Plane : public Object {

public:
	Vector3f point;
	Vector3f normal;
	// vector<float> bounds;
	
	Plane();
	// Plane(Vector3f &p, Vector3f &n, Material &m, vector<float> b);
	Plane(Vector3f &p1, Vector3f &p2, Vector3f &p3, Material &m);

	bool getIntersection(Ray3f &ray, float &t);
	Vector3f getNormalOnIntersectionPoint(Vector3f &point, Ray3f &ray);
	void print();

	// void translation(const Vector3f &transform);
	// void rotateAboutX(float angle);
	// void rotateAboutY(float angle);
	// void rotateAboutZ(float angle);

};

// class Box : public Object{

// public:
// 	float lenA,lenB,lenC;
// 	Vector3f point;
// 	Vector3f dirA, dirB, dirC;
// 	Vector3f dirA_, dirB_, dirC_;
	
// 	Material material;

// 	Box();
// 	// Box with edges aligned to x,y,z. Point p is origin of the box?
// 	  Box(float la, float lb, float lc, Vector3f &p, Material &m);

// 	void getFaces();
	
// 	tuple<Vector3f, bool> getIntersection(Ray3f &ray, float &t);
// 	tuple<Vector3f, bool> getFaceIntersection(Ray3f &ray, Plane &f, float b1, float b1_, float b2, float b2_, float &t);
	
// 	void print();

// };


class Cone : public Object{
public:
	Vector3f center;
	Vector3f upVector;
	float alpha;
	float radius;
	float height;

	Cone();
	Cone(Vector3f c, Vector3f uV, float a, float h, Material &m);

	bool getIntersection(Ray3f &ray, float &t);
	Vector3f getNormalOnIntersectionPoint(Vector3f &point, Ray3f &ray);
	
	void print();

};



#endif