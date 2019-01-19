#include <iostream>
#include "vector.h"

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

Vector Vector::operator * (Vector const &vec){
	return Vector(x*vec.x, y*vec.y, z*vec.z);
}

void Vector::represent() const{
	cout<<x<<" "<<y<<" "<<z<<endl;
}

