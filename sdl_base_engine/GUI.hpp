#pragma once

#include "Engine_System.hpp"

#include <vector>

class GUI_Object
{
private:
	static unsigned int m_object_count;
public:
	const unsigned int m_id;

	GUI_System* parent_system; 

	GUI_Object();
	~GUI_Object();

	unsigned int get_object_count() {return m_object_count};
}

class GUI_Interactive_Area : GUI_Object
{

}

class GUI_System : public Engine_System
{
private:
	std::vector<GUI_Object*> m_object_list;

public:
	GUI_System(Engine * parent_engine);
	~GUI_System();
}