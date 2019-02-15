#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H

#include "vector.h"

using namespace std;

class Transformation{
          public:
                    Transformation();
                    Vector3f translation(const Vector3f &v, const Vector3f &translation);
                    
                    Vector3f scaling(const Vector3f &v, const Vector3f &scaling);
                    
                    Vector3f rotateAboutX(const Vector3f &v, float angle);
                    Vector3f rotateAboutY(const Vector3f &v, float angle);
                    Vector3f rotateAboutZ(const Vector3f &v, float angle);
                    
                    Vector3f shearingXAboutY(const Vector3f &v, float xy);
                    Vector3f shearingYAboutX(const Vector3f &v, float yx);
                    Vector3f shearingXAboutZ(const Vector3f &v, float xz);
                    Vector3f shearingZAboutX(const Vector3f &v, float zx);
                    Vector3f shearingYAboutZ(const Vector3f &v, float yz);
                    Vector3f shearingZAboutY(const Vector3f &v, float zy);
};

#endif
