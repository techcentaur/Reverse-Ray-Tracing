#include <iostream>
#include "vector.h"
#include "ray.h"
#include "material.h"
#include "plane.h"
#include "color.h"
#include "transformation.h"
#include <tuple>

using namespace std;

Plane::Plane(){}

// Plane initialization with a point and normal
Plane::Plane(Vector3f &p, Vector3f &n, Material &m){
	material = m;
	point = p;
	normal = n;
}

// Plane initialization with three points on plane
Plane::Plane(Vector3f &p1, Vector3f &p2, Vector3f &p3, Material &m){
	material = m;
	point = p1;
	normal = (p1.cross(p1-p2, p1-p3)).normalizeIt();
}

bool Plane::getIntersection(Ray3f &ray, float &param){
	float t;
	Vector3f intersectPoint;

	float denom = normal.dot(ray.direction);
	if(denom > 1e-6){
		t = ((point - ray.origin).dot(normal))/((ray.direction).dot(normal));
		
		Vector3f intersectPoint = ray.origin + (ray.direction)*t;

		// If the point is behind camera
		if((ray.origin).lengthFrom(intersectPoint) > (ray.origin + ray.direction).lengthFrom(intersectPoint)){
			param = t;
			return true;
		}
	}

	param = 0.f;
	return false;
}

tuple<float, Vector3f> Plane::distanceAlongRay(Ray3f &ray){
	float t = ((point - ray.origin).dot(this->normal))/((ray.direction - ray.origin).dot(normal));

	Vector3f intersectPoint = ray.origin + (ray.direction - ray.origin)*t;
	float dist = (ray.origin).lengthFrom(intersectPoint);

	return make_tuple(dist, intersectPoint);
}

void translation(const Vector3f &transform){
	Transformation t;
	Vector3f new_point = t.translation(point, transform);
	point = new_point;
}
void rotateAboutX(float angle){
	Transformation t;
	Vector3f new_normal = t.rotateAboutX(normal, angle);
	normal = new_normal;
}
void rotateAboutY(float angle){
	Transformation t;
	Vector3f new_normal = t.rotateAboutY(normal, angle);
	normal = new_normal;
}
void rotateAboutZ(float angle){
	Transformation t;
	Vector3f new_normal = t.rotateAboutZ(normal, angle);
	normal = new_normal;
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
