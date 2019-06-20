#include  <iostream>

/* 	
	Copyright Affonso Amendola 2019

	Fofonso's Matrix, version 1.0

	This is part of my standard usage library, I use this in many of my things, it's pretty kewl.

	Distributed under GPLv3, use it to your hearts content,
	just remember the number one rule:

	Be Excellent to Each Other.
*/

#include "Matrix.hpp"

#if __has_include("Vector.hpp")
#include "Vector.hpp"
#endif

//Constructors
Matrix33::Matrix33(std::initializer_list<double> contents)
{
	std::copy(contents.begin(), contents.end(), this->m_contents);
}

Matrix33::Matrix33(double contents[9])
{
	for(int i = 0; i < 9; i++)
		this->m_contents[i] = contents[i];
}

Matrix33::Matrix33()
{
	for(int i = 0; i < 9; i++)
		this->m_contents[i] = 0.;
} 

//Getter and setter, maybe I could do it with the operator[], but I didnt want to mess with that
double Matrix33::get_value(int column, int row)
{
	if(column <= 3 && column >= 0 && row <= 3 && row >= 0)
		return this->m_contents[column + row * 3];
}

void Matrix33::set_value(int column, int row, double value)
{
	if(column <= 3 && column >= 0 && row <= 3 && row >= 0)
		this->m_contents[column + row * 3] = value;
}

//Determinant calculation, couldve done a generic one using for loops, but feck it

double Matrix33::determinant()
{
	return 	this->m_contents[0]*this->m_contents[4]*this->m_contents[8] + 
			this->m_contents[1]*this->m_contents[5]*this->m_contents[6] +
			this->m_contents[2]*this->m_contents[3]*this->m_contents[7] -
			this->m_contents[2]*this->m_contents[4]*this->m_contents[6] -
			this->m_contents[1]*this->m_contents[3]*this->m_contents[8] -
			this->m_contents[0]*this->m_contents[5]*this->m_contents[7];
}

//Return the transpose of the matrix.

Matrix33 Matrix33::transpose()
{
	Matrix33 transposed(this->m_contents);

	transposed.set_value(1, 0, this->get_value(0,1));
	transposed.set_value(2, 0, this->get_value(0,2));
	transposed.set_value(1, 2, this->get_value(2,1));

	return transposed;
}

//Member operators

Matrix33& Matrix33::operator+=(Matrix33& b_matrix)
{
	for(int x = 0; x < 3; x++)
	{
		for(int y = 0; y < 3; y++)
		{
			this->set_value(x, y, this->get_value(x, y) + b_matrix.get_value(x, y));
		}
	}

	return *this;
}

Matrix33& Matrix33::operator+=(double s)
{
	for(int x = 0; x < 3; x++)
	{
		for(int y = 0; y < 3; y++)
		{
			this->set_value(x, y, this->get_value(x, y) + s);
		}
	}

	return *this;
}

Matrix33& Matrix33::operator-=(Matrix33& b_matrix)
{
	for(int x = 0; x < 3; x++)
	{
		for(int y = 0; y < 3; y++)
		{
			this->set_value(x, y, this->get_value(x, y) - b_matrix.get_value(x, y));
		}
	}

	return *this;
}

Matrix33& Matrix33::operator-=(double s)
{
	return *this += (-s);
}

Matrix33& Matrix33::operator*=(double s)
{
	for(int x = 0; x < 3; x++)
	{
		for(int y = 0; y < 3; y++)
		{
			this->set_value(x, y, this->get_value(x, y) * s);
		}
	}

	return *this;
}

Matrix33& Matrix33::operator/=(double s)
{
	for(int x = 0; x < 3; x++)
	{
		for(int y = 0; y < 3; y++)
		{
			this->set_value(x, y, this->get_value(x, y) / s);
		}
	}

	return *this;
}

Matrix33 Matrix33::operator-()
{
	Matrix33 new_m;

	for(int x = 0; x < 3; x++)
	{
		for(int y = 0; y < 3; y++)
		{
			new_m.set_value(x, y, -(this->get_value(x, y)));
		}
	}

	return new_m;
}


//Only define this function it the Vector.hpp from my utility package has been included
#ifdef _FF_VECTOR_DEF

Vector3 Matrix33::operator*(Vector3& v)
{
	Vector3 new_v;

	double value;

	for(int y = 0; y < 3; y++)
	{	
		value = 0.;

		for(int k = 0; k < 3; k++)
		{
			value += this->get_value(k, y) * v[k];
		}

		new_v[y] = value;
	}

	return new_v;
}
#endif

//Simple print function, didnt want to use cout because fuck formatting with that piece of shit
void Matrix33::print()
{
	printf("%f %f %f\n", this->m_contents[0], this->m_contents[1], this->m_contents[2]);
	printf("%f %f %f\n", this->m_contents[3], this->m_contents[4], this->m_contents[5]);
	printf("%f %f %f\n", this->m_contents[6], this->m_contents[7], this->m_contents[8]);
}

//Non member operators
Matrix33 operator+(Matrix33& a_matrix, Matrix33& b_matrix)
{
	Matrix33 new_m;

	for(int x = 0; x < 3; x++)
	{
		for(int y = 0; y < 3; y++)
		{
			new_m.set_value(x, y, a_matrix.get_value(x, y) + b_matrix.get_value(x, y));
		}
	}

	return new_m;
}

Matrix33 operator+(Matrix33& a_matrix, double s)
{
	Matrix33 new_m;

	for(int x = 0; x < 3; x++)
	{
		for(int y = 0; y < 3; y++)
		{
			new_m.set_value(x, y, a_matrix.get_value(x, y) + s);
		}
	}

	return new_m;
}

Matrix33 operator+(double s, Matrix33& b_matrix)
{
	return b_matrix + s;
}

Matrix33 operator-(Matrix33& a_matrix, double s)
{
	return a_matrix + (-s);
}

Matrix33 operator-(double s, Matrix33& b_matrix)
{
	Matrix33 new_m;

	for(int x = 0; x < 3; x++)
	{
		for(int y = 0; y < 3; y++)
		{
			new_m.set_value(x, y, s - b_matrix.get_value(x, y));
		}
	}

	return new_m;
}

Matrix33 operator*(Matrix33& a_matrix, Matrix33& b_matrix)
{
	Matrix33 new_m;

	double value;

	for(int x = 0; x < 3; x++)
	{
		for(int y = 0; y < 3; y++)
		{	
			value = 0.;

			for(int k = 0; k < 3; k++)
			{
				value += a_matrix.get_value(k, y) * b_matrix.get_value(x, k);
			}

			new_m.set_value(x, y, value);
		}
	}

	return new_m;
}


Matrix33 operator*(Matrix33& a_matrix, double s)
{
	Matrix33 new_m;

	for(int x = 0; x < 3; x++)
	{
		for(int y = 0; y < 3; y++)
		{
			new_m.set_value(x, y, a_matrix.get_value(x, y) * s);
		}
	}

	return new_m;
}

Matrix33 operator*(double s, Matrix33& b_matrix)
{
	return b_matrix * s;
}

Matrix33 operator/(Matrix33& a_matrix, double s)
{
	Matrix33 new_m;

	for(int x = 0; x < 3; x++)
	{
		for(int y = 0; y < 3; y++)
		{
			new_m.set_value(x, y, a_matrix.get_value(x, y) / s);
		}
	}

	return new_m;
}