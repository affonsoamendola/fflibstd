/* 	
	Copyright Affonso Amendola 2019

	Fofonso's Vector, version 1.0

	This is part of my standard usage library, I use this in many of my things, it's pretty kewl.

	Distributed under GPLv3, use it to your hearts content,
	just remember the number one rule:

	Be Excellent to Each Other.
*/

#pragma once

#define FF_VECTOR_DEF _FF_VECTOR_DEF

//Forward Decs
class Point2;
class Point3;

class Vector2;
class Vector3;

//Vector2 is a (X,Y) pair of Double types
class Vector2
{
public:
	double x = 0.0f;
	double y = 0.0f;

	Vector2();
	Vector2(double t_x,  double t_y);
	Vector2(double contents[2]);

	Vector2 operator+(const Vector2& v);
	void operator+=(const Vector2& v);
	
	Vector2 operator-();
	Vector2 operator-(const Vector2& v);
	void operator-=(const Vector2& v);

	Vector2 operator*(double s);
	void operator*=(double s);

	Vector2 operator/(double s);
	void operator/=(double s);

	double& operator[](int i);

#ifdef _FF_POINT_DEF
	explicit operator Point2();
#endif
	explicit operator Vector3();

	double cross(const Vector2& v);
	double dot(const Vector2& v);
	double abs();

	Vector2 unit();

	Vector2 rotate(double ang_rad);
};

//Vector3 is a (X,Y,Z) pairing of Double types
class Vector3
{
public:
	double x = 0.0f;
	double y = 0.0f;
	double z = 0.0f;

	Vector3();
	Vector3(double t_x, double t_y, double t_z);
	Vector3(double contents[3]);

	Vector3 operator+(const Vector3& v);
	void operator+=(const Vector3& v);

	Vector3 operator-();
	Vector3 operator-(const Vector3& v);
	void operator-=(const Vector3& v);

	Vector3 operator*(double s);
	void operator*=(double s);

	Vector3 operator/(double s);
	void operator/=(double s);

	double& operator[](int i);

	explicit operator Point3();

	Vector3 cross(const Vector3& v);
	double dot(const Vector3& v);
	double abs();

	Vector3 unit();
};