#ifndef RAY_H
#define RAY_H

#include <iostream>
#include "vector.h"

using namespace std;

class Ray3f{

public:

	Vector3f origin;
	Vector3f direction;

	Ray3f(){}
	void createRay(Vector3f &v1, Vector3f &v2, bool isNormalized) {
		if(!isNormalized){
			this->origin = v1; this->direction = (v2 - v1).normalizeIt();
		}
		else{
			this->origin = v1; this->direction = v2;

		}
	}

	// make a function to take t, and return Vector
	void print(){cout<<"[*] Ray: \n";
				cout<<"Origin: "; this->origin.print();
				cout<<"Direction: "; this->direction.print();}
};

#endif
