#ifndef COLOR_H
#define COLOR_H

#include <iostream>
using namespace std;

class Color3f{

public:
	float r, g, b;

	Color3f();
	Color3f(float r, float g, float b);
	Color3f(const Color3f &col);

	Color3f operator * (float f);	
	Color3f operator * (const Color3f &col);
	Color3f operator + (const Color3f &col);
	void operator += (const Color3f &col);
	void operator /= (const float f);

	void print();

};

#endif
