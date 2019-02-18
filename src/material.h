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
	float refractiveIndex;

	Material(){}
	void fillColor(Color3f& col, float sExp, float sCoeff, float dCoeff, float reflecCoeff=0, float refracCoeff=0, float rIndex=1) { 
		diffuseColor = col;
		specularReflectionExponent = sExp;
		specularReflectionCoefficient = sCoeff;
		diffuseReflectionCoefficient = dCoeff;
		reflectionCoefficient = reflecCoeff;
		refractionCoefficient = refracCoeff;
		refractiveIndex = rIndex;
	}
	
	void changeColor(Color3f& c){
		diffuseColor = c;
	}

	void print(){cout<<"[*] Material: "; diffuseColor.print();
	cout<<"specularReflectionExponent: "<<specularReflectionExponent<<endl;
	cout<<"specularReflectionCoefficient: "<<specularReflectionCoefficient<<endl;
	cout<<"diffuseReflectionCoefficient: "<<diffuseReflectionCoefficient<<endl;
	cout<<"reflectionCoefficient: "<<reflectionCoefficient<<endl;
	cout<<"refractionCoefficient: "<<refractionCoefficient<<endl;
	cout<<"refractiveIndex: "<<refractiveIndex<<endl;

	}
};

#endif
