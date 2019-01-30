#include <iostream>
#include <cmath>
#include <algorithm>
#include <tuple>

#include "vector.h"
#include "box.h"
#include "ray.h"
#include "transformation.h"

using namespace std;

Box::Box(){
}

Box::Box(float la, float lb, float lc, Vector3f &p, Material &m){
          Transformation t;
          lenA = la; lenB = lb; lenC = lc;
          point = p;
          material = m;

          dirA = Vector3f(1.f,0.f,0.f);
          dirB = Vector3f(0.f,1.f,0.f);
          dirC = Vector3f(0.f,0.f,1.f);

          dirA_ = Vector3f(-1.f,0.f,0.f);
          dirB_ = Vector3f(0.f,-1.f,0.f);
          dirC_ = Vector3f(0.f,0.f,-1.f);
}

tuple<Vector3f, bool> Box::getIntersection(Ray3f &ray, float &t0){
          // intersection in xy face
          vector<tuple<Vector3f,bool> > intersections;
          
          // 1 faceXY
          Vector3f facePoint(point+lenC);
          Plane face(facePoint, dirC, material);
          intersections.push_back(getFaceIntersection(ray, face, max(point.x,)))
}
tuple<Vector3f, bool> Box::getFaceIntersection(Ray3f &ray, Plane &f, float b1, float b1_, float b2, float b2_, float &t0){

}
void Box::print(){
}

int main(){
	Vector3f v1(0, -4, 0), v2(2, -4, 2), v3(4, -4, 1);
	Color3f c1(1, 1, 1);
	Material m1;
	m1.fillColor(c1, 10.f, 0.9, 0.2);

	Plane p(v1, v2, v3, m1);
	p.print();
	return 0;	
}