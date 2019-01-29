 // Main ray tracer

#include <iostream>
#include <fstream>
#include <vector>
#include <limits>
#include <cmath>
#include <tuple>
#include  <typeinfo>

#include "tracer.h"
#include "color.h"
#include "object.h"
#include "vector.h"
#include "ray.h"
#include "material.h"
#include "light.h"

using namespace std;


bool Tracer::SceneRayCasting(Ray3f &ray, vector<Object*> objectList, Vector3f &iPoint, Vector3f &nVector, Material &iMaterial){
    float maxDistance = numeric_limits<float>::max();

    float closestIntersection;
    for(int i=0; i<objectList.size(); i++){
        bool temp = objectList.at(i)->getIntersection(ray, closestIntersection);

        if(temp && closestIntersection < maxDistance){
            maxDistance = closestIntersection;
            // don't need intersection point and normal vector: Fuunction will do it (call by reference)
            // iPoint = ray.origin + ray.direction*closestIntersection;
            // nVector = (iPoint - objectList.at(i)->center).normalizeIt();

            iMaterial = objectList.at(i)->material;
        }
    }

    return maxDistance < 5000;
}

Color3f Tracer::RayCasting(Ray3f &ray, vector<Object*> objectList, vector<Light*> lSrcList, int depth=0){

    Vector3f iPoint, nVector;
    Material iMaterial;

    bool temp = SceneRayCasting(ray, objectList, iPoint, nVector, iMaterial);

    if(!temp || depth > 2){
        Color3f c1(0.2, 0.7, 0.7);
        return c1;
    }

    // reflected ray recursive function
    Vector3f reflectionVector = ((nVector*(2.f*((ray.direction).dot(nVector)))) - ray.direction).normalizeIt();
    Vector3f reflectedPoint;
    if(reflectionVector.dot(nVector) < 0) reflectedPoint = iPoint - nVector*1e-3;
    else reflectedPoint = iPoint + nVector*1e-3;

    Ray3f reflectedRay;
    reflectedRay.createRay(reflectedPoint, reflectionVector, true);
    Color3f reflectedSurfaceColor = RayCasting(reflectedRay, objectList, lSrcList, depth+1);


    // refracted ray recursive function
    float eta = this->refractiveIndexOfMedium/iMaterial.refractiveIndex;
    float costheta1 = max(-1.f, min(1.f, ray.direction.dot(nVector)));
    float sintheat2 = max(-1.f, min(1.f, eta*costheta1));

    Vector3f refractedVector = ((ray.direction)*eta + nVector*(costheta1*eta - sqrtf(1 - (sintheat2*sintheat2)))).normalizeIt();

    Vector3f refractedPoint;
    if(refractedVector.dot(nVector) < 0) refractedPoint = iPoint - nVector*1e-3 ;
    else refractedPoint = iPoint + nVector*1e-3;

    Ray3f refractedRay;
    refractedRay.createRay(refractedPoint, refractedVector, true);
    Color3f refractedSurfaceColor = RayCasting(refractedRay, objectList, lSrcList, depth+1);

    // phong illumination model
    float diffuseLightIntensity = 0;
    float specularLightIntensity = 0;

    for(int i=0; i<lSrcList.size(); i++){
        Vector3f lSrcDirection = (lSrcList.at(i)->source - iPoint).normalizeIt();
 
        // shadow rays
        Vector3f shadowPoint;
        if(lSrcDirection.dot(nVector) < 0) shadowPoint = iPoint - nVector*1e-3;
        else shadowPoint = iPoint + nVector*1e-3;

        Vector3f shadowIPoint, shadowNVector;
        Material shadowIMaterial;
        Ray3f shadowRay;
        shadowRay.createRay(shadowPoint, lSrcDirection, true);

        if(SceneRayCasting(shadowRay, objectList, shadowIPoint, shadowNVector, shadowIMaterial)){
            if((shadowIPoint - shadowPoint).length() < (lSrcList.at(i)->source - iPoint).length()){
                continue;
            }
        }

        // diffuse light intensity
        diffuseLightIntensity += lSrcList.at(i)->intensity*max(0.f, lSrcDirection.dot(nVector));

        // specular light intensity
        Vector3f reflectionVector = lSrcDirection*(-1.f) - nVector*(2.f*((lSrcDirection*(-1.f)).dot(nVector)));
        specularLightIntensity += powf(max(0.f, reflectionVector.dot((iPoint - ray.origin).normalizeIt())), iMaterial.specularReflectionExponent)*lSrcList.at(i)->intensity;
    }

    Color3f support(1.f, 1.f, 1.f);
    Color3f ret = ((iMaterial.diffuseColor * diffuseLightIntensity)* iMaterial.diffuseReflectionCoefficient) + ((support * specularLightIntensity) * iMaterial.specularReflectionCoefficient) + reflectedSurfaceColor*iMaterial.reflectionCoefficient + refractedSurfaceColor*iMaterial.refractionCoefficient;

    return ret;
}

void Tracer::writeImage(vector<Object*> objectList, vector<Light*> lightSourcesList){
    ofstream imageFile;
    imageFile.open("./figures/exp1/19-5.ppm");

    int width = 1024;
    int height = 768;
    int fieldOfView = M_PI/2;

    vector<Color3f> pixelBuffer(width*height);
    
    // base color for all pixels
    for(int i=0; i<height; i++){
        for(int j=0; j<width; j++){
            float x =  (2*(i + 0.5)/(float)width  - 1) * tan(fieldOfView/2.) * width/(float)height;
            float y = -(2*(j + 0.5)/(float)height - 1) * tan(fieldOfView/2.);
            
            Vector3f dir(x, y, -1);
            dir.normalizeIt();

            // ray origin                
            Vector3f orig(0, 0, 0);
            Ray3f newRay;
            newRay.createRay(orig, dir, true);
            
            pixelBuffer[j+i*width] = RayCasting(newRay, objectList, lightSourcesList);
        }
    }

    // write into ImageFile in ppm format
    imageFile<<"P3\n"<<width<<" "<<height<<"\n255\n";
    for(int i=0; i<height*width; ++i){
            float m = max(pixelBuffer[i].r, max(pixelBuffer[i].g, pixelBuffer[i].b));
            
            if(m>1){
                pixelBuffer[i] = pixelBuffer[i]*(1./m);
            }

            imageFile<<int(pixelBuffer[i].r * 255.99)<<" "<<int(pixelBuffer[i].g * 255.99)<<" "<<int(pixelBuffer[i].b * 255.99)<<"\n";

    }

    imageFile.close();
}
