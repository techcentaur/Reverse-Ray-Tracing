#include <iostream>
#include <cmath>
#include <algorithm>
#include <tuple>

#include "vector.h"
#include "box.h"
#include "ray.h"
// #include "transformation.h"

using namespace std;

Box::Box(){
}

Box::Box(float lenA, float lenB, float lenC, Vector3f &cen, Material &m){
          a = lenA; b = lenB; c = lenC;
          // dirA = directionA;
          // dirB = Transformation::rotateAboutZ(directionA, 90.f);
          // dirC = Transformation::rotateAboutY(directionA, -90.f);
          center = cen;
          material = m;
}

tuple<Vector3f, bool> Box::getIntersection(Ray3f &ray, float &t0){
          
}

void Box::print(){
	cout<<"[*] Box: \n";
	cout<<"A: "<<a<<"\n";
          cout<<"B: "<<b<<"\n";
          cout<<"C: "<<c<<"\n";
          // cout<<"A Direction: ";dirA.print();
	// cout<<"B Direction: ";dirB.print();
	// cout<<"C Direction: ";dirC.print();
	cout<<"Center: ";center.print();
	cout<<"Material: "; material.print();
}