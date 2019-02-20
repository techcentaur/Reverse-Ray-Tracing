#include <tuple>
#include <vector>
#include "vector.h"
#include "ray.h"
#include "material.h"
#include "object.h"
#include "transformation.h"
#include <cmath>
#include <limits>
#include <fstream>
#include "color.h"

using namespace std;

Object::Object(Material &m){
	material = m;
}

// -----------------------------Sphere---------------------------
Sphere::Sphere(float r, Vector3f &vec, Material &m):Object(m){
	radius = r; center = vec; material = m;
	readTexture();
}

void Sphere::readTexture(){
    ifstream ifs;
    ifs.open("./samp_tex.ppm", ios::in);
    if(!ifs.is_open()) {
        cout<<"Error opening file"<<endl;
    }

    ifs>>textureCount;
    while(ifs.good()){
        float x, y, z;
        ifs>>x>>y>>z;
    	Color3f c1(x, y, z);
        texture.push_back(c1);
	}
}


bool Sphere::getIntersection(Ray3f &ray, float &t0){

	//-------------------transformations---------
	Vector3f v(0, 0, 0);

	vector<vector<float>> M;
	M.assign(3, vector<float>(3,0));
	
	for (int i=0; i<3; i++) M[i][i] = 0;
	M[0][0] = 1; M[0][1] = 1; M[0][2] = 1;
	M[1][0] = 0; M[1][1] = 1; M[1][2] = 1;
	M[2][0] = 0; M[2][1] = 0; M[2][2] = 1;

	vector<vector<float>> Minv = M;

	Vector3f d(0, 0, 0);

	Ray3f newRay;

	Vector3f temp = ray.origin;
	Vector3f temp2(Minv[0][0]*temp.x + Minv[0][1]*temp.y + Minv[0][2]*temp.z, Minv[1][0]*temp.x + Minv[1][1]*temp.y + Minv[1][2]*temp.z, Minv[2][0]*temp.x + Minv[2][1]*temp.y + Minv[2][2]*temp.z);

	temp = ray.direction;
	Vector3f temp3(Minv[0][0]*temp.x + Minv[0][1]*temp.y + Minv[0][2]*temp.z , Minv[1][0]*temp.x + Minv[1][1]*temp.y + Minv[1][2]*temp.z, Minv[2][0]*temp.x + Minv[2][1]*temp.y + Minv[2][2]*temp.z);
	
	temp3.normalize();
	temp2 = temp2 + d;
	newRay.createRay(temp2, temp3, true);

	// ray = newRay;

	//-------------------transformations:-----------

	// parametric method
	Vector3f line = (center - ray.origin);

	float lineProjection = line.dot(ray.direction);
	float dist2 = line.dot(line) - lineProjection*lineProjection;
	
	if(dist2>radius*radius) return false;
	
	float projection2 = sqrtf(radius*radius - dist2);
	t0 = lineProjection-projection2;
	
	float t1 = lineProjection + projection2;
	float temp_;
	if(t0>=0){
		temp_ = t0;
		t0 = t1;
	}else{
		 return false;
	} 

	t1 = temp_;
	
	recentIntersectionPoint = ray.origin + ray.direction*t0;
	
	if((ray.origin).lengthFrom(this->center) < radius){
		recentNormal = (this->center - recentIntersectionPoint).normalizeIt();	
	}
	else{
		recentNormal = (recentIntersectionPoint - this->center).normalizeIt();
	}

	recentColor = getTexture(recentIntersectionPoint);
	this->material.changeColor(recentColor);

	//---------------transformations on Normal------------
	// Minv = getInverseMatrix(Minv);
	// temp = recentNormal;
	// Minv = getTranspose(Minv);
	// Vector3f tempRec(Minv[0][0]*temp.x + Minv[0][1]*temp.y + Minv[0][2]*temp.z , Minv[1][0]*temp.x + Minv[1][1]*temp.y + Minv[1][2]*temp.z, Minv[2][0]*temp.x + Minv[2][1]*temp.y + Minv[2][2]*temp.z);
	// recentNormal = tempRec;

	return true;
}


Vector3f Sphere::getIntersectionPoint(){
	return recentIntersectionPoint;
}

Vector3f Sphere::getNormalOnIntersectionPoint(){
	return recentNormal;
}

