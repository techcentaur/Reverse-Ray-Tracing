/* Writing Main file and main function */

#include <iostream>
#include <fstream>
#include <vector>

#include "color.h"
// #include "vector.h"
// #include "ray.h"

using namespace std;


void writeImage(){
	ofstream imageFile;
	imageFile.open("temp6.ppm");

	int width = 200;
	int height = 100;

	vector<Color3f> pixelBuffer(width*height);
	
	// base color for all pixels in the figure
	for(int i=0; i<height; i++){
		for(int j=0; j<width; j++){
			pixelBuffer[j+i*width] = Color3f(float(i)/float(height), float(j)/float(width), 0);
		}
	}

	imageFile<<"P3\n"<<width<<" "<<height<<"\n255\n";
	for(int i=0; i<height*width; ++i){
			imageFile<<int(pixelBuffer[i].r * 255.99)<<" "<<int(pixelBuffer[i].g * 255.99)<<" "<<int(pixelBuffer[i].b * 255.99)<<"\n";
	}

	imageFile.close();
}

int main(){
	writeImage();
}