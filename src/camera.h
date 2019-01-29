#ifndef CAMERA_H
#define CAMERA_H

#include <iostream>
#include <cmath>

#include "ray.h"
#include "vector.h"

using namespace std;

class Camera {
public:
    Vector3f origin;
    Vector3f BottomLeftCorner;
    Vector3f horizontal;
    Vector3f vertical;

    Camera(Vector3f lookFrom, Vector3f lookAt, Vector3f viewUp, float verticalFOV, float aspect){
        Vector3f u, v, w;

        float theta = verticalFOV*M_PI/180; //degree to radian

        float heightHalf = tan(theta/2);
        float widthHalf = aspect * heightHalf;

        origin = lookFrom;
        
        w = (lookFrom - lookAt).normalizeIt();
        u = (viewUp.cross(viewUp, w)).normalizeIt();
        v = w.cross(w, u);
        
        BottomLeftCorner = origin - u*widthHalf - v*heightHalf - w;
        horizontal = u*(2*widthHalf);
        vertical = v*(2*heightHalf);
    }

    Ray3f getRay(float x, float y) {
        Vector3f temp = (BottomLeftCorner + horizontal*x + vertical*y - origin).normalizeIt();
        Ray3f newRay;
        newRay.createRay(origin, temp, true);
        return newRay; 
    }

};
#endif


