#include <iostream>
#include "vector.h"
#include "matrix.h"
#include "transformation.h"
#include <vector>
#include <cmath>
using namespace std;

int main(){
	float x,y,z;
	x=5;
	y=6;
	z=2;
	Vector3f v(x,y,z);
	Vector3f t(3.f,0.f,1.f);
	
	Matrix tmatrix;
          tmatrix.mat[0][0] = t.x;
          tmatrix.mat[1][1] = t.y;
          tmatrix.mat[2][2] = t.z;

	Matrix vmatrix(v);
	
          // Vector3f ans = (tmatrix * vmatrix).toVector3f();
	// tmatrix.print();
	// vmatrix.print();
	Vector3f ans(v * t);
	ans.print();
	// ans.print();
	return 1;
}