#include<iostream>
#include <cmath>

#include "transformation.h"
#include "matrix.h"

using namespace std;

Vector3f Transformation::translation(const Vector3f &v, const Vector3f &transform){
          // Traditional Way
          Matrix tmatrix;
          Matrix vmatrix(v);
          tmatrix.mat[0][3] = transform.x;
          tmatrix.mat[1][3] = transform.y;
          tmatrix.mat[2][3] = transform.z;
          return (tmatrix * vmatrix).toVector3f();
        
          // Direct Way
          // Vector3f t = (v + transform);
          // return t;
}

Vector3f Transformation::scaling(const Vector3f &v, const Vector3f &transform){
          // Traditional Way
          Matrix tmatrix;
          Matrix vmatrix(v);
          tmatrix.mat[0][0] = transform.x;
          tmatrix.mat[1][1] = transform.y;
          tmatrix.mat[2][2] = transform.z;
          return (tmatrix * vmatrix).toVector3f();

          // Direct Way
          // Vector3f t = (v * transform);
          // return t;
}

Vector3f Transformation::rotateAboutX(const Vector3f &v, float angle){
          Matrix tmatrix;
          Matrix vmatrix(v);
          tmatrix.mat[0][0] = cos(angle);
          tmatrix.mat[1][1] = cos(angle);
          tmatrix.mat[0][1] = -sin(angle);
          tmatrix.mat[1][0] = sin(angle);
          return (tmatrix * vmatrix).toVector3f();
}
Vector3f Transformation::rotateAboutY(const Vector3f &v, float angle){
          Matrix tmatrix;
          Matrix vmatrix(v);
          tmatrix.mat[0][0] = cos(angle);
          tmatrix.mat[2][2] = cos(angle);
          tmatrix.mat[2][0] = -sin(angle);
          tmatrix.mat[0][2] = sin(angle);
          return (tmatrix * vmatrix).toVector3f();
}
Vector3f Transformation::rotateAboutZ(const Vector3f &v, float angle){
          Matrix tmatrix;
          Matrix vmatrix(v);
          tmatrix.mat[1][1] = cos(angle);
          tmatrix.mat[2][2] = cos(angle);
          tmatrix.mat[1][2] = -sin(angle);
          tmatrix.mat[2][1] = sin(angle);
          return (tmatrix * vmatrix).toVector3f();
}