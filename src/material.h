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
	float reflectionCoefficient;
	float refractionCoefficient;

	Material(){}
	void fillColor(Color3f& col, float sExp, float sCoeff, float dCoeff, float reflecCoeff=0, float refracCoeff=0) { 
		diffuseColor = col;
		specularReflectionExponent = sExp;
		specularReflectionCoefficient = sCoeff;
		diffuseReflectionCoefficient = dCoeff;
		reflectionCoefficient = reflecCoeff;
		refractionCoefficient = refracCoeff;
	}
	
	void print(){cout<<"[*] Material: "; diffuseColor.print();}
};

#endif
