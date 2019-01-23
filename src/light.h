#ifndef LIGHT_H
#define LIGHT_H

#include <iostream>
#include "vector.h"

using namespace std;

class Light{

public:
	float intensity;
	Vector3f source;

	Light();
	Light(Vector3f &src, float i);
	void print();

};

#endif
