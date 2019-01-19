#include <iostream>
#include "vector.h"
#include <cmath>
using namespace std;

Vector::Vector(){
	x=0; y=0; z=0;
}

Vector::Vector(double value){
	x = value; y = value; z = value;
}

Vector::Vector(double valx, double valy, double valz){
	x = valx; y = valy; z = valz;
}


Vector Vector::operator * (double d){
	return Vector(x*d, y*d, z*d);
}
Vector Vector::operator + (double d){
	return Vector(x+d, y+d, z+d);
}


Vector Vector::operator * (Vector &vec){
	return Vector(x*vec.x, y*vec.y, z*vec.z);
}

Vector Vector::operator + (Vector &vec){
	return Vector(x+vec.x, y+vec.y, z+vec.z);
}
bool Vector::operator == (Vector &vec){
	return (((*this)-vec).length() == 0);
	// would it be perfectly zero (floating shit)?
}


double Vector::length(){
	return sqrt(dot(*this));
}
double Vector::lengthSquare(){
	return dot(*this);
}
double Vector::dot(Vector &vec){
	return x*vec.x + y*vec.y + z*vec.z;
}


void Vector::represent(){
	cout<<"x: "<<x<<" y: "<<y<<" z: "<<z<<endl;
}

