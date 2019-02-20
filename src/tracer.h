#ifndef TRACER_H
#define TRACER_H

#include <iostream>
#include <fstream>
#include <vector>
#include <limits>
#include <cmath>
#include <tuple>
#include  <typeinfo>
#include <cstring>

#include "color.h"
#include "object.h"
#include "vector.h"
#include "ray.h"
#include "material.h"
#include "light.h"
#include "camera.h"

using namespace std;

class Tracer{
public:
    float refractiveIndexOfMedium;
    vector<Vector3f> intersectionPointsOfARay;
    vector<Vector3f> normalPoints;
    float recursionDepth;
    Tracer(float rIndex=1.0){refractiveIndexOfMedium = rIndex;
    	recursionDepth = 4;
    }

    bool SceneRayCasting(Ray3f &ray, vector<Object*> objectList, Vector3f &iPoint, Vector3f &nVector, Material &iMaterial);
    Color3f RayCasting(Ray3f &ray, vector<Object*> objectList, vector<Light*> lSrcList, int depth);
    void writeImage(vector<Object*> objectList, vector<Light*> lightSourcesList, string fileName, Camera &cam, bool antiAliasing);
	vector<vector<Vector3f>> getIntersectionPointsOfARay(vector<Object*> objects, vector<Light*> lights, Camera &cam, int i, int j);


};

#endif