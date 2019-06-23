#pragma once

/* 	
	Copyright Affonso Amendola 2019

	Fofonso's Matrix, version 1.0

	This is part of my standard usage library, I use this in many of my things, it's pretty kewl.

	Distributed under GPLv3, use it to your hearts content,
	just remember the number one rule:

	Be Excellent to Each Other.
*/

class Vector3;

class Matrix33
{
private:
	double m_contents[9];
public:
	Matrix33();
	Matrix33(double contents[9]);
	Matrix33(std::initializer_list<double> contents);

	double get_value(int column, int row);
	void set_value(int column, int row, double value);

	double determinant();

	Matrix33 transpose();

	Matrix33& operator+= (Matrix33& m);
	Matrix33& operator+= (double s);
	Matrix33& operator-= (Matrix33& m);
	Matrix33& operator-= (double s);
	Matrix33& operator*= (double s);
	Matrix33& operator/= (double s);

	Matrix33 operator- ();
	Vector3 operator* (Vector3& v);

	void print();
};

Matrix33 operator+ (Matrix33& matrix_a, Matrix33& matrix_b);
Matrix33 operator- (Matrix33& matrix_a, Matrix33& matrix_b);

Matrix33 operator+ (Matrix33& matrix_a, double s);
Matrix33 operator+ (double s, Matrix33& matrix_b);

Matrix33 operator- (Matrix33& matrix_a, double s);
Matrix33 operator- (double s, Matrix33& matrix_b);

Matrix33 operator* (Matrix33& matrix_a, double s);
Matrix33 operator* (double s, Matrix33& matrix_b);

Matrix33 operator/ (Matrix33& matrix_a, double s);

Matrix33 operator* (Matrix33& matrix_a, Matrix33& matrix_b);


const Matrix33 IDENTITY_MATRIX({1., 0., 0., 0., 1., 0., 0., 0., 1.});
