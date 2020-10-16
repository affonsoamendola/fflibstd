#include "Vector.hpp"
#include <cmath>
#include <iostream>

using namespace std;


//Constructors and destructor
template<typename T, int vector_dimension>
Vector<T, vector_dimension>::	Vector()
								:m_values(vector_dimension)
{}
template Vector<double, 2>::Vector();
template Vector<double, 3>::Vector();

template<typename T, int vector_dimension>
Vector<T, vector_dimension>::	~Vector()
{}
template Vector<double, 2>::~Vector();
template Vector<double, 3>::~Vector();


template<typename T, int vector_dimension>
Vector<T, vector_dimension>::	Vector(vector<T> contents)
								:m_values(contents)
{}
template Vector<double, 2>::Vector(vector<double> contents);
template Vector<double, 3>::Vector(vector<double> contents);


template<typename T, int vector_dimension>
Vector<T, vector_dimension>::	Vector(std::initializer_list<T> contents)
								:m_values(contents)
{
	//std::copy(contents.begin(), contents.end(), this->m_values);
}
template Vector<double, 2>::Vector(std::initializer_list<double> contents);
template Vector<double, 3>::Vector(std::initializer_list<double> contents);


//Access Operations
template<typename T, int vector_dimension>
T& Vector<T, vector_dimension>::operator[](int i)
{
	return this->m_values[i];
}
template double& Vector<double, 2>::operator[](int i);
template double& Vector<double, 3>::operator[](int i);


template<typename T, int vector_dimension>
T Vector<T, vector_dimension>::operator[](int i) const
{
	return this->m_values[i];
}
template double Vector<double, 2>::operator[](int i) const;
template double Vector<double, 3>::operator[](int i) const;


//Unary Operations
template<typename T, int vector_dimension>
Vector<T, vector_dimension> Vector<T, vector_dimension>::operator-()
{
	Vector<T, vector_dimension> temp;

	for(int i = 0; i < this->m_values.size(); i++)
	{
		temp[i] = -temp[i];
	}

	return temp;
}
template Vector<double, 2> Vector<double, 2>::operator-();
template Vector<double, 3> Vector<double, 3>::operator-();


//Operations with other vectors;
template<typename T, int vector_dimension>
Vector<T, vector_dimension>& Vector<T, vector_dimension>::operator+=(const Vector<T, vector_dimension>& v)
{
	for(int i = 0; i < this->m_values.size(); i++)
	{
		this->m_values[i] += v[i];
	}
}
template Vector<double, 2>& Vector<double, 2>::operator+=(const Vector<double, 2>& v);
template Vector<double, 3>& Vector<double, 3>::operator+=(const Vector<double, 3>& v);


template<typename T, int vector_dimension>
Vector<T, vector_dimension>& Vector<T, vector_dimension>::operator-=(const Vector<T, vector_dimension>& v)
{
	for(int i = 0; i < this->m_values.size(); i++)
	{
		this->m_values[i] -= v[i];
	}
}
template Vector<double, 2>& Vector<double, 2>::operator-=(const Vector<double, 2>& v);
template Vector<double, 3>& Vector<double, 3>::operator-=(const Vector<double, 3>& v);


template<typename T, int vector_dimension>
Vector<T, vector_dimension>& Vector<T, vector_dimension>::operator*=(const Vector<T, vector_dimension>& v)
{
	for(int i = 0; i < this->m_values.size(); i++)
	{
		this->m_values[i] *= v[i];
	}
}
template Vector<double, 2>& Vector<double, 2>::operator*=(const Vector<double, 2>& v);
template Vector<double, 3>& Vector<double, 3>::operator*=(const Vector<double, 3>& v);


template<typename T, int vector_dimension>
Vector<T, vector_dimension>& Vector<T, vector_dimension>::operator/=(const Vector<T, vector_dimension>& v)
{
	for(int i = 0; i < this->m_values.size(); i++)
	{
		this->m_values[i] /= v[i];
	}
}
template Vector<double, 2>& Vector<double, 2>::operator/=(const Vector<double, 2>& v);
template Vector<double, 3>& Vector<double, 3>::operator/=(const Vector<double, 3>& v);


//Operations with T types;
template<typename T, int vector_dimension>
Vector<T, vector_dimension>& Vector<T, vector_dimension>::operator+=(const T& s)
{
	for(int i = 0; i < this->m_values.size(); i++)
	{
		this->m_values[i] += s;
	}
}
template Vector<double, 2>& Vector<double, 2>::operator+=(const double& s);
template Vector<double, 3>& Vector<double, 3>::operator+=(const double& s);


template<typename T, int vector_dimension>
Vector<T, vector_dimension>& Vector<T, vector_dimension>::operator-=(const T& s)
{
	for(int i = 0; i < this->m_values.size(); i++)
	{
		this->m_values[i] -= s;
	}
}
template Vector<double, 2>& Vector<double, 2>::operator-=(const double& s);
template Vector<double, 3>& Vector<double, 3>::operator-=(const double& s);


