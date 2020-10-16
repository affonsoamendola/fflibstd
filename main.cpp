#include <iostream>

#include "Matrix4f.hpp"
#include "Util.hpp"

int main(int argc, char const *argv[])
{
	Matrix4f test = m4f_identity();

	std::cout << m4f_perspective(radians(90.f), 1.333, 0.1, 2.0) * Vector3f(1.0, 1.0, 1.5) << std::endl;
	
	/* code */
	return 0;
}