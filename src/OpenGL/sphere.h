#ifndef SPHERE_H
#define SPHERE_H

class Sphere{
public:
    float radius;
    float centerX, centerY, centerZ;
    
    Sphere();
    Sphere(float r, float x, float y, float z, float colorR, float colorG, float colorB);


    void init();
    
    void translate(float x, float y, float z);
    void rotate(float x, float y, float z);
    void scale(float x, float y, float z);

    void reshape(int x, int y);
};

#endif
