/* Writing Main file and main function */

#include <iostream>
#include <fstream>
#include <vector>
#include <limits>
#include <cmath>
#include <tuple>
#include  <typeinfo>

#include "color.h"
#include "sphere.h"
#include "vector.h"
#include "ray.h"
#include "material.h"
#include "light.h"
#include "plane.h"

using namespace std;


bool SceneRayCasting(Ray3f &ray, vector<Sphere*> spheresList, Vector3f &iPoint, Vector3f &nVector, Material &iMaterial, vector <Plane*> planesList){
	float maxDistance = numeric_limits<float>::max();

	for(int i=0; i<spheresList.size(); i++){
		float closestIntersection;
		
		tuple<Vector3f, bool> tup = spheresList.at(i)->getIntersection(ray, closestIntersection);
		bool temp = get<1>(tup);
		
		if(temp && closestIntersection < maxDistance){
			maxDistance = closestIntersection;
			iPoint = ray.origin + ray.direction*closestIntersection;

			nVector = (iPoint - spheresList.at(i)->center).normalizeIt();
			iMaterial = spheresList.at(i)->material;
		}
	}

	// float closestDist = maxDistance;
	// float closestDist = numeric_limits<float>::max();

	// for(int i=0; i<planesList.size(); i++){
	// 	bool didIntersect = planesList.at(i)->getIntersection(ray);

	// 	tuple<float, Vector3f> tup1 = planesList.at(i)->distanceAlongRay(ray);

	// 	if(didIntersect && get<0>(tup1) < closestDist){
	// 		closestDist = get<0>(tup1);
	// 		iPoint = get<1>(tup1);

	// 		nVector = planesList.at(i)->normal;
	// 		iMaterial = planesList.at(i)->material;
	// 	}
	// }

	// iMaterial.diffuseColor.print();
	// cout<<(bool)(min(closestDist, maxDistance) == closestDist);
	return maxDistance < 5000;
}

Color3f RayCasting(Ray3f &ray, vector<Sphere*> sList, vector<Light*> lSrcList, vector <Plane*> planesList){
	Vector3f iPoint, nVector;
	Material iMaterial;
	// iMaterial.diffuseColor.print();
	bool temp = SceneRayCasting(ray, sList, iPoint, nVector, iMaterial, planesList);
	if(!temp){
		Color3f c1(0.2, 0.7, 0.7);
		return c1; // background: If didn't intersect
	}

	float diffuseLightIntensity = 0;
	float specularLightIntensity = 0;

	for(int i=0; i<lSrcList.size(); i++){
		Vector3f lSrcDirection = (lSrcList.at(i)->source - iPoint).normalizeIt();
		diffuseLightIntensity += lSrcList.at(i)->intensity*max(0.f, lSrcDirection.dot(nVector));

		Vector3f reflectionVector = lSrcDirection*(-1.f) - nVector*(2.f*((lSrcDirection*(-1.f)).dot(nVector)));
		specularLightIntensity += powf(max(0.f, reflectionVector.dot((iPoint - ray.origin).normalizeIt())), iMaterial.specularReflectionExponent)*lSrcList.at(i)->intensity;
	}
	// cout<<(diffuseLightIntensity);
	// iMaterial.diffuseColor.print();
	Color3f support(1.f, 1.f, 1.f);
	Color3f ret = ((iMaterial.diffuseColor * diffuseLightIntensity)* iMaterial.diffuseReflectionCoefficient) + ((support * specularLightIntensity) * iMaterial.specularReflectionCoefficient);
	// ret.print();
	return ret;
}


