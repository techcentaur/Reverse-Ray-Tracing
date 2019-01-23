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

using namespace std;


bool SceneRayCasting(Ray3f &ray, vector<Sphere*> spheresList, Vector3f &iPoint, Vector3f &nVector, Material &iMaterial){
	float maxDistance = numeric_limits<float>::max();

	for(int i=0; i<spheresList.size(); i++){
		float closetIntersection;
		tuple<Vector3f, bool> tup = spheresList.at(i)->getIntersection(ray, closetIntersection);
		
		bool temp = get<1>(tup);
		if(temp && closetIntersection < maxDistance){
			maxDistance = closetIntersection;
			iPoint = ray.origin + ray.direction*closetIntersection;

			nVector = (iPoint - spheresList.at(i)->center).normalizeIt();
			iMaterial = spheresList.at(i)->material;
		}
	}
	// iMaterial.diffuseColor.print();
	return maxDistance < 1000;
}

Color3f RayCasting(Ray3f &ray, vector<Sphere*> sList, vector<Light*> lSrcList){
	Vector3f iPoint, nVector;
	Material iMaterial;
	// iMaterial.diffuseColor.print();
	bool temp = SceneRayCasting(ray, sList, iPoint, nVector, iMaterial);
	if(!temp){
		Color3f c1(0.0, 0.0, 0.0);
		return c1; // background: If didn't intersect
	}

	float diffuseLightIntensity = 0;
	for(int i=0; i<lSrcList.size(); i++){
		Vector3f lSrcDirection = (lSrcList.at(i)->source - iPoint).normalizeIt();
		diffuseLightIntensity += lSrcList.at(i)->intensity*max(0.f, lSrcDirection.dot(nVector));
	}
	// cout<<(diffuseLightIntensity);
	// iMaterial.diffuseColor.print();
	Color3f ret = iMaterial.diffuseColor * diffuseLightIntensity;
	// ret.print();
	return ret;
}


void writeImage(vector<Sphere*> spheresList, vector<Light*> lightSourcesList){
	ofstream imageFile;
	imageFile.open("./figures/exp1/ninth2.ppm");

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
            Ray3f newRay(orig, direction);
            
			pixelBuffer[j+i*width] = RayCasting(newRay, spheresList, lightSourcesList);
		}
	}

	// write into ImageFile in ppm format
	imageFile<<"P3\n"<<width<<" "<<height<<"\n255\n";
	for(int i=0; i<height*width; ++i){
			imageFile<<int(pixelBuffer[i].r * 255.99)<<" "<<int(pixelBuffer[i].g * 255.99)<<" "<<int(pixelBuffer[i].b * 255.99)<<"\n";
	}

	imageFile.close();
}

int main(){
	Color3f c1(0.3, 0.8, 0.7), c2(0.2, 0.9, 0.3), c3(0.5, 0.1, 0.1);

	Material m1, m2, m3;
	m1.fillColor(c1);
	m2.fillColor(c2);
	m3.fillColor(c3);

	vector<Sphere*> spheresList;
	
	Vector3f v1(-3.f, 0.f, -16.f);
	Vector3f v2(-1.1, -1.5, -12.f), v3(-5, -8, -23.f);
	
	Sphere *s1 = new Sphere(2.f, v1, m1);
	Sphere *s2 = new Sphere(1.f, v2, m2);
	Sphere *s3 = new Sphere(3.f, v3, m3);

	spheresList.push_back(s1);
	spheresList.push_back(s2);
	spheresList.push_back(s3);

	vector<Light*> lightSourcesList;

	Vector3f src1(-50.f, -30.f, -30.f);
	Vector3f src2(50.f, 30.f, 30.f);

	Light *l1 = new Light(src1, 2);
	Light *l2 = new Light(src2, 1);


	lightSourcesList.push_back(l1);
	lightSourcesList.push_back(l2);


	writeImage(spheresList, lightSourcesList);

	return 0;
}