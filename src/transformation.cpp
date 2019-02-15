#include<iostream>
#include <cmath>

#include "transformation.h"
#include "matrix.h"

using namespace std;

Transformation::Transformation(){};

Vector3f Transformation::translation(const Vector3f &v, const Vector3f &translation){
          // Traditional Way
          Matrix tmatrix;
          Matrix vmatrix(v);
          tmatrix.mat[3][0] = translation.x;
          tmatrix.mat[3][1] = translation.y;
          tmatrix.mat[3][2] = translation.z;
          return (tmatrix * vmatrix).toVector3f();
        
          // Direct Way
          // Vector3f t = (v + transform);
          // return t;
}

Vector3f Transformation::scaling(const Vector3f &v, const Vector3f &scaling){
          // Traditional Way
          Matrix tmatrix;
          Matrix vmatrix(v);
          tmatrix.mat[0][0] = scaling.x;
          tmatrix.mat[1][1] = scaling.y;
          tmatrix.mat[2][2] = scaling.z;
          return (tmatrix * vmatrix).toVector3f();

          // Direct Way
          // Vector3f t = (v * transform);
          // return t;
}

Vector3f Transformation::rotateAboutX(const Vector3f &v, float angle){
          float a = M_PI * angle / 180;
          Matrix tmatrix;
          Matrix vmatrix(v);
          tmatrix.mat[1][1] = cos(a);
          tmatrix.mat[2][2] = cos(a);
          tmatrix.mat[1][2] = sin(a);
          tmatrix.mat[2][1] = -sin(a);
          return (tmatrix * vmatrix).toVector3f();
}

Vector3f Transformation::rotateAboutY(const Vector3f &v, float angle){
          float a = M_PI * angle / 180;
          Matrix tmatrix;
          Matrix vmatrix(v);
          tmatrix.mat[0][0] = cos(a);
          tmatrix.mat[2][2] = cos(a);
          tmatrix.mat[2][0] = sin(a);
          tmatrix.mat[0][2] = -sin(a);
          return (tmatrix * vmatrix).toVector3f();
}

Vector3f Transformation::rotateAboutZ(const Vector3f &v, float angle){
          float a = M_PI * angle / 180;
          Matrix tmatrix;
          Matrix vmatrix(v);
          tmatrix.mat[0][0] = cos(a);
          tmatrix.mat[1][1] = cos(a);
          tmatrix.mat[0][1] = sin(a);
          tmatrix.mat[1][0] = -sin(a);
          return (tmatrix * vmatrix).toVector3f();
}

Vector3f Transformation::shearingXAboutY(const Vector3f &v, float xy){
          Matrix tmatrix;
          Matrix vmatrix(v);
          tmatrix.mat[1][0] = xy;
          return (tmatrix * vmatrix).toVector3f();
}

Vector3f Transformation::shearingYAboutX(const Vector3f &v, float yx){
          Matrix tmatrix;
          Matrix vmatrix(v);
          tmatrix.mat[0][1] = yx;
          return (tmatrix * vmatrix).toVector3f();
}

Vector3f Transformation::shearingXAboutZ(const Vector3f &v, float xz){
          Matrix tmatrix;
          Matrix vmatrix(v);
          tmatrix.mat[2][0] = xz;
          return (tmatrix * vmatrix).toVector3f();
}

Vector3f Transformation::shearingZAboutX(const Vector3f &v, float zx){
          Matrix tmatrix;
          Matrix vmatrix(v);
          tmatrix.mat[0][2] = zx;
          return (tmatrix * vmatrix).toVector3f();
}

Vector3f Transformation::shearingZAboutY(const Vector3f &v, float zy){
          Matrix tmatrix;
          Matrix vmatrix(v);
          tmatrix.mat[1][2] = zy;
          return (tmatrix * vmatrix).toVector3f();
}

Vector3f Transformation::shearingYAboutZ(const Vector3f &v, float yz){
          Matrix tmatrix;
          Matrix vmatrix(v);
          tmatrix.mat[2][1] = yz;
          return (tmatrix * vmatrix).toVector3f();
}