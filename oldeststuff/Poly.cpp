#include <limits>
#include <iostream>
#include <typeinfo>

#include "Poly.hpp"

using namespace std;

template <typename T> 
int sign(T val) 
{
    return (T(0) < val) - (val < T(0));
}

template<class T>
Polygon<T>::Polygon()
{}

template Polygon<Vector2>::Polygon();
template Polygon<Vector3>::Polygon();

template<class T>
Polygon<T>::~Polygon()
{}

template Polygon<Vector2>::~Polygon();
template Polygon<Vector3>::~Polygon();

template<class T>
Polygon<T>::Polygon(const std::vector<T>& contents)
{
	this->set(contents);
}

template Polygon<Vector2>::Polygon(const std::vector<Vector2>& contents);
template Polygon<Vector3>::Polygon(const std::vector<Vector3>& contents);

template<class T>
void Polygon<T>::add_vertex(const T& vertex)
{
	this->m_vertexes.push_back(vertex);
	this->m_is_convex = this->is_convex();
}

template void Polygon<Vector2>::add_vertex(const Vector2& vertex);
template void Polygon<Vector3>::add_vertex(const Vector3& vertex);

template<class T>	
void Polygon<T>::add_vertex(const std::vector<T> vertexes)
{
	this->m_vertexes.insert(this->m_vertexes.end(), vertexes.begin(), vertexes.end());	
	this->m_is_convex = this->is_convex();
}

template void Polygon<Vector2>::add_vertex(const std::vector<Vector2> vertexes);
template void Polygon<Vector3>::add_vertex(const std::vector<Vector3> vertexes);

template<class T>
void Polygon<T>::insert_vertex(int position, const T& vertex)
{
	this->m_vertexes.insert(this->m_vertexes.begin() + position, vertex);
	this->m_is_convex = this->is_convex();
}

template void Polygon<Vector2>::insert_vertex(int position, const Vector2& vertex);
template void Polygon<Vector3>::insert_vertex(int position, const Vector3& vertex);

template<class T>
void Polygon<T>::remove_vertex()
{
	this->m_vertexes.erase(this->m_vertexes.end());
	this->m_is_convex = this->is_convex();
}

template void Polygon<Vector2>::remove_vertex();
template void Polygon<Vector3>::remove_vertex();

template<class T>
void Polygon<T>::remove_vertex(int position)
{
	if(position >= 0) 	this->m_vertexes.erase(this->m_vertexes.begin() + position);
	else 				this->m_vertexes.erase(this->m_vertexes.end() + position);

	this->m_is_convex = this->is_convex();
}

template void Polygon<Vector2>::remove_vertex(int position);
template void Polygon<Vector3>::remove_vertex(int position);

template<class T>
void Polygon<T>::set(const std::vector<T>& vertexes)
{
	this->m_vertexes.clear();
	copy(vertexes.begin(), vertexes.end(), this->m_vertexes.begin());
	this->m_is_convex = this->is_convex();
}

template void Polygon<Vector2>::set(const std::vector<Vector2>& vertexes);
template void Polygon<Vector3>::set(const std::vector<Vector3>& vertexes);

const double two_pi = 3.14159265359 * 2;

//Checks if the polygon is convex, concave or complex,
//returns 1 if convex, 0 if concave, -1 if complex
template<>
int Polygon<Vector2>::is_convex()
{
	double total_angle = 0.0f;
	double current_angle = 0.0f;

	Vector2 v0 = this->m_vertexes[0] - this->m_vertexes.back();
	Vector2 v1 = this->m_vertexes[1] - this->m_vertexes[0];

	for(int i = 2; i < this->m_vertexes.size(); i ++)
	{
		current_angle = v0.angle(v1);

		if(total_angle != 0.0f)
		{
			if(sign(current_angle) != sign(total_angle))
				return 0;
		}

		total_angle += current_angle;

		v0 = this->m_vertexes[i-1] - this->m_vertexes[i-2];
		v1 = this->m_vertexes[i]   - this->m_vertexes[i-1];
	}

	double number_of_turns = current_angle / two_pi;

	if(number_of_turns < 0.) number_of_turns *= -1.;

	if(number_of_turns <= 1. + std::numeric_limits<double>::epsilon() && number_of_turns >= 1. - std::numeric_limits<double>::epsilon())
	{
		return 1;
	}
	else
	{
		return -1;
	}
}

template<>
int Polygon<Vector3>::is_convex() {}

template int Polygon<Vector2>::is_convex();
template int Polygon<Vector3>::is_convex();

/*
template<class T>
bool Polygon<T>::is_inside(const Vector2& vertex)
{
}
*/
template<class T>
void Polygon<T>::print()
{
	for(int i = 0; i < this->m_vertexes.size(); i++)
	{
		this->m_vertexes[i].print();
	}
}

template void Polygon<Vector2>::print();
template void Polygon<Vector3>::print();

//bool is_inside(const Vector3& vertex);
