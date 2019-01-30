#ifndef BOX_H
#define BOX_H 

#include <tuple>
#include <vector>
#include "vector.h"
#include "ray.h"
#include "material.h"
#include "plane.h"

class Box{

public:
	float lenA,lenB,lenC;
	Vector3f point;
	Vector3f dirA, dirB, dirC;
	Vector3f dirA_, dirB_, dirC_;
	
	Material material;


	Box();
	// Box with edges aligned to x,y,z. Point p is origin of the box?
          Box(float la, float lb, float lc, Vector3f &p, Material &m);


	
	void getFaces();
	
	tuple<Vector3f, bool> getIntersection(Ray3f &ray, float &t);
	tuple<Vector3f, bool> getFaceIntersection(Ray3f &ray, Plane &f, float b1, float b1_, float b2, float b2_, float &t);
	
	void print();

};

#endif