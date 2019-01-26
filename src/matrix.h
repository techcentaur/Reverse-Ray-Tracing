#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <vector>

#include "vector.h"

using namespace std;


class Matrix{
	public:
		vector< vector<double> > mat;
		
		Matrix();
		Matrix(int, int);
		Matrix(const Vector3f &vec);
		Matrix(const Matrix &m);
		void print();

		Vector3f toVector3f();

		Matrix operator * (const Matrix &m);
		Matrix operator = (const Matrix &m);

		Matrix transpose();
		Matrix inverse();
};

#endif