template<typename T, int vector_dimension>
Vector<T, vector_dimension>& Vector<T, vector_dimension>::operator*=(const T& s)
{
	for(int i = 0; i < this->m_values.size(); i++)
	{
		this->m_values[i] *= s;
	}
}
template Vector<double, 2>& Vector<double, 2>::operator*=(const double& s);
template Vector<double, 3>& Vector<double, 3>::operator*=(const double& s);


template<typename T, int vector_dimension>
Vector<T, vector_dimension>& Vector<T, vector_dimension>::operator/=(const T& s)
{
	for(int i = 0; i < this->m_values.size(); i++)
	{
		this->m_values[i] /= s;
	}
}
template Vector<double, 2>& Vector<double, 2>::operator/=(const double& s);
template Vector<double, 3>& Vector<double, 3>::operator/=(const double& s);


//Standard Vector operations
template<>
double Vector<double, 2>::cross(const Vector<double, 2>& v) const
{
	return (this->m_values[0] * v[1]) - (this->m_values[1] * v[0]);
}

template<>
Vector<double, 3> Vector<double, 3>::cross(const Vector<double, 3>& v) const
{
	Vector<double, 3> new_v;

	new_v[0] = (this->m_values[1]*v[2]) - (this->m_values[2]*v[1]);
	new_v[1] = (this->m_values[2]*v[0]) - (this->m_values[0]*v[2]);
	new_v[2] = (this->m_values[0]*v[1]) - (this->m_values[1]*v[0]);

	return new_v;
}


template<typename T, int vector_dimension>
double Vector<T, vector_dimension>::dot(const Vector<T, vector_dimension>& v) const
{
	double sum = 0.0f;

	for(int i = 0; i < this->m_values.size(); i++)
	{
		sum += this->m_values[i]*v[i];
	}

	return sum;
}
template double Vector<double, 2>::dot(const Vector<double, 2>& v) const;
template double Vector<double, 3>::dot(const Vector<double, 3>& v) const;


template<typename T, int vector_dimension>
double Vector<T, vector_dimension>::abs() const
{
	double sum = 0.0f;

	for(int i = 0; i < this->m_values.size(); i++)
	{
		sum += this->m_values[i] * this->m_values[i];
	}

	return sqrt(sum);
}
template double Vector<double, 2>::abs() const;
template double Vector<double, 3>::abs() const;


template<typename T, int vector_dimension>
double Vector<T, vector_dimension>::angle(const Vector<T, vector_dimension>& v) const
{
	return acos(this->dot(v) / (this->abs() * v.abs()));
}
template double Vector<double, 2>::angle(const Vector<double, 2>& v) const;
template double Vector<double, 3>::angle(const Vector<double, 3>& v) const;


template<typename T, int vector_dimension>
Vector<T, vector_dimension> Vector<T, vector_dimension>::unit()
{
	Vector<T, vector_dimension> new_v;

	new_v /= this->abs();

	return new_v;
}
template Vector<double, 2> Vector<double, 2>::unit();
template Vector<double, 3> Vector<double, 3>::unit();


/*
template<typename T, int vector_dimension>
Vector<T, vector_dimension>& Vector<T, vector_dimension>::rotate(double ang_rad)
{

}
*/

template<>
void Vector<double, 2>::print()
{

	printf("%f %f\n", this[0], this[1]);
}

template<>
void Vector<double, 3>::print()
{

	printf("%f %f %f\n", this[0], this[1], this[2]);
}


template<typename T, int vector_dimension>
Vector<T, vector_dimension> operator+(	const Vector<T, vector_dimension>& v_a, 
										const Vector<T, vector_dimension>& v_b)
{
	Vector<T, vector_dimension> new_v;

	for(int i = 0; i < vector_dimension; i++)
	{
		new_v[i] = v_a[i] + v_b[i];
	}

	return new_v;
}
template Vector<double, 2> operator+(	const Vector<double, 2>& v_a, 
										const Vector<double, 2>& v_b);
template Vector<double, 3> operator+(	const Vector<double, 3>& v_a, 
										const Vector<double, 3>& v_b);


template<typename T, int vector_dimension>
Vector<T, vector_dimension> operator-(	const Vector<T, vector_dimension>& v_a, 
										const Vector<T, vector_dimension>& v_b)
{
	Vector<T, vector_dimension> new_v;

	for(int i = 0; i < vector_dimension; i++)
	{
		new_v[i] = v_a[i] - v_b[i];
	}

	return new_v;
}
template Vector<double, 2> operator-(	const Vector<double, 2>& v_a, 
										const Vector<double, 2>& v_b);
template Vector<double, 3> operator-(	const Vector<double, 3>& v_a, 
										const Vector<double, 3>& v_b);


template<typename T, int vector_dimension>
Vector<T, vector_dimension> operator*(	const Vector<T, vector_dimension>& v_a, 
										const Vector<T, vector_dimension>& v_b)
{
	Vector<T, vector_dimension> new_v;

	for(int i = 0; i < vector_dimension; i++)
	{
		new_v[i] = v_a[i] * v_b[i];
	}

	return new_v;
}
template Vector<double, 2> operator*(	const Vector<double, 2>& v_a, 
										const Vector<double, 2>& v_b);
