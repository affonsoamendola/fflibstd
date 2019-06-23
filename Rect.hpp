#pragma once

#include "Vector.hpp"

class Rect
{
private:
	Vector2 m_bounds[2]; // index 0 is lower_left corner, 1 is upper right corner
public:
	Rect();
	Rect(Vector2 bounds[2]);
	Rect(std::vector<Vector2> bounds);
	Rect(Vector2 v0, Vector2 v1);

	~Rect(){};

	inline Vector2 lower_left(){return this->m_bounds[0];};
	inline Vector2 upper_right(){return this->m_bounds[1];};

	void move(const Vector2& amount);
	bool is_inside(const Vector2& point);
};