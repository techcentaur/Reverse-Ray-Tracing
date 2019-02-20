 // Main ray tracer

#include <iostream>
#include <fstream>
#include <vector>
#include <limits>
#include <cmath>
#include <tuple>
#include  <typeinfo>
#include <cstring>
#include <algorithm>

#include "tracer.h"
#include "color.h"
#include "object.h"
#include "vector.h"
#include "ray.h"
#include "material.h"
#include "camera.h"
#include "light.h"

using namespace std;

vector<Vector3f> intersectionPointsOfARay;

bool Tracer::SceneRayCasting(Ray3f &ray, vector<Object*> objectList, Vector3f &iPoint, Vector3f &nVector, Material &iMaterial){
    float maxDistance = numeric_limits<float>::max();

    float closestIntersection;
    for(int i=0; i<objectList.size(); i++){
        bool temp = objectList.at(i)->getIntersection(ray, closestIntersection);

        if(temp && closestIntersection < maxDistance){
            maxDistance = closestIntersection;
            // don't need intersection point and normal vector: Fuuction will do the work (call by reference)

            iPoint = ray.origin + ray.direction*closestIntersection;
            nVector = objectList.at(i)->getNormalOnIntersectionPoint(iPoint, ray);

            iMaterial = objectList.at(i)->material;
        }
    }
    return maxDistance < 5000;
}

