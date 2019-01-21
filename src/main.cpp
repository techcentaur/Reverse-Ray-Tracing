/* Writing Main file and main function:

I will write the functions calls that will get used
And then implement the functions afterward
: Sort of Reverse Engineering*/

#include <iostream>
#include <fstream>

using namespace std;


void writeImage(){
	ofstream imageFile;
	imageFile.open("temp.ppm");

	int nx = 200;
	int ny = 100;
	
	imageFile<<"P3\n"<<nx<<" "<<ny<<"\n255\n";
	for (int i=ny-1; i>=0; i--){
		for(int j=0; j<nx; j++){
			int r = (int)(255.99 * float(j)/float(nx));
			int g = (int)(255.99 * float(i)/float(ny));
			int b = (int)(255.99 * 0.2);
			imageFile<<r<<" "<<g<<" "<<b<<"\n";
		}
	}

	imageFile.close();
}

int main(){
	writeImage();
}