#include <cmath>
#include <vector>
#include <iostream>
#include <algorithm>
#include <stdexcept>
#include "matrix.h"

using namespace std;

// Initialize with unit matrix of size 4
Matrix::Matrix(){
	mat.assign(4, vector<double>(4,0));
	for (int i=0; i<4; i++) mat[i][i] = 1;
}

// Generates a matrix of size x*y
Matrix::Matrix(int x, int y){
	mat.assign(x, vector<double>(y,0));
}

// Converts a Vector3f to a 4*1 matrix
Matrix::Matrix(const Vector3f &vec){
	mat.assign(4, vector<double>(1,1));
	mat[0][0] = vec.x;
	mat[1][0] = vec.y;
	mat[2][0] = vec.z;	
}

Matrix::Matrix(const Matrix &m){
	mat.assign(m.mat.size(), vector<double>(m.mat[0].size(), 0));

	for(int i=0; i<mat.size(); i++){
		for(int j=0; j<mat[0].size(); j++){
			mat[i][j] = m.mat[i][j];
		}
	}
}

Matrix Matrix::operator = (const Matrix &m){
	Matrix temp(mat.size(),m.mat[0].size());

	for(int i=0; i<mat.size(); i++){
		for(int j=0; j<mat[0].size(); j++){
			temp.mat[i][j] = m.mat[i][j];
		}
	}
	return temp;
}

Matrix Matrix::operator * (const Matrix &m){

	if(mat[0].size() != m.mat.size()){throw std::invalid_argument( "sizes of matrices dont match for multiplication" );}

	Matrix temp(mat.size(),m.mat[0].size());

	for(int i=0; i<mat.size(); i++){
		for(int j=0; j<m.mat[0].size(); j++){
			for(int k=0; k<mat[0].size(); k++){
				temp.mat[i][j] += mat[i][k] * m.mat[k][j];
			}
		}
	}
	return temp;
}

Vector3f Matrix::toVector3f() {
	if(mat[0].size() != 1 && mat.size() != 4){throw std::invalid_argument( "matrix is not of size 4*1. Can't be converted to Vector3f" );}
	return Vector3f(mat[0][0], mat[1][0], mat[2][0]);
}

Matrix Matrix::transpose() {
	Matrix temp(mat[0].size(),mat.size());

	for(int i=0; i<mat.size(); i++){
		for(int j=0; j<mat[0].size(); j++){
			temp.mat[i][j] = this->mat[j][i];
		}
	}
	return temp;
}

// Matrix Matrix::inverse(){
// }

void Matrix::print(){
	for(int i=0; i<mat.size(); i++){
		for(int j=0; j<mat[i].size(); j++){
			cout<<mat[i][j]<<" ";
		}
		cout<<endl;	
	}
}

