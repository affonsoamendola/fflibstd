#include <iostream>

#include "Engine.hpp"
#include "SDL2/SDL.h"

#define AVERAGE_FRAME_T_SAMPLING 60
#define DROPPED_FRAME_THRESHOLD 15

using namespace std;

Engine::Engine()
	:	m_graphics(this),
		m_input(this),
		m_gui(this)
{
}

vector<double> average_frame_time = vector<double>(AVERAGE_FRAME_T_SAMPLING, 0.);
int current_average = 0;

void Engine::update()
{
	this->frame_start = SDL_GetPerformanceCounter();

	this->m_graphics.update();
	this->m_input.update();
	this->m_gui.update();

	this->m_graphics.render();

	this->m_frame_time_l = this->delta_time();
    this->m_frame_time = static_cast<double>(this->m_frame_time_l);
    this->m_fps = 1. / this->m_frame_time;

    if(current_average >= AVERAGE_FRAME_T_SAMPLING) current_average = 0;

   	average_frame_time[current_average] = this->m_frame_time;

   	double sum = 0.;

   	for(int i = 0; i < AVERAGE_FRAME_T_SAMPLING; i ++)
   	{	
   		sum += average_frame_time[i];
   	}

   	this->m_avg_frame_time = sum / static_cast<double>(AVERAGE_FRAME_T_SAMPLING);
   	this->m_avg_fps = 1. / this->m_avg_frame_time;

   	current_average++;

   	if(this->m_fps <= this->m_avg_fps*DROPPED_FRAME_THRESHOLD*0.01)
   	{
   		this->m_dropped_frames ++;
   	}

   	this->m_time += this->m_frame_time_l;
}

long double Engine::delta_time()
{
	const unsigned int frame_end = SDL_GetPerformanceCounter();
    const static unsigned int freq = SDL_GetPerformanceFrequency();
    
	return (frame_end - this->frame_start) / static_cast<long double>(freq);
}

long double Engine::get_time()
{
	return this->m_time;
}