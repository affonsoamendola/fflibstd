#include <iostream>

#include "Engine.hpp"

using namespace std;

int main()
{
	Engine engine;

	while(engine.m_is_running)
	{
		engine.update();
	}
	
	return 0;
}


