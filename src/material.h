#ifndef MATERIAL_H
#define MATERIAL_H

#include <iostream>
#include "color.h"
using namespace std;

class Material{

public:
	Color3f diffuseColor;
	float specularReflectionExponent;

	Material(){}
	void fillColor(Color3f& col, float exp) { diffuseColor = col; specularReflectionExponent = exp;}
	void print(){cout<<"[*] Material: "; diffuseColor.print();}
};

#endif
