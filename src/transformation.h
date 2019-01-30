#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H

#include "vector.h"

using namespace std;

class Transformation{
          public:
                    Transformation();
                    Vector3f translation(const Vector3f &v, const Vector3f &transform);
                    Vector3f scaling(const Vector3f &v, const Vector3f &transform);
                    Vector3f rotateAboutX(const Vector3f &v, float angle);
                    Vector3f rotateAboutY(const Vector3f &v, float angle);
                    Vector3f rotateAboutZ(const Vector3f &v, float angle);
          
};

#endif
