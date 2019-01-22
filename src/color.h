#ifndef COLOR_H
#define COLOR_H

#include <iostream>
using namespace std;

class Color3f{

public:
	float r, g, b;

	Color3f() {r=0; g=0; b=0;}
	Color3f(float r, float g, float b) {this->r = r; this->g = g; this->b = b;}

	Color3f operator * (float f) {r=r*f; g=g*f; b=b*f; return *this;}
	void print(){cout<<"("<<r<<", "<<g<<", "<<b<<")"<<endl;}

};

#endif
