#ifndef VECTOR_H
#define VECTOR_H

class Vector3f{

public:
	float x, y, z;

	Vector3f();
	Vector3f(const Vector3f &v);
	Vector3f(float u, float v, float w);

	// Vector3f operator = (const Vector3f &vec);
	Vector3f operator * (float d);
	Vector3f operator + (float d);
	Vector3f operator * (const Vector3f &vec);
	Vector3f operator + (const Vector3f &vec);
	Vector3f operator - (const Vector3f &vec);
	Vector3f operator / (const Vector3f &vec);
	Vector3f operator = (const Vector3f &vec);

	Vector3f& operator+=(const Vector3f &vec);
	Vector3f& operator*=(const Vector3f &vec);

	bool operator == (const Vector3f &vec);

	float length();
	float lengthSquare();
	float dot(const Vector3f &vec);
	void normalize();

	Vector3f normalizeIt();
	Vector3f cross(const Vector3f &vec1, const Vector3f &vec2);

	void print();

};

#endif