vector<vector<float>> Sphere::getInverseMatrix(vector<vector<float>> mat){
	vector<vector<float>> resultMat;
	int i,j;
	resultMat.assign(3, vector<float>(3,0));
	for (int i=0; i<3; i++) resultMat[i][i] = 0;

	float determinant = 0;
	//finding determinant
	for(i = 0; i < mat.size(); i++){
		determinant = determinant + (mat[0][i] * (mat[1][(i+1)%3] * mat[2][(i+2)%3] - mat[1][(i+2)%3] * mat[2][(i+1)%3]));
	}

	for(i = 0; i < 3; i++){
		for(j = 0; j < 3; j++)
			resultMat[i][j] = ((mat[(j+1)%3][(i+1)%3] * mat[(j+2)%3][(i+2)%3]) - (mat[(j+1)%3][(i+2)%3] * mat[(j+2)%3][(i+1)%3]))/ determinant;
	}
 
   return resultMat;
}

vector<vector<float>> Sphere::getTranspose(vector<vector<float>> m) {
	vector<vector<float>> temp;
	temp.assign(3, vector<float>(3,0));

	for(int i=0; i<m.size(); i++){
		for(int j=0; j<m[0].size(); j++){
			temp[i][j] = m[j][i];
		}
	}
	return temp;
}

Color3f Sphere::getTexture(Vector3f OP){
	float PI = 3.141592654;
	float TWOPI = 6.283185308;

	// CP = OP - OC
	Vector3f CP = OP - this->center;
	Vector3f Xaxis(1,0,0), Zaxis(0,0,1);

	float theta = acos(CP.dot(Zaxis)/CP.length());
	float phi = acos(CP.dot(Xaxis)/CP.length());

	Vector3f v(this->radius*sin(theta)*cos(phi), this->radius*sin(theta)*sin(phi), this->radius*cos(theta));

	float s;
	float t = acos(v.z/this->radius) / PI;
	if (v.y >= 0)
		s = acos(v.x/(this->radius * sin(PI*(t)))) / TWOPI;
	else
		s = (PI + acos(v.x/(this->radius * sin(PI*(t))))) / TWOPI;

	s = abs(s)*(textureCount*10); t=abs(t)*(textureCount*10);
	int s1 = (int)s;
	int t1 = (int)t;
	s1 = s1 % textureCount; t1 = t1 % textureCount;
	return texture.at(t1*textureCount+s1);

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
	vector<Vector3f> points;
	bounds = points;
}

Plane::Plane(Vector3f &p1, Vector3f &p2, Vector3f &p3, Material &m):Object(m){
	point = p1;
	normal = (p1.cross(p2-p1, p3-p2)).normalizeIt();
	vector<Vector3f> points;
	bounds = points;
}

// Plane initialization with a point and normal
Plane::Plane(Vector3f &p, Vector3f &n, vector<Vector3f> &points, Material &m):Object(m){
	point = p;
	// normal = n.normalizeIt();
	normal = (points[0].cross(points[1]-points[0], points[2]-points[1])).normalizeIt();
	bounds = points;
}

// Plane initialization with three points on plane
Plane::Plane(vector<Vector3f> &points, Material &m):Object(m){
	point = points[0];
	normal = (points[0].cross(points[1]-points[0], points[2]-points[1])).normalizeIt();
	bounds = points;
}

bool Plane::getIntersection(Ray3f &ray, float &t){
	float param;
	Vector3f intersectPoint;

	float denom = normal.dot(ray.direction);
	if(denom > 1e-6){
		param = ((point - ray.origin).dot(normal))/((ray.direction).dot(normal));
		
		Vector3f intersectPoint = ray.origin + (ray.direction)*param;

			if((ray.origin).lengthFrom(intersectPoint) > (ray.origin + ray.direction).lengthFrom(intersectPoint)){

				// polygon code here

				if(bounds.size() > 2){
					
					int timesIntersect = 0;
					
					Vector3f dir = (((bounds[0] + bounds[1])/2) - intersectPoint ).normalizeIt();

					for(int i = 0; i < bounds.size(); i++){
						Vector3f p0 = bounds[i];
						Vector3f p1; 	if(i == bounds.size() - 1){ p1 = bounds[0];} 	else{p1 = bounds[i+1];}
						Vector3f pd = (p1-p0).normalizeIt();

						float t1xy = ( ((intersectPoint.y - p0.y)*(-pd.x)) - ((intersectPoint.x - p0.x)*(-pd.y)) )/( ((-pd.y)*(dir.x)) - ((-pd.x)*(dir.y)) );
						float t2xy = -( ((intersectPoint.y - p0.y)*(dir.x)) - ((intersectPoint.x - p0.x)*(dir.y)) )/( ((-pd.y)*(dir.x)) - ((-pd.x)*(dir.y)) );

						float t1xz = ( ((intersectPoint.z - p0.z)*(-pd.x)) - ((intersectPoint.x - p0.x)*(-pd.z)) )/( ((-pd.z)*(dir.x)) - ((-pd.x)*(dir.z)) );
						float t2xz = -( ((intersectPoint.z - p0.z)*(dir.x)) - ((intersectPoint.x - p0.x)*(dir.z)) )/( ((-pd.z)*(dir.x)) - ((-pd.x)*(dir.z)) );

						float t1yz = ( ((intersectPoint.z - p0.z)*(-pd.y)) - ((intersectPoint.y - p0.y)*(-pd.z)) )/( ((-pd.z)*(dir.y)) - ((-pd.y)*(dir.z)) );
						float t2yz = -( ((intersectPoint.z - p0.z)*(dir.y)) - ((intersectPoint.y - p0.y)*(dir.z)) )/( ((-pd.z)*(dir.y)) - ((-pd.y)*(dir.z)) );

						if( (t2xy>=0 && t2xy<=1 && t1xy>=0) || (t2xz>=0 && t2xz<=1 && t1xz>=0) || (t2yz>=0 && t2yz<=1 && t1yz>=0)){
							timesIntersect+=1;
						}
					}

					if( timesIntersect%2 == 0){				
						t = 0.f;
						return false;
					}
				}
				
				// polygon code here
				
				t = param;
				return true;
			}
	}
	recentIntersectionPoint = ray.origin + ray.direction*t;

	t = 0.f;
	return false;
}