template Vector<double, 3> operator*(	const Vector<double, 3>& v_a, 
										const Vector<double, 3>& v_b);


template<typename T, int vector_dimension>
Vector<T, vector_dimension> operator/(	const Vector<T, vector_dimension>& v_a, 
										const Vector<T, vector_dimension>& v_b)
{
	Vector<T, vector_dimension> new_v;

	for(int i = 0; i < vector_dimension; i++)
	{
		new_v[i] = v_a[i] / v_b[i];
	}

	return new_v;
}
template Vector<double, 2> operator/(	const Vector<double, 2>& v_a, 
										const Vector<double, 2>& v_b);
template Vector<double, 3> operator/(	const Vector<double, 3>& v_a, 
										const Vector<double, 3>& v_b);





template<typename T, int vector_dimension>
Vector<T, vector_dimension> operator+(	const Vector<T, vector_dimension>& v_a, 
										const T& b)
{
	Vector<T, vector_dimension> new_v;

	for(int i = 0; i < vector_dimension; i++)
	{
		new_v[i] = v_a[i] +b;
	}

	return new_v;
}
template Vector<double, 2> operator+(	const Vector<double, 2>& v_a, 
										const double& b);
template Vector<double, 3> operator+(	const Vector<double, 3>& v_a, 
										const double& b);


template<typename T, int vector_dimension>
Vector<T, vector_dimension> operator+(	const T& a, 
										const Vector<T, vector_dimension>& v_b)
{
	return v_b + a;
}
template Vector<double, 2> operator+(	const double& a, 
										const Vector<double, 2>& v_b);
template Vector<double, 3> operator+(	const double& a, 
										const Vector<double, 3>& v_b);


template<typename T, int vector_dimension>
Vector<T, vector_dimension> operator-(	const Vector<T, vector_dimension>& v_a, 
										const T& b)
{
	Vector<T, vector_dimension> new_v;

	for(int i = 0; i < vector_dimension; i++)
	{
		new_v[i] = v_a[i] - b;
	}

	return new_v;
}
template Vector<double, 2> operator-(	const Vector<double, 2>& v_a, 
										const double& b);
template Vector<double, 3> operator-(	const Vector<double, 3>& v_a, 
										const double& b);


template<typename T, int vector_dimension>
Vector<T, vector_dimension> operator-(	const T& a, 
										const Vector<T, vector_dimension>& v_b)
{
	Vector<T, vector_dimension> new_v;

	for(int i = 0; i < vector_dimension; i++)
	{
		new_v[i] = a - v_b[i];
	}

	return new_v;
}
template Vector<double, 2> operator-(	const double& a, 
										const Vector<double, 2>& v_b);
template Vector<double, 3> operator-(	const double& a, 
										const Vector<double, 3>& v_b);


template<typename T, int vector_dimension>
Vector<T, vector_dimension> operator*(	const Vector<T, vector_dimension>& v_a, 
										const T& b)
{
	Vector<T, vector_dimension> new_v;

	for(int i = 0; i < vector_dimension; i++)
	{
		new_v[i] = v_a[i] * b;
	}

	return new_v;
}
template Vector<double, 2> operator*(	const Vector<double, 2>& v_a, 
										const double& b);
template Vector<double, 3> operator*(	const Vector<double, 3>& v_a, 
										const double& b);


template<typename T, int vector_dimension>
Vector<T, vector_dimension> operator*(	const T& a, 
										const Vector<T, vector_dimension>& v_b)
{
	return v_b * a;
}
template Vector<double, 2> operator*(	const double& a, 
										const Vector<double, 2>& v_b);
template Vector<double, 3> operator*(	const double& a, 
										const Vector<double, 3>& v_b);



template<typename T, int vector_dimension>
Vector<T, vector_dimension> operator/(	const Vector<T, vector_dimension>& v_a, 
										const T& b)
{
	Vector<T, vector_dimension> new_v;

	for(int i = 0; i < vector_dimension; i++)
	{
		new_v[i] = v_a[i] / b;
	}

	return new_v;
}
template Vector<double, 2> operator/(	const Vector<double, 2>& v_a, 
										const double& b);
template Vector<double, 3> operator/(	const Vector<double, 3>& v_a, 
										const double& b);


template<typename T, int vector_dimension>
Vector<T, vector_dimension> operator/(	const T& a, 
										const Vector<T, vector_dimension>& v_b)
{
	Vector<T, vector_dimension> new_v;

	for(int i = 0; i < vector_dimension; i++)
	{
		new_v[i] = a / v_b[i];
	}

	return new_v;
}
template Vector<double, 2> operator/(	const double& a, 
										const Vector<double, 2>& v_b);
template Vector<double, 3> operator/(	const double& a, 
										const Vector<double, 3>& v_b);