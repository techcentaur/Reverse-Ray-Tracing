#include <tuple>
#include "vector.h"
#include "ray.h"
#include "material.h"
#include "object.h"
#include <cmath>

using namespace std;

Object::Object(Material &m){
	material = m;
}

// -----------------------------Sphere---------------------------
Sphere::Sphere(float r, Vector3f &vec, Material &m)
	:Object(m){
	radius = r; center = vec; material = m;
}

bool Sphere::getIntersection(Ray3f &ray, float &t0){

	Vector3f v(0, 0, 0);

	// parametric method
	Vector3f line = (center - ray.origin);

	float lineProjection = line.dot(ray.direction);
	float dist2 = line.dot(line) - lineProjection*lineProjection;
	
	if(dist2>radius*radius) return false;
	
	float projection2 = sqrtf(radius*radius - dist2);
	t0 = lineProjection-projection2;
	
	float t1 = lineProjection + projection2;
	
	if(t0>0) t0 = t1;
	if(t0<0) return false; 

	return true;
}

void Sphere::print(){
	cout<<"[*] Sphere: \n";
	cout<<"Center: "; center.print();
	cout<<"Radius: "<<radius<<"\n";
	cout<<"Material: "; material.print();
}
// -----------------------------Sphere---------------------------