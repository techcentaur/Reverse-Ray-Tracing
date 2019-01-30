#ifndef BOX_H
#define BOX_H 

#include <tuple>
#include "vector.h"
#include "ray.h"
#include "material.h"

class Box{

public:
	Material material;

	float a,b,c;
          // Vector3f dirA, dirB, dirC;
          Vector3f center;

	Box();	
          // Box(float a, float b, float c, Vector3f &dirA, Vector3f &center, Material &m);
          Box(float a, float b, float c, Vector3f &center, Material &m);

	tuple<Vector3f, bool> getIntersection(Ray3f &ray, float &t);

	void print();

};

#endif