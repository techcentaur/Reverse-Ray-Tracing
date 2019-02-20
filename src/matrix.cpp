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

	if(mat[0].size() != m.mat.size()){throw invalid_argument( "sizes of matrices dont match for multiplication" );}

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
	if(mat[0].size() != 1 && mat.size() != 4){throw invalid_argument( "matrix is not of size 4*1. Can't be converted to Vector3f" );}
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

double Matrix::determinant2(const Matrix &m){
	// only for 2X2
	double D = (m.mat[0][0]*m.mat[1][1])-(m.mat[0][1]*m.mat[1][0]);
	return D;
}

double Matrix::determinant3(const Matrix &m){
	// only for 3X3
	double D = ( ((m.mat[0][0]) * ((m.mat[1][1]*m.mat[2][2])-(m.mat[1][2]*m.mat[2][1]))) - ((m.mat[0][1]) * ((m.mat[1][0]*m.mat[2][2])-(m.mat[1][2]*m.mat[2][0]))) + ((m.mat[0][2]) * ((m.mat[1][0]*m.mat[2][1])-(m.mat[1][1]*m.mat[2][0]))) );
	return D;
}

double Matrix::determinant4(const Matrix &m){
	// only for 4X4
	double D = 0;
 	
	// A00
	Matrix A00(3,3);
	A00.mat[0][0] = m.mat[1][1];
	A00.mat[0][1] = m.mat[1][2];
	A00.mat[0][2] = m.mat[1][3];
	A00.mat[1][0] = m.mat[2][1];
	A00.mat[1][1] = m.mat[2][2];
	A00.mat[1][2] = m.mat[2][3];
	A00.mat[2][0] = m.mat[3][1];
	A00.mat[2][1] = m.mat[3][2];
	A00.mat[2][2] = m.mat[3][3];
	D += m.mat[0][0]*determinant3(A00);


	//A01
	Matrix A01(3,3);
	A01.mat[0][0] = m.mat[1][0];
	A01.mat[0][1] = m.mat[1][2];
	A01.mat[0][2] = m.mat[1][3];
	A01.mat[1][0] = m.mat[2][0];
	A01.mat[1][1] = m.mat[2][2];
	A01.mat[1][2] = m.mat[2][3];
	A01.mat[2][0] = m.mat[3][0];
	A01.mat[2][1] = m.mat[3][2];
	A01.mat[2][2] = m.mat[3][3];
	D -= m.mat[0][1]*determinant3(A01);

	//A02
	Matrix A02(3,3);
	A02.mat[0][0] = m.mat[1][0];
	A02.mat[0][1] = m.mat[1][1];
	A02.mat[0][2] = m.mat[1][3];
	A02.mat[1][0] = m.mat[2][0];
	A02.mat[1][1] = m.mat[2][1];
	A02.mat[1][2] = m.mat[2][3];
	A02.mat[2][0] = m.mat[3][0];
	A02.mat[2][1] = m.mat[3][1];
	A02.mat[2][2] = m.mat[3][3];
	D += m.mat[0][2]*determinant3(A02);

	//A03
	Matrix A03(3,3);
	A01.mat[0][0] = m.mat[1][0];
	A01.mat[0][1] = m.mat[1][1];
	A01.mat[0][2] = m.mat[1][2];
	A01.mat[1][0] = m.mat[2][0];
	A01.mat[1][1] = m.mat[2][1];
	A01.mat[1][2] = m.mat[2][2];
	A01.mat[2][0] = m.mat[3][0];
	A01.mat[2][1] = m.mat[3][1];
	A01.mat[2][2] = m.mat[3][2];
	D -= m.mat[0][3]*determinant3(A03);

	return D;
}

