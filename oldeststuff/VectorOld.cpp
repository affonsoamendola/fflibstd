/* 	
	DEPRECATED, use the new ones instead.

	Copyright Affonso Amendola 2019

	Fofonso's Vector, version 1.0

	This was part of my standard usage library, I used this in many of my things, it was pretty kewl.

	So, I changed this to use C++ templates instead of defining everything for ints, doubles, 2 and 3 dim
	like it would be needed here, so go use Fofonso's Vector v 2.0 or the one im working on right now.

	Distributed under GPLv3, use it to your hearts content,
	just remember the number one rule:

	Be Excellent to Each Other.
*/

#include <cmath>
#include <limits>
#include <stdio.h>

#include "Vector.hpp"

#if __has_include("Point.hpp") 
#include "Point.hpp"
#endif

Vector2::Vector2()
{}

Vector2::Vector2(	double t_x, double t_y)
					:x(t_x) , y(t_y) 
{}

Vector2::Vector2(	double contents[2])
					:x(contents[0]) , y(contents[1])
{}

//Basic Operators
//Sum
Vector2 Vector2::operator+(const Vector2& v)
{
	Vector2 new_v;

	new_v.x = this->x + v.x;
	new_v.y = this->y + v.y;

	return new_v;
}
void Vector2::operator+=(const Vector2& v)
{
	this->x += v.x;
	this->y += v.y;
}

//Sub / Neg
Vector2 Vector2::operator-()
{
	Vector2 new_v;

	new_v.x = -(this->x);
	new_v.y = -(this->y);

	return new_v;
}
Vector2 Vector2::operator-(const Vector2& v)
{
	Vector2 new_v;

	new_v.x = this->x - v.x;
	new_v.y = this->y - v.y;

	return new_v; 
}
void Vector2::operator-=(const Vector2& v)
{
	this->x -= v.x;
	this->y -= v.y;
}

//Scalar Multiply
Vector2 Vector2::operator*(double s)
{
	Vector2 new_v;

	new_v.x = this->x * s;
	new_v.y = this->y * s;

	return new_v;
}
void Vector2::operator*=(double s)
{
	this->x *= s;
	this->y *= s;
}

//Scalar Divide
Vector2 Vector2::operator/(double s)
{
	Vector2 new_v;

	new_v.x = this->x / s;
	new_v.y = this->y / s;

	return new_v;
}
void Vector2::operator/=(double s)
{
	this->x /= s;
	this->y /= s;
}

double& Vector2::operator[](int i)
{
	switch(i)
	{
		case 0:
			return this->x;
		case 1:
			return this->y;
	}
}

#ifdef _FF_POINT_DEF
//Vector2 -> Point2 Conversion (Explicit)
Vector2::operator Point2()
{
	Point2 new_p;

	new_p.x = static_cast<int>(this->x);
	new_p.y = static_cast<int>(this->y);

	return new_p;
} 
#endif

//Vector2 -> Vector3 Conversion (Explicit)
Vector2::operator Vector3()
{
	Vector3 new_v;

	new_v.x = this->x;
	new_v.y = this->y;
	new_v.z = 0.0f;

	return new_v;
} 

//Cross Product, since the cross product isn't really defined for 2 dimensional vectors,
//(It is supposed to be a Vect3 -> Vect3 operation that gives something orthogonal to both vectors)
//(Not really possible in 2 dimensions, but I digress.)
//We're using the standard extension of the definition of cross product to allow this.
//Which basically returns the length of the Vector3 that *would* exist if they were Vector3's 
double Vector2::cross(const Vector2& v) {return (this->x * v.y) - (this->y * v.x);}

//Dot product
double Vector2::dot(const Vector2& v) {return (this->x * v.x) + (this->y * v.y);}

//Angle in radians between two vectors
double Vector2::angle(Vector2& v)
{
	return acos(this->dot(v) / this->abs() * v.abs());
}

//Abs / Length of the vector, using square root of dot product, Could use the sqr x*x+y*y, but,
//Its really the same thing.
double Vector2::abs()	{return sqrt(this->dot(*this));}

//Returns the Unitary vector version of this vector
Vector2 Vector2::unit()
{
	Vector2 new_v;

	new_v = (*this) / this->abs();

	return new_v;
}

//Rotates this vector around the origin by ang_rad degrees radian.
Vector2 Vector2::rotate(double ang_rad)
{
	Vector2 new_v;

	new_v.x = this->x * cos(ang_rad) - this->y * sin(ang_rad);
	new_v.y = this->x * sin(ang_rad) + this->y * cos(ang_rad);

	return new_v;
}

void Vector2::print()
{
	printf("%f %f\n", this->x, this->y);
}

//Checks if vertex is on the left/on/right side of the infinite line passing through v0 and v1
//Returns 1 if left, 0, if on, and -1 if right
int is_left(const Vector2& v0, const Vector2& v1, const Vector2& vertex)
{
	return (((v1.x - v0.x) * (vertex.y - v0.y)) - ((vertex.x - v0.x) * (v1.y - v0.y)));
}

