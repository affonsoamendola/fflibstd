#pragma once
/*  
	Copyright Affonso Amendola 2019
	Fofonso's Standard Library

	This is part of my standard library of functions and stuff.

	Distributed under GPLv3, use it to your hearts content,
	just remember the number one rule:

	Be Excellent to Each Other.
*/
#include "Vector.hpp"

//MATRIX CLASS DECLARATION (and some definitions ;P)
template<typename T>
class Matrix
{
private:
	T* m_contents;
	size_t m_dim_x = 0;
	size_t m_dim_y = 0;

public:
	Matrix(size_t dim_x = 0, size_t dim_y = 0) : m_dim_x{dim_x}, m_dim_y{dim_y}
	{

		m_contents = static_cast<T*>(malloc(m_dim_x * m_dim_y * sizeof(T)));
	}
	Matrix(Point2 size) : m_dim_x{size[0]}, m_dim_y{size[1]}
	{

		m_contents = static_cast<T*>(malloc(m_dim_x * m_dim_y * sizeof(T)));
	}

	~Matrix()
	{

		free(m_contents);
	}

	inline T& get_value (size_t pos_x, size_t pos_y) const
	{

		return m_contents[pos_x + pos_y * m_dim_x];
	}
	inline T  get_value (size_t pos_x, size_t pos_y)
	{

		return m_contents[pos_x + pos_y * m_dim_x];
	}

	inline void set_value (size_t pos_x, size_t pos_y, T value)
	{

		m_contents[pos_x + pos_y * m_dim_x] = value;
	}

	inline T& operator[] (size_t pos)
	{

		return m_contents[pos];
	}
	inline T& operator[] (const Point2& pos)
	{

		return *this[pos[0] + pos[1] * m_dim_x];
	}

	T determinant() const;
	void print() const;

	inline Point2 shape() const { return Point2(m_dim_x, m_dim_y); }
	inline size_t len() const { return m_dim_x * m_dim_y; }
	inline size_t size() const { return m_dim_x * m_dim_y * sizeof(T); }

};

//MATRIX CLASS MEMBER FUNCTIONS DEFINITIONS

template<typename T>
void Matrix<T>::print() const
{
	for(int x = 0; x < m_dim_x; x++)
	{
		for(int y = 0; y < m_dim_y; y++)
		{
			std::cout << get_value(x, y) << "\t";
		}

		std::cout << std::endl;
	}
}

template<typename T>
T Matrix<T>::determinant() const
{
	T det = T{0};

	if(m_dim_x != m_dim_y) return NULL;

	if(m_dim_x == 2) return get_value(0, 0) * get_value(1, 1) - (get_value(1, 0) * get_value(0, 1));

	for(int x = 0; x < m_dim_x; x++)
	{
		T diag_p = T{1};
		T diag_m = T{1};

		for(int y = 0; y < m_dim_y; y++)
		{
			diag_p *= get_value( (x + y >= m_dim_x) ? x + y - m_dim_x : x + y ,
								 y);

			diag_m *= get_value( (x - y < 0) ? x - y + m_dim_x : x - y ,
								 y);
		}

		det += diag_p - diag_m;
	}

	return det;
}

//--------------------------

//NON-MEMBER RELATED FUNCTIONS

template<typename T>
inline Matrix<T> operator-(const Matrix<T>& a)
{
	Matrix<T> new_matrix(a.shape());

	for(int i = 0; i < a.len(); i++)
	{
		new_matrix[i] = -a[i];
	}

	return new_matrix;
}

template<typename T>
inline Matrix<T> operator+(const Matrix<T>& a, const Matrix<T>& b)
{
	static_assert(a.m_dim_x == b.m_dim_x && a.m_dim_y == b.m_dim_y, "FFMATRIX: Trying to sum two matrixes of different sizes.");

	Matrix<T> new_matrix(a.shape());

	for(int i = 0; i < a.len(); i++)
	{
		new_matrix[i] = a[i] + b[i];
	}

	return new_matrix;
}

template<typename T>
inline Matrix<T> operator-(const Matrix<T>& a, const Matrix<T>& b)
{
	static_assert(a.m_dim_x == b.m_dim_x && a.m_dim_y == b.m_dim_y, "FFMATRIX: Trying to sum two matrixes of different sizes.");

	Matrix<T> new_matrix(a.shape());

	for(int i = 0; i < a.len(); i++)
	{
		new_matrix[i] = a[i] - b[i];
	}

	return new_matrix;
}

template<typename T>
inline Matrix<T> operator*(const Matrix<T>& a, const Matrix<T>& b)
{
	static_assert(a.m_dim_x == b.m_dim_y, "FFMATRIX: Trying to multiply two matrixes of imcompatible sizes.");

	Matrix<T> new_matrix(b.m_dim_x, a.m_dim_y);

	T current_value{0};

	for(int x = 0; x < b.m_dim_x; x++)
	{
		for(int y = 0; y < a.m_dim_y; y++)
		{
			current_value = T{0};

			for(int c = 0; c < a.m_dim_x; c++)
			{
				current_value += a.get_value(c, y) * b.get_value(x, c);
			}

			new_matrix.set_value(x, y, current_value);
		}	
	}

	return new_matrix;
}

//----------------------------