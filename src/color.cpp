#include <iostream>
#include <cmath>

#include "color.h"

using namespace std;

Color3f::Color3f(){}

Color3f::Color3f(float r, float g, float b) {this->r = r; this->g = g; this->b = b;}
Color3f::Color3f(const Color3f &col) {this->r=col.r; this->g=col.g; this->b=col.b;}

Color3f Color3f::operator * (float f) {return Color3f(r*f, g*f, b*f);}	

void Color3f::print(){cout<<"[*] Color: "<<"("<<r<<", "<<g<<", "<<b<<")"<<endl;}
