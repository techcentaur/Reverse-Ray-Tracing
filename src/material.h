#ifndef MATERIAL_H
#define MATERIAL_H

#include <iostream>
#include "color.h"
using namespace std;

class Material{

public:
	Color3f diffuseColor;
	float specularReflectionExponent;
	float specularReflectionCoefficient;
	float diffuseReflectionCoefficient;

	Material(){}
	void fillColor(Color3f& col, float sExp, float sCoeff, float dCoeff) { 
		diffuseColor = col;
		specularReflectionExponent = sExp;
		specularReflectionCoefficient = sCoeff;
		diffuseReflectionCoefficient = dCoeff;
	}
	
	void print(){cout<<"[*] Material: "; diffuseColor.print();}
};

#endif
