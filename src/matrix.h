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
		void operator = (const Matrix &m);

		Matrix transpose();
		double determinant2(const Matrix &m);
		double determinant3(const Matrix &m);
		double determinant4(const Matrix &m);

		Matrix inverse(const Matrix &m);
};

#endif