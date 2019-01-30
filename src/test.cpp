#include <iostream>
#include <vector>
#include <cmath>

#include "color.h"
#include "vector.h"
#include "transformation.h"
#include "box.h"
#include "material.h"
using namespace std;

int main(){
          Vector3f c(0.5,1.f,1.5);

          Color3f c1(0.3, 0.8, 0.7);
          Material m1;
          m1.fillColor(c1, 20.f, 1, 0.1, 0.5);
          
          cout<<cos(-M_PI_2);
          // m = Transformation::rotateAboutZ(n, 90.f);
          // m.print();
          Box b(1.f, 2.f, 3.f,c,m1);
          b.print();
}