//Checks if the lines defined by v1 and v2, and, v3 and v4 intersect,
//puts the intersection point in intersect_vector and
//returns 1 in case of intersection, 0 in case of non intersection, and -1 in case of collinear lines
int is_intersection(Vector2& v1, Vector2& v2, Vector2& v3, Vector2& v4, Vector2& intersect_vector)
{
	double denominator = ((v4.x - v3.x) * (v1.y - v2.y) - (v1.x - v2.x) * (v4.y - v3.y));

	if(denominator <= std::numeric_limits<double>::epsilon() && denominator >= -std::numeric_limits<double>::epsilon()) return -1;

	Vector2 len_segment_1;

	double t_a = 	((v3.y - v4.y) * (v1.x - v3.x) + (v4.x - v3.x) * (v1.y - v3.y)) / denominator;

	//Long live Total Biscuit, we really miss you, 
	//wish you could review my shitty game... maybe in another life.
	double t_b = 	((v1.y - v2.y) * (v1.x - v3.x) + (v2.x - v1.x) * (v1.y - v3.y)) / denominator;

	if(t_a >= 0. && t_a <= 1. && t_b >= 0. && t_b <= 1.)
	{
		len_segment_1 = v2 - v1;
		intersect_vector = v1 + (len_segment_1 * t_a);

		return 1;
	}
	else return 0;
}

Vector3::Vector3()
{}

Vector3::Vector3(	double t_x, double t_y, double t_z)
					:x(t_x) , y(t_y), z(t_z)
{}

Vector3::Vector3(	double contents[3])
					:x(contents[0]) , y(contents[1]), z(contents[2])
{}

//Basic Operators
//Sum
Vector3 Vector3::operator+(const Vector3& v)
{
	Vector3 new_v;

	new_v.x = this->x + v.x;
	new_v.y = this->y + v.y;
	new_v.z = this->z + v.z;

	return new_v;
}
void Vector3::operator+=(const Vector3& v)
{
	this->x += v.x;
	this->y += v.y;
	this->z += v.z;
}

//Sub / Neg
Vector3 Vector3::operator-()
{
	Vector3 new_v;

	new_v.x = -(this->x);
	new_v.y = -(this->y);
	new_v.z = -(this->z);

	return new_v;
}
Vector3 Vector3::operator-(const Vector3& v)
{
	Vector3 new_v;

	new_v.x = this->x - v.x;
	new_v.y = this->y - v.y;
	new_v.z = this->z - v.z;

	return new_v; 
}
void Vector3::operator-=(const Vector3& v)
{
	this->x -= v.x;
	this->y -= v.y;
	this->z -= v.z;
}

//Scalar Multiply
Vector3 Vector3::operator*(double s)
{
	Vector3 new_v;

	new_v.x = this->x * s;
	new_v.y = this->y * s;
	new_v.z = this->z * s;

	return new_v;
}
void Vector3::operator*=(double s)
{
	this->x *= s;
	this->y *= s;
	this->z *= s;
}

//Scalar Divide
Vector3 Vector3::operator/(double s)
{
	Vector3 new_v;

	new_v.x = this->x / s;
	new_v.y = this->y / s;
	new_v.z = this->z / s;

	return new_v;
}
void Vector3::operator/=(double s)
{
	this->x /= s;
	this->y /= s;
	this->z /= s;
}

double& Vector3::operator[](int i)
{
	switch(i)
	{
		case 0:
			return this->x;
		case 1:
			return this->y;
		case 2:
			return this->z;
	}
}

//Cross Product
Vector3 Vector3::cross(const Vector3& v)
{
	Vector3 new_v;

	new_v.x = (this->y*v.z) - (this->z*v.y);
	new_v.y = (this->z*v.x) - (this->x*v.z);
	new_v.z = (this->x*v.y) - (this->y*v.x);

	return new_v;
}

//Dot Product
double Vector3::dot(const Vector3& v) {return (this->x * v.x) + (this->y * v.y) + (this->z * v.z);}

//Angle in radians between two vectors
double Vector3::angle(Vector3& v)
{
	return acos(this->dot(v) / this->abs() * v.abs());
}

//Abs / Length of the vector
double Vector3::abs()	{return sqrt(this->dot(*this));}

//Returns the Unitary vector version of this vector
Vector3 Vector3::unit()
{
	Vector3 new_v;

	new_v = (*this) / this->abs();

	return new_v;
}

void Vector3::print()
{
	printf("%f %f %f\n", this->x, this->y, this->z);
}

#ifdef _FF_POINT_DEF

//Vector3 -> Point3 Conversion (Explicit)
Vector3::operator Point3()
{
	Point3 new_p;

	new_p.x = static_cast<int>(this->x);
	new_p.y = static_cast<int>(this->y);
	new_p.z = static_cast<int>(this->z);

	return new_p;
} 

#endif