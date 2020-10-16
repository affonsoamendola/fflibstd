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

template<typename T, size_t dim_x, size_t dim_y>
class Matrix
{
private:
	T* m_contents;
	size_t m_dim_x = 0;
	size_t m_dim_y = 0;
public:
	Matrix(size_t dim_x = 0, size_t dim_y = 0) : m_dim_x{dim_x}, m_dim_y{dim_y}
	{

		this->m_contents = static_cast<T*>(malloc(dim_x * dim_y * sizeof(T)));
	}
	Matrix(Point2 size) : m_dim_x{size[0]}, m_dim_y{size_y}
	{

		this->m_contents = static_cast<T*>(malloc(dim_x * dim_y * sizeof(T)));
	}

	~Matrix()
	{

		free(this->m_contents);
	}

	inline T& get_value const (size_t pos_x, size_t pos_y)
	{

		return this->m_contents[pos_x + pos_y * this->m_dim_x];
	}
	inline T  get_value 	  (size_t pos_x, size_t pos_y)
	{

		return this->m_contents[pos_x + pos_y * this->m_dim_x];
	}

	inline void set_value	  (size_t pos_x, size_t pos_y, T value)
	{

		this->m_contents[pos_x + pos_y * this->m_dim_x] = value;
	}

	inline T& operator[]	  (size_t pos)
	{

		return this->m_contents[pos];
	}
	inline T& operator[]	  (const Point2& pos)
	{

		return this[pos[0] + pos[1] * this->m_dim_x];
	}

	inline T determinant()
	{
		T det = T{0};

		for(int x = 0; x < this->m_dim_x; x++)
		{

		}
	}
};
