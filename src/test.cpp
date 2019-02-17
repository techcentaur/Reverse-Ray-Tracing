#include <iostream>
#include <vector>
// #include <cmath>
// #include <GL/glut.h>
#include "vector.h"
// #include "transformation.h"

using namespace std;
 
void displayMe(void)
{
    // glClear(GL_COLOR_BUFFER_BIT);
    // glBegin(GL_POLYGON);
    //     glVertex3f(0.5, 0.0, 0.5);
    //     glVertex3f(0.5, 0.0, 0.0);
    //     glVertex3f(0.0, 0.5, 0.0);
    //     glVertex3f(0.0, 0.0, 0.5);
    // glEnd();
    // glFlush();
}
 
int main(int argc, char** argv)
{
    Vector3f intersectPoint(1.1,1.1,0);
    
    vector<Vector3f> bounds;
    
    bounds.push_back(Vector3f(0,0,0));
    bounds.push_back(Vector3f(0,1,0));
    bounds.push_back(Vector3f(1,0,0));
    
    int timesIntersect = 0;
    
    Vector3f dir = (((bounds[0] + bounds[1])/2) - intersectPoint ).normalizeIt();
    
    // Vector3f dir = Vector3f((static_cast <float> (rand()) / static_cast <float> (RAND_MAX)),(static_cast <float> (rand()) / static_cast <float> (RAND_MAX)),0).normalizeIt();
    dir.print();

    for(int i = 0; i < bounds.size(); i++){
        Vector3f p0 = bounds[i];
        Vector3f p1; 	if(i == bounds.size() - 1){ p1 = bounds[0];} 	else{p1 = bounds[i+1];}
        Vector3f pd = (p1-p0).normalizeIt();
        cout<<endl;
        p0.print();
        p1.print(); pd.print();

        // t1 = (c2*b1 - c1*b2)/(b2*a1 - b1*a2)
        // t2 = (c2*a1 - c1*a2)/(b2*a1 - b1*a2)
        float t1xy = ( ((intersectPoint.y - p0.y)*(-pd.x)) - ((intersectPoint.x - p0.x)*(-pd.y)) )/( ((-pd.y)*(dir.x)) - ((-pd.x)*(dir.y)) );
        float t2xy = ( ((intersectPoint.y - p0.y)*(dir.x)) - ((intersectPoint.x - p0.x)*(dir.y)) )/( ((-pd.y)*(dir.x)) - ((-pd.x)*(dir.y)) );
        cout << "t1xy: " << t1xy << " t2xy: " << t2xy << endl;

        float t1xz = ( ((intersectPoint.z - p0.z)*(-pd.x)) - ((intersectPoint.x - p0.x)*(-pd.z)) )/( ((-pd.z)*(dir.x)) - ((-pd.x)*(dir.z)) );
        float t2xz = ( ((intersectPoint.z - p0.z)*(dir.x)) - ((intersectPoint.x - p0.x)*(dir.z)) )/( ((-pd.z)*(dir.x)) - ((-pd.x)*(dir.z)) );
        cout << "t1xz: " << t1xz << " t2xz: " << t2xz << endl;

        float t1yz = ( ((intersectPoint.z - p0.z)*(-pd.y)) - ((intersectPoint.y - p0.y)*(-pd.z)) )/( ((-pd.z)*(dir.y)) - ((-pd.y)*(dir.z)) );
        float t2yz = ( ((intersectPoint.z - p0.z)*(dir.y)) - ((intersectPoint.y - p0.y)*(dir.z)) )/( ((-pd.z)*(dir.y)) - ((-pd.y)*(dir.z)) );
        cout << "t1yz: " << t1yz << " t2yz: " << t2yz << endl;
        
        // float t1xy = ((p0.y - intersectPoint.y) - (((intersectPoint.x - p0.x)*pd.y)/pd.x) )/(((dir.x*pd.y)/pd.x) - dir.y);
        // float t2xy = ((intersectPoint.y - p0.y) + (((p0.x - intersectPoint.x)*dir.y)/dir.x) )/(pd.y - ((pd.x*dir.y)/dir.x) );

        // float t1xz = ((p0.z - intersectPoint.z) - (((intersectPoint.x - p0.x)*pd.z)/pd.x) )/(((dir.x*pd.z)/pd.x) - dir.z);
        // float t2xz = ((intersectPoint.z - p0.z) + (((p0.z - intersectPoint.x)*dir.z)/dir.x) )/(pd.z - ((pd.x*dir.z)/dir.x) );

        // float t1yz = ((p0.z - intersectPoint.z) - (((intersectPoint.y - p0.y)*pd.z)/pd.y) )/(((dir.y*pd.z)/pd.y) - dir.z);
        // float t2yz = ((intersectPoint.z - p0.z) + (((p0.z - intersectPoint.y)*dir.z)/dir.y) )/(pd.z - ((pd.y*dir.z)/dir.y) );

        if( (t2xy>=0 && t2xy<=1 && t1xy>=0) || (t2xz>=0 && t2xz<=1 && t1xz>=0) || (t2yz>=0 && t2yz<=1 && t1yz>=0)){
            cout<<"Intersect+1"<<endl;
            timesIntersect+=1;
        }
        cout<<(t1xy>=0)<<(t2xy>=0)<<(t2xy<=1);
        cout<<(t1xz>=0)<<(t2xz>=0)<<(t2xz<=1);
        cout<<(t1yz>=0)<<(t2yz>=0)<<(t2yz<=1)<<endl;

    }

    if( timesIntersect%2 == 0){
        cout<<endl<<"outside"<<endl;
        return 0;
    }
    else{cout<<endl<<"inside"<<endl;}

    return 1;
}
