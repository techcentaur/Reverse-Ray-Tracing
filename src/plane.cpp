#include <iostream>
#include "vector.h"
#include "ray.h"
#include "material.h"
#include "plane.h"
#include "color.h"
#include <tuple>

using namespace std;

Plane::Plane(){}

Plane::Plane(Vector3f &p1, Vector3f &p2, Vector3f &p3, Material &m){
	material = m;
	point = p1;
	normal = (p1.cross(p1-p2, p1-p3)).normalizeIt();

}

bool Plane::getIntersection(Ray3f &ray){
	float t;

	float denom = normal.dot((ray.direction - ray.origin).normalizeIt());
	Vector3f intersectPoint;
	if(denom > 1e-6){
		float t = ((point - ray.origin).dot(this->normal))/((ray.direction - ray.origin).dot(normal));
		intersectPoint = ray.origin + (ray.direction - ray.origin)*t;
		if((ray.origin).lengthFrom(intersectPoint) > (ray.direction).lengthFrom(intersectPoint)){
			return true;
		}
	}
	return false;
}

tuple<float, Vector3f> Plane::distanceAlongRay(Ray3f &ray){
	float t = ((point - ray.origin).dot(this->normal))/((ray.direction - ray.origin).dot(normal));

	Vector3f intersectPoint = ray.origin + (ray.direction - ray.origin)*t;
	float dist = (ray.origin).lengthFrom(intersectPoint);

	return make_tuple(dist, intersectPoint);
}

void Plane::print(){
	cout<<"[*] Plane: \n";
	cout<<"Point: "; point.print();
	cout<<"Normal: "; normal.print();
	cout<<"Material: "; material.print();
}

// int main(){
// 	Vector3f v1(0, -4, 0), v2(2, -4, 2), v3(4, -4, 1);
// 	Color3f c1(1, 1, 1);
// 	Material m1;
// 	m1.fillColor(c1, 10.f, 0.9, 0.2);

// 	Plane p(v1, v2, v3, m1);
// 	p.print();
// }