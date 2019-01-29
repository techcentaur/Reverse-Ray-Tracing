#include <iostream>
#include <cmath>

#include "color.h"

using namespace std;

Color3f::Color3f(){}

Color3f::Color3f(float r, float g, float b) {this->r = r; this->g = g; this->b = b;}
Color3f::Color3f(const Color3f &col) {this->r=col.r; this->g=col.g; this->b=col.b;}

Color3f Color3f::operator * (float f) {return Color3f(r*f, g*f, b*f);}	
Color3f Color3f::operator * (const Color3f &col){
	return Color3f(r*col.r, g*col.g, b*col.b);
}
Color3f Color3f::operator + (const Color3f &col){
	return Color3f(r+col.r, g+col.g, b+col.b);
}
void Color3f::operator += (const Color3f &col){
	r = r+col.r; g = g+col.g; b = b+col.b;
}
void Color3f::operator /= (const float f){
	r = r/f; g = g/f; b = b/f;
}


void Color3f::print(){cout<<"[*] Color: "<<"("<<r<<", "<<g<<", "<<b<<")"<<endl;}
