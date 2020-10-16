#pragma once

#include <vector>

template<typename T, int vector_dimension>
class Vector
{
public:
	std::vector<T> m_values;

	Vector();
	~Vector();

	Vector(std::vector<T> contents);
	Vector(std::initializer_list<T> contents);

	//Access Operations
	T& operator[](int i);
	T operator[](int i) const;

	//Unary Operations
	Vector<T, vector_dimension> operator-();

	//Operations with other vectors;
	Vector<T, vector_dimension>& operator+=(const Vector<T, vector_dimension>& v);
	Vector<T, vector_dimension>& operator-=(const Vector<T, vector_dimension>& v);

	Vector<T, vector_dimension>& operator*=(const Vector<T, vector_dimension>& v);
	Vector<T, vector_dimension>& operator/=(const Vector<T, vector_dimension>& v);

	//Operations with T types
	Vector<T, vector_dimension>& operator+=(const T& s);
	Vector<T, vector_dimension>& operator-=(const T& s);

	Vector<T, vector_dimension>& operator*=(const T& s);
	Vector<T, vector_dimension>& operator/=(const T& s);

	//Standard Vector operations
	double cross(const Vector<double, 2>& v) const;
	Vector<double, 3> cross(const Vector<double, 3>& v) const;

	double dot(const Vector<T, vector_dimension>& v) const;
	double abs() const;

	double angle(const Vector<T, vector_dimension>& v) const; 

	Vector<T, vector_dimension> unit();
	Vector<T, vector_dimension>& rotate(double ang_rad);

	void print();
};

//Non-member functions
//Operations between two vectors
template<typename T, int vector_dimension>
Vector<T, vector_dimension> operator+(const Vector<T, vector_dimension>& v_a, const Vector<T, vector_dimension>& v_b);

template<typename T, int vector_dimension>
Vector<T, vector_dimension> operator-(const Vector<T, vector_dimension>& v_a, const Vector<T, vector_dimension>& v_b);

template<typename T, int vector_dimension>
Vector<T, vector_dimension> operator*(const Vector<T, vector_dimension>& v_a, const Vector<T, vector_dimension>& v_b);

template<typename T, int vector_dimension>
Vector<T, vector_dimension> operator/(const Vector<T, vector_dimension>& v_a, const Vector<T, vector_dimension>& v_b);


//Operations between a vector and a scalar
template<typename T, int vector_dimension>
Vector<T, vector_dimension> operator+(const Vector<T, vector_dimension>& v_a, const T& b);
template<typename T, int vector_dimension>
Vector<T, vector_dimension> operator+(const T& a, const Vector<T, vector_dimension>& v_b);

template<typename T, int vector_dimension>
Vector<T, vector_dimension> operator-(const Vector<T, vector_dimension>& v_a, const T& b);
template<typename T, int vector_dimension>
Vector<T, vector_dimension> operator-(const T& a, const Vector<T, vector_dimension>& v_b);

template<typename T, int vector_dimension>
Vector<T, vector_dimension> operator*(const Vector<T, vector_dimension>& v_a, const T& b);
template<typename T, int vector_dimension>
Vector<T, vector_dimension> operator*(const T& a, const Vector<T, vector_dimension>& v_b);

template<typename T, int vector_dimension>
Vector<T, vector_dimension> operator/(const Vector<T, vector_dimension>& v_a, const T& b);
template<typename T, int vector_dimension>
Vector<T, vector_dimension> operator/(const T& a, const Vector<T, vector_dimension>& v_b);

typedef Vector<double, 2> Vector2;
typedef Vector<double, 3> Vector3;

#define Vector2(a, b) Vector<double, 2>({a, b})
#define Vector3(a, b, c) Vector<double, 3>({a, b, c})