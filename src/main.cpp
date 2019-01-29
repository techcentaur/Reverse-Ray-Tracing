/* Writing Main file and main function */

#include <iostream>
#include <fstream>
#include <vector>
#include <limits>
#include <cmath>
#include <tuple>
#include  <typeinfo>
#include <cstring>


#include "color.h"
#include "object.h"
#include "vector.h"
#include "ray.h"
#include "material.h"
#include "light.h"
#include "tracer.h"

using namespace std;

int main(int argc, char** argv){
    Color3f c1(0.3, 0.8, 0.7), c2(0.2, 0.9, 0.3), c3(0.5, 0.1, 0.1);
    Color3f violet(0.6, 0, 0.8), indigo(0.26, 0, 0.56), blue(0, 0, 1);
    Color3f orange(1, 0.5, 0), white(1.0, 1.0, 1.0);
    Color3f mirrorColor(1.0, 1.0, 1.0), glassColor(0.6, 0.7, 0.8);

    Material m1, m2, m3, mv, mi, mb, mo, mr, mirror, glass;
    m1.fillColor(c1, 20.f, 1, 0.1, 0.5);
    m2.fillColor(c2, 30.f, 1, 0.8, 0.3);
    m3.fillColor(c3, 50.f, 0.3, 2, 0.1);
    mv.fillColor(violet, 20.f, 0.1, 2.5, 0.3);
    mi.fillColor(indigo, 20.f, 0.2, 0.6, 0.2);
    mb.fillColor(blue, 20.f, 0.2, 1.3, 0.3);
    mo.fillColor(orange, 20.f, 0.4, 0.9, 0.2);
    mr.fillColor(white, 20.f, 1, 1, 0.1);
    mirror.fillColor(mirrorColor, 1000.f, 10.0, 0.0, 0.8);
    glass.fillColor(glassColor, 200.f, 0.5, 0.0, 0.1, 0.8, 1.5);

    vector<Object*> objectList;
    
    Vector3f v1(-3.f, 0.f, -16.f);
    Vector3f v2(-1.1, -1.5, -12.f), v3(-5, -8, -23.f);
    Vector3f vv(-1.f, 5.f, -20.f), vi(-1.f, 2.f, -20.f), vb(-1.f, -2.f, -20.f);
    Vector3f vo(-1.f, -5.f, -20.f), vr(-1.f, -10.f, -20.f);

    Object* s1 = new Sphere(3.f, v1, m1);
    Object* s2 = new Sphere(1.f, v2, glass);
    Object* s3 = new Sphere(3.f, v3, m3);
    Object *sv = new Sphere(1.f, vv, mv);
    Object *si = new Sphere(1.f, vi, mi);
    Object *sb = new Sphere(1.f, vb, mirror);
    Object *so = new Sphere(1.f, vo, mo);
    Object *sr = new Sphere(1.f, vr, mr);

    objectList.push_back(s1);
    objectList.push_back(s2);
    objectList.push_back(s3);
    objectList.push_back(sv);
    objectList.push_back(si);
    objectList.push_back(sb);
    objectList.push_back(so);
    objectList.push_back(sr);


    vector<Light*> lightSourcesList;

    Vector3f src1(-50.f, -30.f, -30.f);
    Vector3f src2(0.f, 0.f, -20.f);
    Vector3f src3(20.f, 10.f, 10.f);

    Light *l1 = new Light(src1, 1.2);
    Light *l2 = new Light(src2, 1.8);
    Light *l3 = new Light(src3, 1.7);

    lightSourcesList.push_back(l1);
    lightSourcesList.push_back(l2);
    lightSourcesList.push_back(l3);

    // Vector3f vp1(-2, 0, 5), vp2(-2, 7,6), vp3(-2, 2,5);
    // Color3f cp1(1, 1, 1);
    // Material mp1;
    // mp1.fillColor(cp1, 2.f, 1, 1);

    // // vector <Plane*> planesList;

    // Plane *p1 = new Plane(vp1, vp2, vp3, mp1);
    // planesList.push_back(p1);

    string fileName = argv[1];

    Tracer rayTracer;
    rayTracer.writeImage(objectList, lightSourcesList, fileName, true);

    return 0;
}