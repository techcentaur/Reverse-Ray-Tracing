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
	Plane(Vector3f &p, Vector3f &n, Material &m);
	Plane(Vector3f &p1, Vector3f &p2, Vector3f &p3, Material &m);

	bool getIntersection(Ray3f &ray, float &t);
	Vector3f getNormalOnIntersectionPoint(Vector3f &point, Ray3f &ray);
	void print();

	// void translation(const Vector3f &transform);
	// void rotateAboutX(float angle);
	// void rotateAboutY(float angle);
	// void rotateAboutZ(float angle);

};


class Box : public Object{

public:
	// float lenA,lenB,lenC;
	// Vector3f point;
	// Vector3f dirA, dirB, dirC;
	// Vector3f dirA_, dirB_, dirC_;
	Vector3f recentNormal;
	vector<Plane> planes;
	vector<Vector3f> boundPoints;
	vector<Vector3f> vertices;
	
	Box();
	Box(Vector3f &translate, Vector3f &scale, Material &m);
	
	bool getIntersection(Ray3f &ray, float &t);
	Vector3f getNormalOnIntersectionPoint(Vector3f &point, Ray3f &ray);
	
	void print();

};


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