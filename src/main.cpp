/* Writing Main file and main function */

#include <iostream>
#include <fstream>
#include <vector>
#include <limits>
#include <cmath>
#include <tuple>

#include "color.h"
#include "sphere.h"
#include "vector.h"
#include "ray.h"

using namespace std;

Color3f RayCasting(Ray3f &r, Sphere &s){
	float maxDistance = numeric_limits<float>::max();

	tuple<Vector3f, int> tup = s.getIntersection(r, maxDistance);
	if(!get<1>(tup)){
		return Color3f(0.2, 0.7, 0.8); // background: If didn't intersect
	}
	return Color3f(0.4, 0.4, 0.3);
}

void writeImage(Sphere &sphere){
	ofstream imageFile;
	imageFile.open("./figures/exp1/first.ppm");

	int width = 1024;
	int height = 768;

	int fieldOfView = M_PI/2;

	vector<Color3f> pixelBuffer(width*height);
	
	// base color for all pixels
	for(int i=0; i<height; i++){
		for(int j=0; j<width; j++){
            float x =  (2*(i + 0.5)/(float)width  - 1) * tan(fieldOfView/2.) * width/(float)height;
            float y = -(2*(j + 0.5)/(float)height - 1) * tan(fieldOfView/2.);
			
            Vector3f direction(x, y, -1); direction.normalize();
            Vector3f orig(0, 0, 0);
            Ray3f newRay(orig, direction);
            
			pixelBuffer[j+i*width] = RayCasting(newRay, sphere);
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
	Vector3f v1(-3.f, 0.f, -16.f);
	Sphere sphere(2.f, v1);
	writeImage(sphere);
}