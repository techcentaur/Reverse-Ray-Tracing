#include<iostream>
#include "transformations.h"

#include "matrix.h"

using namespace std;

Vector3f Transformations::translation(const Vector3f &initial, const Vector3f &transform){
          Matrix tmatrix;
          tmatrix.mat[0][3] = transform.x;
          tmatrix.mat[1][3] = transform.y;
          tmatrix.mat[2][3] = transform.z;
          return (tmatrix * initial).toVector3f();
}
