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
Vector Vector::operator - (Vector &vec){
	return Vector(x-vec.x, y-vec.y, z-vec.z);
}
Vector Vector::operator / (Vector &vec){
	if (vec.x==0 || vec.y==0 || vec.z==0){
		//raise divideByZeroError here
	}
	return Vector(x/vec.x, y/vec.y, z/vec.z);
}

bool Vector::operator == (Vector &vec){
	return (((*this)-vec).length() == 0);
}
Vector& Vector::operator+=(const Vector &vec){
	x += vec.x; y += vec.y; z += vec.z;
	return *this;
}
Vector& Vector::operator*=(const Vector &vec){
	x += vec.x; y += vec.y; z += vec.z;
	return *this;
} 


double Vector::length(){
	return sqrt((*this).lengthSquare());
}
double Vector::lengthSquare(){
	return (*this).dot(*this);
}
double Vector::dot(Vector &vec){
	return x*vec.x + y*vec.y + z*vec.z;
}

Vector Vector::cross(Vector &vec1, Vector &vec2){
	return Vector((vec1.y * vec2.z - vec1.z * vec2.y),
		(-(vec1.x * vec2.z - vec1.z * vec2.x)),
		(vec1.x * vec2.y - vec1.y * vec2.x));
}
void Vector::normalize(){
	double len = (*this).length();
	this->x = x/len;
	this->y = y/len;
	this->z = z/len;
}

Vector Vector::normalizeIt(Vector &vec){
	double len = vec.length();
	vec.x = vec.x/len;
	vec.y = vec.y/len;
	vec.z = vec.z/len;
}

void Vector::print(){
	cout<<"("<<x<<", "<<y<<", "<<z<<")"<<endl;
}

int main(){

}