Color3f Tracer::RayCasting(Ray3f &ray, vector<Object*> objectList, vector<Light*> lSrcList, int depth=0){

    Vector3f iPoint, nVector;
    Material iMaterial;

    bool temp = SceneRayCasting(ray, objectList, iPoint, nVector, iMaterial);

    if(!temp || depth > this->recursionDepth){
        Color3f c1(0.2, 0.7, 0.7);
        return c1;
    }

    // if(iPoint){
    //     intersectionPointsOfARay.at(1).push_back(iPoint);
    // }
    // reflected ray recursive function
    Vector3f reflectionVector = ((nVector*(2.f*((ray.direction).dot(nVector)))) - ray.direction).normalizeIt();
    Vector3f reflectedPoint;
    if(reflectionVector.dot(nVector) < 0) reflectedPoint = iPoint - nVector*1e-3;
    else reflectedPoint = iPoint + nVector*1e-3;

    Ray3f reflectedRay;
    reflectedRay.createRay(reflectedPoint, reflectionVector, true);
    Color3f reflectedSurfaceColor = RayCasting(reflectedRay, objectList, lSrcList, depth+1);


    // refracted ray recursive function - first refraction
    float eta = this->refractiveIndexOfMedium/iMaterial.refractiveIndex;
    float costheta1 = max(-1.f, min(1.f, ray.direction.dot(nVector)));
    float sintheat2 = max(-1.f, min(1.f, eta*costheta1));

    Vector3f refractedVector = ((ray.direction)*eta + nVector*(costheta1*eta - sqrtf(1 - (sintheat2*sintheat2)))).normalizeIt();

    Vector3f refractedPoint;
    if(refractedVector.dot(nVector) < 0) refractedPoint = iPoint - nVector*1e-3 ;
    else refractedPoint = iPoint + nVector*1e-3;

    Ray3f refractedRay;
    refractedRay.createRay(refractedPoint, refractedVector, true);

    // final ray achieved after 2 refraction

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
            if((shadowIPoint - shadowPoint).length() < (lSrcList.at(i)->source - shadowPoint).length()){
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

    if (find(intersectionPointsOfARay.begin(), intersectionPointsOfARay.end(), iPoint) == intersectionPointsOfARay.end())
        intersectionPointsOfARay.push_back(iPoint);

    return ret;
}

vector<Vector3f> Tracer::getIntersectionPointsOfARay(vector<Object*> objects, vector<Light*> lights, Camera &cam, int i, int j){
    /* Indexing of Intersection Points:
    Index | Description
    0 - For initial camera point
    1 - For intersection point

    */

    int width = cam.width;
    int height = cam.height;
    int superSamplingRays = 1;
    int fieldOfView = cam.fov;
    this->recursionDepth = cam.recursionDepth;

    intersectionPointsOfARay.clear();

    for(int s=0; s<superSamplingRays; s++){
        float x = float(j + 0.5) / float(width);
        float y = float(i + 0.5) / float(height);

        Ray3f newRay = cam.getRay(x, y);
        
        Vector3f v1(0, 0, 1);
        Vector3f v2(float(1024 + 0.5) / float(width), 0, 1);
        Vector3f v3(float(1024 + 0.5) / float(width), float(768 + 0.5) / float(width), 1);
        Vector3f v4(0, float(768 + 0.5) / float(width), 1);
        intersectionPointsOfARay.push_back(v1);
        intersectionPointsOfARay.push_back(v2);
        intersectionPointsOfARay.push_back(v3);
        intersectionPointsOfARay.push_back(v4);
        intersectionPointsOfARay.push_back(newRay.origin);

        RayCasting(newRay, objects, lights, 0);
    }
    // drawInPixelBuffer(j, i, col.r, col.g, col.b);
    cout<<"Number of Intersections Points: "<<intersectionPointsOfARay.size()<<endl;

    // for(Vector3f v: intersectionPointsOfARay){
    //     v.print();
    // }
    return intersectionPointsOfARay;
}

void Tracer::writeImage(vector<Object*> objectList, vector<Light*> lightSourcesList, string fileName, Camera &cam, bool antiAliasing=false){
    ofstream imageFile;
    imageFile.open(fileName);

    int width = cam.width;
    int height = cam.height;
    int superSamplingRays = cam.superSampling;
    int fieldOfView = cam.fov;
    this->recursionDepth = cam.recursionDepth;

    vector<Color3f> pixelBuffer(width*height);

    // base color for all pixels
    if(antiAliasing){
        for(int i=0; i<height; i++){
            for(int j=0; j<width; j++){
                float x =  (2*(i + 0.25)/(float)width  - 1) * tan(fieldOfView/2.) * width/(float)height;
                float y = -(2*(j + 0.25)/(float)height - 1) * tan(fieldOfView/2.);
                
                Vector3f dir1(x, y, -1);
                dir1.normalizeIt();

                x =  (2*(i + 0.25)/(float)width  - 1) * tan(fieldOfView/2.) * width/(float)height;
                y = -(2*(j + 0.75)/(float)height - 1) * tan(fieldOfView/2.);

                Vector3f dir2(x, y, -1);
                dir2.normalizeIt();

                x =  (2*(i + 0.75)/(float)width  - 1) * tan(fieldOfView/2.) * width/(float)height;
                y = -(2*(j + 0.25)/(float)height - 1) * tan(fieldOfView/2.);

                Vector3f dir3(x, y, -1);
                dir3.normalizeIt();

                x =  (2*(i + 0.75)/(float)width  - 1) * tan(fieldOfView/2.) * width/(float)height;
                y = -(2*(j + 0.75)/(float)height - 1) * tan(fieldOfView/2.);

                Vector3f dir4(x, y, -1);
                dir4.normalizeIt();

                // ray origin                
                Vector3f orig(0, 0, 0);
                Ray3f newRay1, newRay2, newRay3, newRay4;
                newRay1.createRay(orig, dir1, true);
                newRay2.createRay(orig, dir2, true);
                newRay3.createRay(orig, dir3, true);
                newRay4.createRay(orig, dir4, true);

                
                pixelBuffer[j+i*width] = (RayCasting(newRay1, objectList, lightSourcesList) + RayCasting(newRay2, objectList, lightSourcesList) + RayCasting(newRay3, objectList, lightSourcesList) + RayCasting(newRay4, objectList, lightSourcesList))*0.25;
            }
        }
    }else{
        for(int i=height-1; i>=0; i--){
            for(int j=0; j<width; j++){
                intersectionPointsOfARay.clear();
                Color3f col(0.f, 0.f, 0.f);
                for(int s=0; s<superSamplingRays; s++){
                    float x = float(j + 0.5) / float(width);
                    float y = float(i + 0.5) / float(height);

                    Ray3f newRay = cam.getRay(x, y);
                    intersectionPointsOfARay.push_back(newRay.origin);
                    col += (RayCasting(newRay, objectList, lightSourcesList));
                    if(intersectionPointsOfARay.size() > 3){
                        cam.getRay(x, y).print();
                        cout<<"X "<<x<<"  "<<"y "<<y<<endl;
                        cout<<"i "<<i<<"  "<<"j "<<j<<endl;
                        cout<<intersectionPointsOfARay.size()<<endl;

                        for(int p=0; p<intersectionPointsOfARay.size(); p++){
                            intersectionPointsOfARay.at(p).print();
                        }
                    }
                }
                col /= float(superSamplingRays);
                pixelBuffer[j+i*width] = col;
            }
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
