#pragma once

#include <math.h>
#include <stdlib.h>
#include <iostream>

/*  
	Copyright Affonso Amendola 2019

	Fofonso's Standard Library

	This is part of my standard library of functions and stuff.
	
	This class is almost an EXACT copy of the vec3 class from Peter Shirleys Ray Tracing in a Weekend minibook.

	Distributed under GPLv3, use it to your hearts content,
	just remember the number one rule:

	Be Excellent to Each Other.
*/

class Vector3 
{
public:
	float v[3];

	Vector3() {}
	Vector3(float v0, float v1, float v2) {v[0] = v0; v[1] = v1; v[2] = v2;}

	inline float x() const {return v[0];}
	inline float y() const {return v[1];}
	inline float z() const {return v[2];}

	inline float r() const {return v[0];}
	inline float g() const {return v[1];}
	inline float b() const {return v[2];}

	inline const Vector3& operator+() const {return *this; }
	inline Vector3 operator-() const {return Vector3(-v[0], -v[1], -v[2]);}

	inline float operator[](int i) const {return v[i];}
	inline float& operator[](int i) {return v[i];}

	inline Vector3& operator+=(const Vector3& other);
	inline Vector3& operator-=(const Vector3& other);
	inline Vector3& operator*=(const Vector3& other);
	inline Vector3& operator/=(const Vector3& other);
	inline Vector3& operator*=(const float scale);
	inline Vector3& operator/=(const float scale);

	inline float length() const 
	{
		return sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);
	}

	inline float length_squared() const
	{
		return v[0]*v[0] + v[1]*v[1] + v[2]*v[2];
	}

	inline Vector3 unit();
};

inline std::istream& operator>>(std::istream& is, Vector3& t)
{
	is >> t.v[0] >> t.v[1] >> t.v[2];
	return is;
}

inline std::ostream& operator<<(std::ostream& os, const Vector3& t)
{
	os << t.v[0] << " " << t.v[1] << " " << t.v[2];
	return os;
}

inline Vector3 Vector3::unit()
{
	float k = 1.0 / sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);
	return Vector3(v[0]*k, v[1]*k, v[2]*k);
}

inline Vector3 operator+(const Vector3& v0, const Vector3& v1)
{
	return Vector3(v0.v[0] + v1.v[0], v0.v[1] + v1.v[1], v0.v[2] + v1.v[2]);
}

inline Vector3 operator-(const Vector3& v0, const Vector3& v1)
{
	return Vector3(v0.v[0] - v1.v[0], v0.v[1] - v1.v[1], v0.v[2] - v1.v[2]);
}

inline Vector3 operator*(const Vector3& v0, const Vector3& v1)
{
	return Vector3(v0.v[0] * v1.v[0], v0.v[1] * v1.v[1], v0.v[2] * v1.v[2]);
}

inline Vector3 operator/(const Vector3& v0, const Vector3& v1)
{
	return Vector3(v0.v[0] / v1.v[0], v0.v[1] / v1.v[1], v0.v[2] / v1.v[2]);
}

inline Vector3 operator*(float scale, const Vector3& t)
{
	return Vector3(scale * t.v[0], scale * t.v[1], scale * t.v[2]);
}

inline Vector3 operator*(const Vector3& t, float scale)
{
	return Vector3(scale * t.v[0], scale * t.v[1], scale * t.v[2]);
}

inline Vector3 operator/(const Vector3& t, float scale)
{
	return Vector3(t.v[0] / scale, t.v[1] / scale, t.v[2] / scale);
}

inline float dot_v3(const Vector3& v0, const Vector3& v1)
{
	return v0.v[0]*v1.v[0] + v0.v[1]*v1.v[1] + v0.v[2]*v1.v[2];   
}

inline Vector3 cross_v3(const Vector3& v0, const Vector3& v1)
{
	return Vector3	(	(v0.v[1] * v1.v[2] - v0.v[2] * v1.v[1]),
					   -(v0.v[0] * v1.v[2] - v0.v[2] * v1.v[0]),
					    (v0.v[0] * v1.v[1] - v0.v[1] * v1.v[0])
					);
}

inline Vector3& Vector3::operator+=(const Vector3& t)
{
	v[0]
}