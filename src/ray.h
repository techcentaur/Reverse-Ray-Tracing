#ifndef RAY_H
#define RAY_H

#include "vector.h"

class Ray{

public:
	Vector origin, direction;

	Ray();
	Ray(Vector &vec1, Vector &vec2);
	
	void print();
};

#endif
