#include "GUI.hpp"

#include "Rect.hpp"
#include "Engine.hpp"

GUI_Object::GUI_Object(	const Point2& position, GUI_System* parent_system)
{
	this->m_is_base = true;

	this->m_parent_system = parent_system;

	this->m_parent_system->m_object_list.push_back(this);

	this->m_global_position = position;
}

GUI_Object::GUI_Object(	GUI_Object* parent_object, const Point2& local_position, GUI_System* parent_system)
{
	this->m_is_base = false;
	
	this->m_parent_object = parent_object;
	this->m_parent_object->m_elements.push_back(this);

	this->m_parent_system = parent_system;

	this->m_local_position = local_position;
	this->m_global_position = this->m_parent_object->m_global_position + local_position;
}

GUI_Object::~GUI_Object()
{
	for(int i = 0; i < this->m_elements.size(); i++)
	{
		delete this->m_elements[i];
	}
}

GUI_Object* GUI_Object::get_base()
{
	GUI_Object* current_object = this;
	
	while(!(current_object->m_is_base))
	{
		current_object = current_object->m_parent_object;
	}

	return current_object;
}

GUI_Window::GUI_Window(const Recti& local_rect, const Point2& position, GUI_System* parent_system)
						: 	GUI_Object(position, parent_system),
							m_rect(local_rect)
{}


void draw_9_seg_square(	const Recti& window_rect, const Point2& seg_size, 
						const Texture* window_texture_holder,
						Graphics_System* graphics_system)
{
	graphics_system->blit_texture(	window_texture_holder,
									Recti(seg_size),
									window_rect.p0());

	graphics_system->blit_texture(	window_texture_holder,
									Recti(seg_size).move(Point2(2*seg_size[0], 0)),
									Point2(window_rect.p1()[0], window_rect.p0()[1]) - Point2(seg_size[0], 0));

	graphics_system->blit_texture(	window_texture_holder,
									Recti(seg_size).move(Point2(0, 2*seg_size[1])),
									Point2(window_rect.p0()[0], window_rect.p1()[1]) - Point2(0, seg_size[1]));

	graphics_system->blit_texture(	window_texture_holder,
									Recti(seg_size).move(Point2(2*seg_size[0], 2*seg_size[1])),
									Point2(window_rect.p1()[0], window_rect.p1()[1]) - Point2(seg_size[0], seg_size[1]));
/*
	for(int w = 1; w < (this->m_rect.width() / 8) - 1; w++)
	{
		graphics_system.blit_texture(	window_texture_holder,
										Recti({8, 0}, {16, 8}),
										this->m_global_position + Point2(w * 8, 0));
		graphics_system.blit_texture(	window_texture_holder,
										Recti({8, 16}, {16, 24}),
										this->m_global_position + Point2(w * 8, this->m_rect.height()-8));
	}

	for(int h = 1; h < (this->m_rect.height() / 8) - 1; h++)
	{
		graphics_system.blit_texture(	window_texture_holder,
										Recti({0, 8}, {8, 16}),
										this->m_global_position + Point2(0, h * 8));
		graphics_system.blit_texture(	window_texture_holder,
										Recti({16, 8}, {24, 16}),
										this->m_global_position + Point2(this->m_rect.width()-8, h * 8));
	}*/
}

void GUI_Window::render()
{
	draw_9_seg_square(Recti(10, 10, 30, 30), Point2(8, 8), &this->m_parent_system->m_gui_texture, &this->m_parent_system->m_parent_engine->m_graphics);
}

GUI_System::GUI_System(	Engine * parent_engine) 
						: 	Engine_System(parent_engine),
							m_gui_texture("gui.png", parent_engine->m_graphics)

{
	new GUI_Window(Recti({32, 32}), Point2({20, 0}), this);
}

GUI_System::~GUI_System()
{
	for(int i = 0; i < this->m_object_list.size(); i++)
	{
		delete this->m_object_list[i];
	}
}

void GUI_System::update()
{}

void GUI_System::render()
{
	for(int i = 0; i < this->m_object_list.size(); i++)
	{
		this->m_object_list[i]->render();
	}
}