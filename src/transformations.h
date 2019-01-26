#ifndef TRANSFORMATIONS_H
#define TRANSFORMATIONS_H

#include "vector.h"

using namespace std;

class Transformations{
          public:
                    Vector3f translation(const Vector3f &initial, const Vector3f &transform);
                    Vector3f scaling(Vector3f, Vector3f);
                    Vector3f rotation(Vector3f, Vector3f);
          
};

#endif
