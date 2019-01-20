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
Matrix::Matrix(Matrix &m){
	this->mat.assign(4, vector<double>(4, 0));

	for(int i=0; i<4; i++) this->mat[i][j] = 1;

	for(int i=0; i<4; i++){
		for(int j=0; j<4; j++){
			this->mat[i][j] = m.mat[i][j];
		}
	}
}

Matrix Matrix::operator * (const Matrix &m){
	Matrix temp;
	for(int i=0; i<4; i++){
		for(int j=0; j<4; j++){
			for(int k=0; k<4; k++){
				temp.mat[i][j] += this->mat[i][k] * m.mat[k][j];
			}
		}
	}
}

Vector Matrix::transform(Vector &v) {
}


Matrix Matrix::transpose() {
	Matrix temp;
	for(int i=0; i<4; i++){
		for(int j=0; j<4; j++){
			temp.mat[i][j] = this->mat[j][i];
		}
	}
}

Matrix Matrix::inverse(){
}

void Matrix::print(){
	for(int i=0; i<4; i++){
		for(int j=0; j<4; j++){
			cout<<mat[i][j]<<" ";
		}
		cout<<endl;	
	}
}

