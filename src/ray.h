#ifndef RAY_H
#define RAY_H
#ifndef VECTOR_H
#define VECTOR_H

class Ray{

public:
	Vector origin, direction;

	Ray();
	Ray(Vector, Vector);

	double dot(Ray &r);

	void represent();
}