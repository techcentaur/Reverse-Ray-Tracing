#include <iostream>
#include "vector.h"
#include "matrix.h"
#include "transformations.h"
#include <vector>
#include <cmath>
using namespace std;

int main(){
	float x,y,z;
	x=5;
	y=6;
	z=2;
	Vector3f v(x,y,z);
	Vector3f t(1.f,1.f,1.f);
	Matrix m(v);
	// Matrix m2;

	// Matrix m4(m2*m);
	m.toVector3f().print();
	return 1;
}