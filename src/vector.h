#ifndef VECTOR_H
#define VECTOR_H

class Vector{

public:
	double x, y, z;

	Vector();
	Vector(double);
	Vector(double, double, double);

	Vector operator * (double);
	Vector operator + (double);
	Vector operator * (Vector &vec);
	Vector operator + (Vector &vec);
	Vector operator - (Vector &vec);
	Vector operator / (Vector &vec);

	Vector& operator+=(const Vector &vec);
	Vector& operator*=(const Vector &vec);

	bool operator == (Vector &vec);

	double length();
	double lengthSquare();
	double dot(Vector &vec);
	void normalize();

	Vector normalizeIt(Vector &vec);
	Vector cross(Vector &vec1, Vector &vec2);

	void print();

};

#endif
