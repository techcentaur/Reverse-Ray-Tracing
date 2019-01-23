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
		Matrix(Matrix &m);
		void print();
		

		Vector3f transform();
		Matrix operator * (const Matrix &m);

		Matrix transpose();
		Matrix inverse();
};

#endif