Matrix Matrix::inverse(const Matrix &m){
	// only for 4X4
	double D = this->determinant4(m);
	Matrix Cij(m);

	//A00
	Matrix A00(3,3);
	A00.mat[0][0] = m.mat[1][1];
	A00.mat[0][1] = m.mat[1][2];
	A00.mat[0][2] = m.mat[1][3];
	A00.mat[1][0] = m.mat[2][1];
	A00.mat[1][1] = m.mat[2][2];
	A00.mat[1][2] = m.mat[2][3];
	A00.mat[2][0] = m.mat[3][1];
	A00.mat[2][1] = m.mat[3][2];
	A00.mat[2][2] = m.mat[3][3];
	Cij.mat[0][0] = determinant3(A00);
	//A01
	Matrix A01(3,3);
	A01.mat[0][0] = m.mat[1][0];
	A01.mat[0][1] = m.mat[1][2];
	A01.mat[0][2] = m.mat[1][3];
	A01.mat[1][0] = m.mat[2][0];
	A01.mat[1][1] = m.mat[2][2];
	A01.mat[1][2] = m.mat[2][3];
	A01.mat[2][0] = m.mat[3][0];
	A01.mat[2][1] = m.mat[3][2];
	A01.mat[2][2] = m.mat[3][3];
	Cij.mat[0][1] = -determinant3(A01);
	//A02
	Matrix A02(3,3);
	A02.mat[0][0] = m.mat[1][0];
	A02.mat[0][1] = m.mat[1][1];
	A02.mat[0][2] = m.mat[1][3];
	A02.mat[1][0] = m.mat[2][0];
	A02.mat[1][1] = m.mat[2][1];
	A02.mat[1][2] = m.mat[2][3];
	A02.mat[2][0] = m.mat[3][0];
	A02.mat[2][1] = m.mat[3][1];
	A02.mat[2][2] = m.mat[3][3];
	Cij.mat[0][2] = determinant3(A02);
	//A03
	Matrix A03(3,3);
	A01.mat[0][0] = m.mat[1][0];
	A01.mat[0][1] = m.mat[1][1];
	A01.mat[0][2] = m.mat[1][2];
	A01.mat[1][0] = m.mat[2][0];
	A01.mat[1][1] = m.mat[2][1];
	A01.mat[1][2] = m.mat[2][2];
	A01.mat[2][0] = m.mat[3][0];
	A01.mat[2][1] = m.mat[3][1];
	A01.mat[2][2] = m.mat[3][2];
	Cij.mat[0][3] = -determinant3(A03);


	//A10	
	Matrix A10(3,3);
	A10.mat[0][0] = m.mat[0][1];
	A10.mat[0][1] = m.mat[0][2];
	A10.mat[0][2] = m.mat[0][3];
	A10.mat[1][0] = m.mat[2][1];
	A10.mat[1][1] = m.mat[2][2];
	A10.mat[1][2] = m.mat[2][3];
	A10.mat[2][0] = m.mat[3][1];
	A10.mat[2][1] = m.mat[3][2];
	A10.mat[2][2] = m.mat[3][3];
	Cij.mat[1][0] = -determinant3(A10);
	//A11	
	Matrix A11(3,3);
	A11.mat[0][0] = m.mat[0][0];
	A11.mat[0][1] = m.mat[0][2];
	A11.mat[0][2] = m.mat[0][3];
	A11.mat[1][0] = m.mat[2][0];
	A11.mat[1][1] = m.mat[2][2];
	A11.mat[1][2] = m.mat[2][3];
	A11.mat[2][0] = m.mat[3][0];
	A11.mat[2][1] = m.mat[3][2];
	A11.mat[2][2] = m.mat[3][3];
	Cij.mat[1][1] = determinant3(A11);
	//A12	
	Matrix A12(3,3);
	A12.mat[0][0] = m.mat[0][0];
	A12.mat[0][1] = m.mat[0][1];
	A12.mat[0][2] = m.mat[0][3];
	A12.mat[1][0] = m.mat[2][0];
	A12.mat[1][1] = m.mat[2][1];
	A12.mat[1][2] = m.mat[2][3];
	A12.mat[2][0] = m.mat[3][0];
	A12.mat[2][1] = m.mat[3][1];
	A12.mat[2][2] = m.mat[3][3];
	Cij.mat[1][2] = -determinant3(A12);
	//A13	
	Matrix A13(3,3);
	A13.mat[0][0] = m.mat[0][0];
	A13.mat[0][1] = m.mat[0][1];
	A13.mat[0][2] = m.mat[0][2];
	A13.mat[1][0] = m.mat[2][0];
	A13.mat[1][1] = m.mat[2][1];
	A13.mat[1][2] = m.mat[2][2];
	A13.mat[2][0] = m.mat[3][0];
	A13.mat[2][1] = m.mat[3][1];
	A13.mat[2][2] = m.mat[3][2];
	Cij.mat[1][3] = determinant3(A13);


	//A20	
	Matrix A20(3,3);
	A20.mat[0][0] = m.mat[0][1];
	A20.mat[0][1] = m.mat[0][2];
	A20.mat[0][2] = m.mat[0][3];
	A20.mat[1][0] = m.mat[1][1];
	A20.mat[1][1] = m.mat[1][2];
	A20.mat[1][2] = m.mat[1][3];
	A20.mat[2][0] = m.mat[3][1];
	A20.mat[2][1] = m.mat[3][2];
	A20.mat[2][2] = m.mat[3][3];
	Cij.mat[2][0] = determinant3(A20);
	//A21	
	Matrix A21(3,3);
	A21.mat[0][0] = m.mat[0][0];
	A21.mat[0][1] = m.mat[0][2];
	A21.mat[0][2] = m.mat[0][3];
	A21.mat[1][0] = m.mat[1][0];
	A21.mat[1][1] = m.mat[1][2];
	A21.mat[1][2] = m.mat[1][3];
	A21.mat[2][0] = m.mat[3][0];
	A21.mat[2][1] = m.mat[3][2];
	A21.mat[2][2] = m.mat[3][3];
	Cij.mat[2][1] = -determinant3(A21);
	//A22	
	Matrix A22(3,3);
	A22.mat[0][0] = m.mat[0][0];
	A22.mat[0][1] = m.mat[0][1];
	A22.mat[0][2] = m.mat[0][3];
	A22.mat[1][0] = m.mat[1][0];
	A22.mat[1][1] = m.mat[1][1];
	A22.mat[1][2] = m.mat[1][3];
	A22.mat[2][0] = m.mat[3][0];
	A22.mat[2][1] = m.mat[3][1];
	A22.mat[2][2] = m.mat[3][3];
	Cij.mat[2][2] = determinant3(A22);
	//A23	
	Matrix A23(3,3);
	A23.mat[0][0] = m.mat[0][0];
	A23.mat[0][1] = m.mat[0][1];
	A23.mat[0][2] = m.mat[0][2];
	A23.mat[1][0] = m.mat[1][0];
	A23.mat[1][1] = m.mat[1][1];
	A23.mat[1][2] = m.mat[1][2];
	A23.mat[2][0] = m.mat[3][0];
	A23.mat[2][1] = m.mat[3][1];
	A23.mat[2][2] = m.mat[3][2];
	Cij.mat[2][3] = -determinant3(A23);


	//A30	
	Matrix A30(3,3);
	A30.mat[0][0] = m.mat[0][1];
	A30.mat[0][1] = m.mat[0][2];
	A30.mat[0][2] = m.mat[0][3];
	A30.mat[1][0] = m.mat[1][1];
	A30.mat[1][1] = m.mat[1][2];
	A30.mat[1][2] = m.mat[1][3];
	A30.mat[2][0] = m.mat[2][1];
	A30.mat[2][1] = m.mat[2][2];
	A30.mat[2][2] = m.mat[2][3];
	Cij.mat[3][0] = -determinant3(A30);
	//A31	
	Matrix A31(3,3);
	A31.mat[0][0] = m.mat[0][0];
	A31.mat[0][1] = m.mat[0][2];
	A31.mat[0][2] = m.mat[0][3];
	A31.mat[1][0] = m.mat[1][0];
	A31.mat[1][1] = m.mat[1][2];
	A31.mat[1][2] = m.mat[1][3];
	A31.mat[2][0] = m.mat[2][0];
	A31.mat[2][1] = m.mat[2][2];
	A31.mat[2][2] = m.mat[2][3];
	Cij.mat[3][1] = determinant3(A31);
	//A32	
	Matrix A32(3,3);
	A32.mat[0][0] = m.mat[0][0];
	A32.mat[0][1] = m.mat[0][1];
	A32.mat[0][2] = m.mat[0][3];
	A32.mat[1][0] = m.mat[1][0];
	A32.mat[1][1] = m.mat[1][1];
	A32.mat[1][2] = m.mat[1][3];
	A32.mat[2][0] = m.mat[2][0];
	A32.mat[2][1] = m.mat[2][1];
	A32.mat[2][2] = m.mat[2][3];
	Cij.mat[3][2] = -determinant3(A32);
	//A33	
	Matrix A33(3,3);
	A33.mat[0][0] = m.mat[0][0];
	A33.mat[0][1] = m.mat[0][1];
	A33.mat[0][2] = m.mat[0][2];
	A33.mat[1][0] = m.mat[1][0];
	A33.mat[1][1] = m.mat[1][1];
	A33.mat[1][2] = m.mat[1][2];
	A33.mat[2][0] = m.mat[2][0];
	A33.mat[2][1] = m.mat[2][1];
	A33.mat[2][2] = m.mat[2][2];
	Cij.mat[3][3] = determinant3(A33);


	Matrix Adj = Cij.transpose();

	for(int i=0; i<mat.size(); i++){
		for(int j=0; j<mat[0].size(); j++){
			Adj.mat[i][j] = Adj.mat[i][j] / D;
		}
	}

	return Adj;

}

void Matrix::print(){
	for(int i=0; i<mat.size(); i++){
		for(int j=0; j<mat[i].size(); j++){
			cout<<mat[i][j]<<" ";
		}
		cout<<endl;	
	}
}

// int main(){
// 	Matrix m;
// 	m.mat[0][0] = 4;

// 	m.mat[1][1] = 5;

// 	m.mat[0][1] = 1;

// 	m.print();
// 	cout<< endl;

// 	Matrix nm = m.inverse(m);
// 	nm.print();
// }