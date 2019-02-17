#include <tuple>
#include "vector.h"
#include "ray.h"
#include "material.h"
#include "object.h"
#include "transformation.h"
#include <cmath>
#include <limits>


using namespace std;

Object::Object(Material &m){
	material = m;
}

// -----------------------------Sphere---------------------------
Sphere::Sphere(float r, Vector3f &vec, Material &m):Object(m){
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
	float temp;
	if(t0>=0){
		temp = t0;
		t0 = t1;
	}else{
		 return false;
	} 

	t1 = temp;

	return true;
}

Vector3f Sphere::getNormalOnIntersectionPoint(Vector3f &point, Ray3f &ray){
	if((ray.origin).lengthFrom(this->center) < radius){
		return (this->center - point).normalizeIt();	
	}
	return (point - this->center).normalizeIt();
}


void Sphere::print(){
	cout<<"[*] Sphere: \n";
	cout<<"Center: "; center.print();
	cout<<"Radius: "<<radius<<"\n";
	cout<<"Material: "; material.print();
}
// -----------------------------Sphere---------------------------


// ------------------------------Plane---------------------------

// Plane initialization with a point and normal
Plane::Plane(Vector3f &p, Vector3f &n, Material &m):Object(m){
	point = p;
	normal = n.normalizeIt();
}

// Plane initialization with three points on plane
Plane::Plane(Vector3f &p1, Vector3f &p2, Vector3f &p3, Material &m):Object(m){
	point = p1;
	normal = (p1.cross(p1-p2, p1-p3)).normalizeIt();
	// bounds = b;
}

