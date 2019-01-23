#ifndef MATERIAL_H
#define MATERIAL_H

#include <iostream>
#include "color.h"
using namespace std;

class Material{

public:
	Color3f diffuseColor;
	
	Material(){}
	void fillColor(Color3f& col) { diffuseColor = col; }
	void print(){cout<<"[*] Material: "; diffuseColor.print();}
};

#endif
