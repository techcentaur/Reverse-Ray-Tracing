#ifndef VECTOR_H
#define VECTOR_H

class Vector{

public:
	double x, y, z;

	Vector();
	Vector(double);
	Vector(double, double, double);

	Vector operator * (Vector const &vec);

	void represent() const;

};

#endif