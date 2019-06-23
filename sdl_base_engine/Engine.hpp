#pragma once

#include "Graphics.hpp"
#include "Input.hpp"
#include "GUI.hpp"

class Engine
{
private:
	long double m_time = 0.;
public:
	bool m_is_running = true;

	unsigned int frame_start;

	double m_fps = 0.;
	long double m_frame_time_l = 0.;
	double m_frame_time = 0.;
	double m_avg_fps = 0.;
	double m_avg_frame_time = 0.;

	int m_dropped_frames = 0;

	Graphics_System m_graphics;
	Input_System m_input;
	GUI_System m_gui;

	Engine();

	void update();
	long double delta_time();
	long double get_time();
};