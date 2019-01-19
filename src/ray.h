#ifndef RAY_H
#define RAY_H
#endif
#include "vector.h"

class Ray{

public:
	Vector origin, direction;

	Ray();
	Ray(Vector, Vector);

	double dot(Ray &r);

	void represent();
}