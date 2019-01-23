#ifndef COLOR_H
#define COLOR_H

#include <iostream>
using namespace std;

class Color3f{

public:
	float r, g, b;

	Color3f() {}
	Color3f(float r, float g, float b) {this->r = r; this->g = g; this->b = b;}
	Color3f(Color3f& col){r=col.r; g=col.g; b=col.b;}

	Color3f operator * (float f) {r=r*f; g=g*f; b=b*f; return *this;}
	void print(){cout<<"[*] Color: "<<"("<<r<<", "<<g<<", "<<b<<")"<<endl;}

};

#endif
