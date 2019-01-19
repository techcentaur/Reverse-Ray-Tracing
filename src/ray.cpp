#include <iostream>
#include "ray.h"
#include "vector.h"
#include <cmath>
using namespace std;

Ray::Ray(){
	Vector origin;
	Vector direction;
}

Ray::Ray(Vector o, Vector d){
	origin = o;
	if(d.length != 1){
		double l = d.length;
		d.x = d.x/l;
		d.y = d.y/l;
		d.z = d.z/l;
	}
	direction = d;
}

void Ray::represent(){
	cout<<"Origin: "<<origin.represent()<<endl;
	cout<<" Direction: "<<direction.represent()<<endl;
}
