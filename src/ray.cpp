#include <iostream>
#include <cmath>

#include "ray.h"
#include "vector.h"

using namespace std;

Ray::Ray(){
	Vector origin;
	Vector direction;
}

Ray::Ray(Vector &vec1, Vector &vec2){
	this->origin = vec1;
	double len = vec2.length();
	if(len != 1) this->direction = Vector(vec2.x/len, vec2.y/len, vec2.z/len);
}

void Ray::print(){
	cout<<"Origin: "<<origin.print()<<endl;
	cout<<"Direction: "<<direction.print()<<endl;
}

