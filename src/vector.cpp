#include <iostream>
#include "vector.h"
#include <cmath>
using namespace std;

Vector3f::Vector3f(){
	x=0; y=0; z=0;
}
Vector3f::Vector3f(const Vector3f &v){
	x = v.x; y=v.y; z=v.z;
}
Vector3f::Vector3f(float u, float v, float w){
	x = u; y = v; z = w;
}

// void Vector3f::operator = (const Vector3f &vec){
// 	x = vec.x; y=vec.y; z=vec.z;
// }
Vector3f Vector3f::operator * (float d){
	return Vector3f(x*d, y*d, z*d);
}
Vector3f Vector3f::operator + (float d){
	return Vector3f(x+d, y+d, z+d);
}
Vector3f Vector3f::operator * (const Vector3f &vec){
	return Vector3f(x*vec.x, y*vec.y, z*vec.z);
}
Vector3f Vector3f::operator + (const Vector3f &vec){
	return Vector3f(x+vec.x, y+vec.y, z+vec.z);
}
Vector3f Vector3f::operator - (const Vector3f &vec){
	return Vector3f(x-vec.x, y-vec.y, z-vec.z);
}

Vector3f Vector3f::operator / (const Vector3f &vec){
	if (vec.x==0 || vec.y==0 || vec.z==0){
		//raise divideByZeroError here
	}
	return Vector3f(x/vec.x, y/vec.y, z/vec.z);
}

bool Vector3f::operator == (const Vector3f &vec){
	return (((*this)-vec).length() == 0);
}
Vector3f& Vector3f::operator+=(const Vector3f &vec){
	x += vec.x; y += vec.y; z += vec.z;
	return *this;
}
Vector3f& Vector3f::operator*=(const Vector3f &vec){
	x *= vec.x; y *= vec.y; z *= vec.z;
	return *this;
}

Vector3f Vector3f::operator = (const Vector3f &vec){
	return Vector3f(vec.x, vec.y, vec.z);
}

float Vector3f::length(){
	return sqrt((*this).lengthSquare());
}

float Vector3f::lengthFrom(const Vector3f &vec){
	return sqrt(fabs(pow(this->x - vec.x, 2) + pow(this->y - vec.y, 2) + pow(this->z - vec.z, 2)));
}

float Vector3f::lengthSquare(){
	return (*this).dot(*this);
}
float Vector3f::dot(const Vector3f &vec){
	return x*vec.x + y*vec.y + z*vec.z;
}

Vector3f Vector3f::cross(const Vector3f &vec1, const Vector3f &vec2){
	return Vector3f((vec1.y * vec2.z - vec1.z * vec2.y),
		(-(vec1.x * vec2.z - vec1.z * vec2.x)),
		(vec1.x * vec2.y - vec1.y * vec2.x));
}

void Vector3f::normalize(){
	float len = (*this).length();
	this->x = x/len;
	this->y = y/len;
	this->z = z/len;
}

Vector3f Vector3f::normalizeIt(){
	float len = (*this).length();
	this->x = x/len;
	this->y = y/len;
	this->z = z/len;
	return *this;
}

void Vector3f::print(){
	cout<<"[*] Vector: ";
	cout<<"("<<x<<", "<<y<<", "<<z<<")"<<endl;
}
