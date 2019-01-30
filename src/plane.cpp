#include <iostream>
#include "vector.h"
#include "ray.h"
#include "material.h"
#include "plane.h"
#include "color.h"
#include "transformation.h"
#include <tuple>
#include <vector>

using namespace std;

Plane::Plane(){}

// Plane initialization with a point and normal
Plane::Plane(Vector3f &p, Vector3f &n, Material &m, vector<float> b){
	material = m;
	point = p;
	normal = n;
	bounds = b;
}

// Plane initialization with three points on plane
Plane::Plane(Vector3f &p1, Vector3f &p2, Vector3f &p3, Material &m, vector<float> b){
	material = m;
	point = p1;
	normal = (p1.cross(p1-p2, p1-p3)).normalizeIt();
	bounds = b;
}

Plane::Plane(const Plane &p){

}

bool Plane::getIntersection(Ray3f &ray, float &param){
	float t;
	Vector3f intersectPoint;

	float denom = normal.dot(ray.direction);
	if(denom > 1e-6){
		t = ((point - ray.origin).dot(normal))/((ray.direction).dot(normal));
		
		Vector3f intersectPoint = ray.origin + (ray.direction)*t;

		// If the point is behind camera
		if(bounds.size() == 0){
			if((ray.origin).lengthFrom(intersectPoint) > (ray.origin + ray.direction).lengthFrom(intersectPoint)){
				param = t;
				return true;
			}
		}
		else if(bounds.size() > 0){
			if(intersectPoint.x >= bounds[0] && intersectPoint.x <= bounds[1] )
			{
				if(intersectPoint.y >= bounds[2] && intersectPoint.y <= bounds[3] ){
					if(intersectPoint.z >= bounds[4] && intersectPoint.z <= bounds[5] ){
						if((ray.origin).lengthFrom(intersectPoint) > (ray.origin + ray.direction).lengthFrom(intersectPoint)){
							param = t;
							return true;
						}
					}
				}
			}
		}
		
	}

	param = 0.f;
	return false;
}


Vector3f Plane::getNormalOnIntersectionPoint(Vector3f &point, Ray3f &ray){
	return this->normal;
}

// void Plane::translation(const Vector3f &vec){
// 	point = point + vec;
// 	bound[0] += vec.x; bound[2] += vec.y; bound[4] += vec.z;
// 	bound[1] += vec.x; bound[3] += vec.y; bound[5] += vec.z;
// }

// void rotateAboutX(float angle){
// 	Transformation t;
// 	Vector3f new_normal = t.rotateAboutX(normal, angle);
// 	normal = new_normal;
// }

// void rotateAboutY(float angle){
// 	Transformation t;
// 	Vector3f new_normal = t.rotateAboutY(normal, angle);
// 	normal = new_normal;
// }
// void rotateAboutZ(float angle){
// 	Transformation t;
// 	Vector3f new_normal = t.rotateAboutZ(normal, angle);
// 	normal = new_normal;
// }

void Plane::print(){
	cout<<"[*] Plane: \n";
	cout<<"Point: "; point.print();
	cout<<"Normal: "; normal.print();
	cout<<"Material: "; material.print();
}

