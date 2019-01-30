#ifndef READER_H
#define READER_H

#include <iostream>
#include <fstream>
#include <vector>
#include <limits>
#include <cmath>
#include <tuple>
#include <typeinfo>
#include <cstring>

#include "tracer.h"
#include "color.h"
#include "object.h"
#include "vector.h"
#include "ray.h"
#include "material.h"
#include "camera.h"
#include "light.h"

using namespace std;

class Reader{
public:

	Reader();

	tuple<vector<Object*>, vector<Light*>, Camera> readFile(string fileName){
	
		ifstream ifs;
		ifs.open(fileName, ios::in);
		if(!ifs.is_open()) {
			cout<<"Error opening file"<<endl;
		}

		vector<Object*> objects;
		vector<Light*> lights;
		Camera cam;

		while(ifs.good()){
			string type;
			ifs>>type;
			if(type == "LIGHTS") {
				while(ifs.good()){
					ifs>>type;
					if(type=="LIGHT"){
						Vector3f pos;
						float intensity;
						ifs>>pos.x>>pos.y>>pos.z>>intensity;
						Light *l1 = new Light(pos, intensity);
						lights.push_back(l1);
					}
					else{
						break;
					}
				}
			}
			else if(type=="CAMERA"){
				Vector3f lookFrom, lookAt, viewUp;
				float fov, height, width, sSampling, recursionDepth;
				while(ifs.good()){
					ifs>>type;
					if(type == "LOOKFROM"){
						ifs>>lookFrom.x>>lookFrom.y>>lookFrom.z;
					}
					else if(type == "LOOKAT") {
						ifs>>lookAt.x>>lookAt.y>>lookAt.z;
					}
					else if(type == "VIEWUP") {
						ifs>>viewUp.x>>viewUp.y>>viewUp.z;
					}
					else if(type == "DIMENSIONS") {
						ifs>>width>>height;
					}
					else if(type == "FOV") {
						ifs>>fov;
					}
					else if(type == "SUPERSAMPLING") {
						ifs>>sSampling;
					}
					else if(type == "RECURSION_DEPTH") {
						ifs>>recursionDepth;
					}
					else{
						break;
					}
				}
				cam.formCamera(lookFrom, lookAt, viewUp, fov, width, height, sSampling, recursionDepth);
			}
			else if(type == "OBJECTS") {
				while(ifs.good()){
					ifs>>type;
					Vector3f origin;
					Color3f color;
					float sRE, sRC, dRC, reflecC, refracC, rI, radius;
					if(type == "SPHERE"){
						while(ifs.good()){
							ifs>>type;
							if(type=="COLOR"){
								ifs>>color.r>>color.g>>color.b;
							}
							else if(type=="SPECULAR_REFLECTION_EXPONENT"){
								ifs>>sRE;
							}
							else if(type=="SPECULAR_REFLECTION_COEFF"){
								ifs>>sRC;
							}
							else if(type=="DIFFUSE_REFLECTION_COEFF"){
								ifs>>dRC;
							}
							else if(type=="REFLECTION_COEFF"){
								ifs>>reflecC;
							}
							else if(type=="REFRACTION_COEFF"){
								ifs>>refracC;
							}
							else if(type=="REFRACTIVE_INDEX"){
								ifs>>rI;
							}
							else if(type=="ORIGIN"){
								ifs>>origin.x>>origin.y>>origin.z;
							}
							else if(type=="RADIUS"){
								ifs>>radius;
							}
							else {
								break;
							}
						}
					}
					Material m;
					m.fillColor(color, sRE, sRC, dRC, reflecC, refracC, rI);
					Object* s = new Sphere(radius, origin, m);
					objects.push_back(s);
					}
				}
				else if(type == "CUT"){
					break;
				}
			}

			return make_tuple(objects, lights, cam);
		}
};

#endif