bool Plane::getIntersection(Ray3f &ray, float &t){
	float param;
	Vector3f intersectPoint;

	float denom = normal.dot(ray.direction);
	if(denom > 1e-6){
		param = ((point - ray.origin).dot(normal))/((ray.direction).dot(normal));
		
		Vector3f intersectPoint = ray.origin + (ray.direction)*param;

		// If the point is behind camera
		// if(bounds.size() == 0){
			if((ray.origin).lengthFrom(intersectPoint) > (ray.origin + ray.direction).lengthFrom(intersectPoint)){
				t = param;
				return true;
			}
		// }
		// else if(bounds.size() > 0){
		// 	if(intersectPoint.x >= bounds[0] && intersectPoint.x <= bounds[1] )
		// 	{
		// 		if(intersectPoint.y >= bounds[2] && intersectPoint.y <= bounds[3] ){
		// 			if(intersectPoint.z >= bounds[4] && intersectPoint.z <= bounds[5] ){
		// 				if((ray.origin).lengthFrom(intersectPoint) > (ray.origin + ray.direction).lengthFrom(intersectPoint)){
		// 					t = param;
		// 					return true;
		// 				}
		// 			}
		// 		}
		// 	}
		// }
		
	}

	t = 0.f;
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

// ------------------------------Plane---------------------------


// -------------------------------Box----------------------------

Box::Box(Vector3f &translate, Vector3f &scale, Material &m):Object(m){

		// center; lbh
		Vector3f vt(0, 0, 0); // reference coordianate
		// scale and translate
		Vector3f v1 =  (vt)*scale + translate; 
		Vector3f v2 = (vt+1.0)*scale + translate;
		
		// create normals
		Vector3f n1(-1, 0, 0), n2(0, -1, 0), n3(0, 0, -1);
		Vector3f n4(1, 0, 0), n5(0, 1, 0), n6(0, 0, 1);

		// Transformation t;
		// v2 = t.shearingYAboutX(v2,1);
		// n1 = t.rotateAboutY(n1,-45);
		// n4 = t.rotateAboutY(n4,-45);
		// v2.print();
		// n1.print();
		// n4.print();

		// create all side planes
		Plane p1(v1, n1, m), p2(v1, n2, m), p3(v1, n3, m);
		Plane p4(v2, n4, m), p5(v2, n5, m), p6(v2, n6, m);

		planes.push_back(p1);
		planes.push_back(p2);
		planes.push_back(p3);
		planes.push_back(p4);
		planes.push_back(p5);
		planes.push_back(p6);

		Vector3f recentNormal(0.0, 0.0, 0.0);

		boundPoints.push_back(v1);
		boundPoints.push_back(v2);
}


bool Box::getIntersection(Ray3f &ray, float &t){
	vector<tuple<float, int>> allParams;

	for(int i=0; i<planes.size(); i++){
		float t1;
		if((planes.at(i)).getIntersection(ray, t1)){
            // Vector3f iPoint = ray.origin + ray.direction*t1;
            // Vector3f nVector = (planes.at(i)).getNormalOnIntersectionPoint(iPoint, ray);
			allParams.push_back(make_tuple(t1, i));
		}	
	}

	if(allParams.size()==0){
		return false;
	}
	// cout<<allParams.size();

	int minIndex = numeric_limits<int>::max();
	bool flag = false;
	float minT = numeric_limits<float>::max();
	vector<tuple<Vector3f, int>> interPointsList;
	for(int i=0; i<allParams.size(); i++){

		Vector3f interPoint = ray.origin + ray.direction*get<0>(allParams.at(i));

		if((interPoint.x <= boundPoints[1].x && interPoint.x >= boundPoints[0].x) || (interPoint.x >= boundPoints[1].x && interPoint.x <= boundPoints[0].x)){
		// 	cout<<"*";
			if((interPoint.y <= boundPoints[1].y && interPoint.y >= boundPoints[0].y) || (interPoint.y >= boundPoints[1].y && interPoint.y <= boundPoints[0].y)){
		// 		cout<<"+";
				if((interPoint.z <= boundPoints[1].z && interPoint.z >= boundPoints[0].z) || (interPoint.z >= boundPoints[1].z && interPoint.z <= boundPoints[0].z)){
				// 	cout<<"l/"<<endl;
					interPointsList.push_back(make_tuple(interPoint, i));
					// cout<<flag;	
				}
			}
		}
	}

	if(interPointsList.size()==0){
		return false;
	}

	float dist = numeric_limits<float>::max();
	int minDistIndex = 0;

	for(int i=0; i<interPointsList.size(); i++){
		if((ray.origin).lengthFrom(get<0>(interPointsList.at(i))) < dist){
			dist = (ray.origin).lengthFrom(get<0>(interPointsList.at(i)));
			minDistIndex = i;
		}
	}

	recentNormal = planes[get<1>(interPointsList.at(minDistIndex))].getNormalOnIntersectionPoint(get<0>(interPointsList.at(minDistIndex)), ray);

	return true;
}

Vector3f Box::getNormalOnIntersectionPoint(Vector3f &point, Ray3f &ray){
	return recentNormal;
}

void Box::print(){
	cout<<"Not implemented"<<endl;
}
// -------------------------------Box----------------------------



//--------------------------------Cone----------------------------------

Cone::Cone(Vector3f c, Vector3f uV, float a, float h, Material &m):Object(m) {
	center = c;
	upVector = uV.normalizeIt();
	alpha = a;
	radius = h * tan(a);
	height = h;
}


bool Cone::getIntersection(Ray3f &ray, float &t) {
	vector<float> intersectionPointsParams;

	float cos2Alpha = cos(alpha)*cos(alpha);
	float sin2Alpha = 1 - cos2Alpha;

	Vector3f apexVector = center + upVector * height;
	Vector3f downVector = upVector * -1;
	Vector3f deltaP = (ray.origin - apexVector);

	float projec1 = ray.direction.dot(downVector);
	Vector3f vec1 = downVector*projec1;
	float projec2 = deltaP.dot(downVector);
	Vector3f vec2 = downVector*projec2;

	float a = cos2Alpha*((ray.direction - vec1).lengthSquare()) - sin2Alpha*projec1*projec1;
	float b = 2*cos2Alpha*((ray.direction - vec1).dot(deltaP - vec2)) - 2 * sin2Alpha*(projec1*projec2);
	float c = cos2Alpha*((deltaP - vec2).lengthSquare()) - sin2Alpha*(projec2*projec2);

	float discriminant = b*b - 4*a*c;
	if (discriminant < 0) return false;
	else {
		discriminant = sqrt(discriminant);
		float t1 = ((-1*b) + discriminant)/(2*a);
		float t2 = ((-1*b) - discriminant)/(2*a);
		if(t1>=0){
			if(upVector.dot((ray.origin - center) + ray.direction*t1)>0 && upVector.dot((ray.origin - apexVector) + ray.direction*t1)<0)
				intersectionPointsParams.push_back(t1);
		}
		if(t2>=0)
			if(upVector.dot((ray.origin - center) + ray.direction*t2)>0 && upVector.dot((ray.origin - apexVector) + ray.direction*t2)<0)
				intersectionPointsParams.push_back(t2);
	}

	float denominator = (ray.direction).dot(upVector);
	if (denominator > 1e-6) {
		Vector3f co = center - ray.origin;
		float t3 = co.dot(upVector)/denominator;
		if(t3 > 0 && (ray.direction*t3 - co).lengthSquare() <= radius*radius)
			intersectionPointsParams.push_back(t3);
	}

	float minParam = INFINITY;
	bool flag = false;
	for(int i=0;i<intersectionPointsParams.size();i++){
		if(minParam > intersectionPointsParams[i] && intersectionPointsParams[i]>=0) {
			minParam = intersectionPointsParams[i];
			flag = true;
		}
	}
	if(flag){ t = minParam; return true;}
	else return false;
}

Vector3f Cone::getNormalOnIntersectionPoint(Vector3f &point, Ray3f &ray){

	if(abs((point - center).dot(upVector)) < 1e-4){
		return upVector*(-1);
	}

	Vector3f top = center + upVector * height;
	Vector3f perpendicularVec = (upVector * -1).cross((upVector * -1), point - top);

	return ((point - top).cross((point - top), perpendicularVec)).normalizeIt();
}

void Cone::print(){
	cout<<"Not implemented"<<endl;
}