Vector3f Plane::getIntersectionPoint(){
	return recentIntersectionPoint;
}

Vector3f Plane::getNormalOnIntersectionPoint(){
	return this->normal;
}

void Plane::print(){
	cout<<"[*] Plane: \n";
	cout<<"Point: "; point.print();
	cout<<"Normal: "; normal.print();
	cout<<"Material: "; material.print();
}

// ------------------------------Plane---------------------------


// // -------------------------------Box----------------------------

// Box::Box(Vector3f &translate, Vector3f &scale, Material &m):Object(m){

// 		// center; lbh
// 		Vector3f vt(0, 0, 0); // reference coordianate
// 		// scale and translate
// 		Vector3f v1 =  (vt)*scale + translate; 
// 		Vector3f v2 = (vt+1.0)*scale + translate;
		
// 		// create normals
// 		Vector3f n1(-1, 0, 0), n2(0, -1, 0), n3(0, 0, -1);
// 		Vector3f n4(1, 0, 0), n5(0, 1, 0), n6(0, 0, 1);

// 		// Transformation t;
// 		// v2 = t.shearingYAboutX(v2,1);
// 		// n1 = t.rotateAboutY(n1,-45);
// 		// n4 = t.rotateAboutY(n4,-45);
// 		// v2.print();
// 		// n1.print();
// 		// n4.print();

// 		// create all side planes
// 		Plane p1(v1, n1, m), p2(v1, n2, m), p3(v1, n3, m);
// 		Plane p4(v2, n4, m), p5(v2, n5, m), p6(v2, n6, m);

// 		planes.push_back(p1);
// 		planes.push_back(p2);
// 		planes.push_back(p3);
// 		planes.push_back(p4);
// 		planes.push_back(p5);
// 		planes.push_back(p6);

// 		Vector3f recentNormal(0.0, 0.0, 0.0);

// 		boundPoints.push_back(v1);
// 		boundPoints.push_back(v2);
// }


// bool Box::getIntersection(Ray3f &ray, float &t){
// 	vector<tuple<float, int>> allParams;

// 	for(int i=0; i<planes.size(); i++){
// 		float t1;
// 		if((planes.at(i)).getIntersection(ray, t1)){
//             // Vector3f iPoint = ray.origin + ray.direction*t1;
//             // Vector3f nVector = (planes.at(i)).getNormalOnIntersectionPoint(iPoint, ray);
// 			allParams.push_back(make_tuple(t1, i));
// 		}	
// 	}

// 	if(allParams.size()==0){
// 		return false;
// 	}
// 	// cout<<allParams.size();

// 	int minIndex = numeric_limits<int>::max();
// 	bool flag = false;
// 	float minT = numeric_limits<float>::max();
// 	vector<tuple<Vector3f, int>> interPointsList;
// 	for(int i=0; i<allParams.size(); i++){

// 		Vector3f interPoint = ray.origin + ray.direction*get<0>(allParams.at(i));

// 		if((interPoint.x <= boundPoints[1].x && interPoint.x >= boundPoints[0].x) || (interPoint.x >= boundPoints[1].x && interPoint.x <= boundPoints[0].x)){
// 		// 	cout<<"*";
// 			if((interPoint.y <= boundPoints[1].y && interPoint.y >= boundPoints[0].y) || (interPoint.y >= boundPoints[1].y && interPoint.y <= boundPoints[0].y)){
// 		// 		cout<<"+";
// 				if((interPoint.z <= boundPoints[1].z && interPoint.z >= boundPoints[0].z) || (interPoint.z >= boundPoints[1].z && interPoint.z <= boundPoints[0].z)){
// 				// 	cout<<"l/"<<endl;
// 					interPointsList.push_back(make_tuple(interPoint, i));
// 					// cout<<flag;	
// 				}
// 			}
// 		}
// 	}

