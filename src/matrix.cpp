#include <cmath>
#include <vector>
#include <iostream>
#include <algorithm>

#include "matrix.h"

using namespace std;

Matrix::Matrix(){
	mat.assign(4, vector<double>(4,0));
	for (int i=0; i<4; i++) mat[i][i] = 1;
}

void Matrix::print(){
	for(int i=0; i<4; i++){
		for(int j=0; j<4; j++){
			cout<<mat[i][j]<<" ";
		}
		cout<<endl;	
	}
}