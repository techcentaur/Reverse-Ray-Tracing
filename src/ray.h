#ifndef RAY_H
#define RAY_H

#include <iostream>
#include "vector.h"

using namespace std;

class Ray3f{

public:

	Vector3f origin;
	Vector3f direction;

	Ray3f() {}
	Ray3f(Vector3f &v1, Vector3f &v2) {origin = v1; direction = v2;}

	// make a function to take t, and return Vector
	void print(){cout<<"[*] Ray: "; origin.print(); direction.print();}

};

#endif