// 	if(interPointsList.size()==0){
// 		return false;
// 	}

// 	float dist = numeric_limits<float>::max();
// 	int minDistIndex = 0;

// 	for(int i=0; i<interPointsList.size(); i++){
// 		if((ray.origin).lengthFrom(get<0>(interPointsList.at(i))) < dist){
// 			dist = (ray.origin).lengthFrom(get<0>(interPointsList.at(i)));
// 			minDistIndex = i;
// 		}
// 	}

// 	recentNormal = planes[get<1>(interPointsList.at(minDistIndex))].getNormalOnIntersectionPoint(get<0>(interPointsList.at(minDistIndex)), ray);

// 	return true;
// }

// Vector3f Box::getNormalOnIntersectionPoint(Vector3f &point, Ray3f &ray){
// 	return recentNormal;
// }

// void Box::print(){
// 	cout<<"Not implemented"<<endl;
// }
// // -------------------------------Box----------------------------



// //--------------------------------Cone----------------------------------

// Cone::Cone(Vector3f c, Vector3f uV, float a, float h, Material &m):Object(m) {
// 	center = c;
// 	upVector = uV.normalizeIt();
// 	alpha = a;
// 	radius = h * tan(a);
// 	height = h;
// }


// bool Cone::getIntersection(Ray3f &ray, float &t) {
// 	vector<float> intersectionPointsParams;

// 	float cos2Alpha = cos(alpha)*cos(alpha);
// 	float sin2Alpha = 1 - cos2Alpha;

// 	Vector3f apexVector = center + upVector * height;
// 	Vector3f downVector = upVector * -1;
// 	Vector3f deltaP = (ray.origin - apexVector);

// 	float projec1 = ray.direction.dot(downVector);
// 	Vector3f vec1 = downVector*projec1;
// 	float projec2 = deltaP.dot(downVector);
// 	Vector3f vec2 = downVector*projec2;

// 	float a = cos2Alpha*((ray.direction - vec1).lengthSquare()) - sin2Alpha*projec1*projec1;
// 	float b = 2*cos2Alpha*((ray.direction - vec1).dot(deltaP - vec2)) - 2 * sin2Alpha*(projec1*projec2);
// 	float c = cos2Alpha*((deltaP - vec2).lengthSquare()) - sin2Alpha*(projec2*projec2);

// 	float discriminant = b*b - 4*a*c;
// 	if (discriminant < 0) return false;
// 	else {
// 		discriminant = sqrt(discriminant);
// 		float t1 = ((-1*b) + discriminant)/(2*a);
// 		float t2 = ((-1*b) - discriminant)/(2*a);
// 		if(t1>=0){
// 			if(upVector.dot((ray.origin - center) + ray.direction*t1)>0 && upVector.dot((ray.origin - apexVector) + ray.direction*t1)<0)
// 				intersectionPointsParams.push_back(t1);
// 		}
// 		if(t2>=0)
// 			if(upVector.dot((ray.origin - center) + ray.direction*t2)>0 && upVector.dot((ray.origin - apexVector) + ray.direction*t2)<0)
// 				intersectionPointsParams.push_back(t2);
// 	}

// 	float denominator = (ray.direction).dot(upVector);
// 	if (denominator > 1e-6) {
// 		Vector3f co = center - ray.origin;
// 		float t3 = co.dot(upVector)/denominator;
// 		if(t3 > 0 && (ray.direction*t3 - co).lengthSquare() <= radius*radius)
// 			intersectionPointsParams.push_back(t3);
// 	}

// 	float minParam = INFINITY;
// 	bool flag = false;
// 	for(int i=0;i<intersectionPointsParams.size();i++){
// 		if(minParam > intersectionPointsParams[i] && intersectionPointsParams[i]>=0) {
// 			minParam = intersectionPointsParams[i];
// 			flag = true;
// 		}
// 	}
// 	if(flag){ t = minParam; return true;}
// 	else return false;
// }

// Vector3f Cone::getNormalOnIntersectionPoint(Vector3f &point, Ray3f &ray){

// 	if(abs((point - center).dot(upVector)) < 1e-4){
// 		return upVector*(-1);
// 	}

// 	Vector3f top = center + upVector * height;
// 	Vector3f perpendicularVec = (upVector * -1).cross((upVector * -1), point - top);

// 	return ((point - top).cross((point - top), perpendicularVec)).normalizeIt();
// }

// void Cone::print(){
// 	cout<<"Not implemented"<<endl;
// }