#include "Rect.hpp"

Rect::	Rect()
{
	this->m_bounds[0] = {0., 0.};
	this->m_bounds[1] = {0., 0.};
}

Rect::	Rect(Vector2 bounds[2])
{
	this->m_bounds[0] = bounds[0];
	this->m_bounds[1] = bounds[1];
}

Rect::	Rect(std::vector<Vector2> bounds)
{
	this->m_bounds[0] = bounds[0];
	this->m_bounds[1] = bounds[1];
}

Rect::	Rect(Vector2 v0, Vector2 v1)
{
	this->m_bounds[0] = v0;
	this->m_bounds[1] = v1;
}

void Rect::move(const Vector2& v)
{
	this->m_bounds[0] += v;
	this->m_bounds[1] += v;
}

bool Rect::is_inside(const Vector2& point)
{
	if(	point[0] >= this->m_bounds[0][0] && point[0] <= this->m_bounds[1][0] &&
		point[1] >= this->m_bounds[0][1] && point[0] <= this->m_bounds[1][1])
	{
		return true;
	}
	else
	{
		return false;
	}
}