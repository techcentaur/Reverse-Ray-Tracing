#include <iostream>
#include <cmath>

#include "vector.h"
#include "light.h"

using namespace std;

Light::Light(){
}

Light::Light(Vector3f &src, float i){
	source = src; intensity = i;
}

void Light::print(){
	cout<<"[*] Light: \n";
	cout<<"Source: "; source.print();
	cout<<"Intensity: "<<intensity;
}