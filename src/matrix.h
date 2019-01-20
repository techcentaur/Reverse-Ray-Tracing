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
		void print();
};

#endif