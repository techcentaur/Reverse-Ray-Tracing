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
    float recursionDepth;
    float width;
    float height;
    float superSampling;
    float fov;

    Camera(){};

    void formCamera(Vector3f lookFrom, Vector3f lookAt, Vector3f viewUp, float verticalFOV, float wid, float h, float sSampling, float rD){
        Vector3f u, v, w;

        this->width=wid;
        this->height=h;
        this->recursionDepth = rD;
        this->superSampling = sSampling;
        this->fov = verticalFOV;

        float theta = verticalFOV*M_PI/180; //degree to radian

        float aspect = float(wid)/float(h);
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

    void print(){
    cout<<"recursionDepth: "<<recursionDepth<<endl;
    cout<<"width: "<<width<<endl;
    cout<<"height: "<<height<<endl;
    cout<<"superSampling: "<<superSampling<<endl;
    cout<<"fov"<<fov<<endl;
    }

};
#endif