void writeImage(vector<Sphere*> spheresList, vector<Light*> lightSourcesList, vector <Plane*> planesList){
	ofstream imageFile;
	imageFile.open("./figures/exp1/16.ppm");

	int width = 1024;
	int height = 768;

	int fieldOfView = M_PI/2;

	vector<Color3f> pixelBuffer(width*height);
	
	// base color for all pixels
	for(int i=0; i<height; i++){
		for(int j=0; j<width; j++){
            float x =  (2*(i + 0.5)/(float)width  - 1) * tan(fieldOfView/2.) * width/(float)height;
            float y = -(2*(j + 0.5)/(float)height - 1) * tan(fieldOfView/2.);
			
            Vector3f direction(x, y, -1);
            direction.normalizeIt();
            
            Vector3f orig(0, 0, 0);
            Ray3f newRay;
            newRay.Ray3fWithDirection(orig, direction);
            
			pixelBuffer[j+i*width] = RayCasting(newRay, spheresList, lightSourcesList, planesList);
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

int main(){
	Color3f c1(0.3, 0.8, 0.7), c2(0.2, 0.9, 0.3), c3(0.5, 0.1, 0.1);
	Color3f violet(0.6, 0, 0.8), indigo(0.26, 0, 0.56), blue(0, 0, 1);
	Color3f orange(1, 0.5, 0), red(1, 0, 0);


	Material m1, m2, m3, mv, mi, mb, mo, mr;
	m1.fillColor(c1, 20.f, 0.8, 0.9);
	m2.fillColor(c2, 30.f, 0.5, 0.9);
	m3.fillColor(c3, 50.f, 0.8, 0.3);
	mv.fillColor(violet, 20.f, 0.7, 0.4);
	mi.fillColor(indigo, 20.f, 0.8, 0.6);
	mb.fillColor(blue, 20.f, 0.2, 0.3);
	mo.fillColor(orange, 20.f, 0.4, 0.6);
	mr.fillColor(red, 20.f, 0.6, 0.2);

	vector<Sphere*> spheresList;
	
	Vector3f v1(-3.f, 0.f, -16.f);
	Vector3f v2(-1.1, -1.5, -12.f), v3(-5, -8, -23.f);
	Vector3f vv(-1.f, 5.f, -20.f), vi(-1.f, 2.f, -20.f), vb(-1.f, -2.f, -20.f);
	Vector3f vo(-1.f, -5.f, -20.f), vr(-1.f, -10.f, -20.f);
	
	Sphere *s1 = new Sphere(2.f, v1, m1);
	Sphere *s2 = new Sphere(1.f, v2, m2);
	Sphere *s3 = new Sphere(3.f, v3, m3);
	Sphere *sv = new Sphere(1.f, vv, mv);
	Sphere *si = new Sphere(1.f, vi, mi);
	Sphere *sb = new Sphere(1.f, vb, mb);
	Sphere *so = new Sphere(1.f, vo, mo);
	Sphere *sr = new Sphere(1.f, vr, mr);


	spheresList.push_back(s1);
	spheresList.push_back(s2);
	spheresList.push_back(s3);
	spheresList.push_back(sv);
	spheresList.push_back(si);
	spheresList.push_back(sb);
	spheresList.push_back(so);
	spheresList.push_back(sr);


	vector<Light*> lightSourcesList;

	Vector3f src1(-50.f, -30.f, -30.f);
	Vector3f src2(0.f, 0.f, -20.f);
	// Vector3f src3(20.f, 10.f, 10.f);

	Light *l1 = new Light(src1, 1.2);
	Light *l2 = new Light(src2, 1.8);
	// Light *l3 = new Light(src3, 1.7);

	lightSourcesList.push_back(l1);
	lightSourcesList.push_back(l2);
	// lightSourcesList.push_back(l3);

	// Vector3f vp1(-2, 1,5), vp2(-2, 2,6), vp3(-2, 4,5);
	// Color3f cp1(0.2, 0.2, 0.2);
	// Material mp1;
	// mp1.fillColor(cp1, 20.f, 0.9, 0.2);
// 
	vector <Plane*> planesList;

	// Plane *p1 = new Plane(vp1, vp2, vp3, mp1);
	// planesList.push_back(p1);

	writeImage(spheresList, lightSourcesList, planesList);

	return 0;
}