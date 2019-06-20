#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>

#include "Graphics.hpp"
#include "Engine.hpp"

#include "SDL2/SDL.h"
#include "SDL2/SDL_render.h"

using namespace std;

Graphics_System::Graphics_System(Engine * parent_engine) : Engine_System(parent_engine)
{
	this->m_screen_pixels.reserve(this->m_screen_width * this->m_screen_height * 4);
	this->m_default_font.reserve(768);

	if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		SDL_Log("Problem initializing SDL: %s", SDL_GetError());
		exit(1);
	}

	this->m_window = SDL_CreateWindow	(	"Raymarcher test - SDL2",
											SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
											this->m_screen_surface_width, this->m_screen_surface_height,
											SDL_WINDOW_SHOWN
										);

	if(m_window == NULL)
	{
		SDL_Log("Problem creating SDL Window: %s", SDL_GetError());
		exit(1);
	}

	this->m_renderer = SDL_CreateRenderer	( 	this->m_window,
												-1,
												SDL_RENDERER_ACCELERATED
											);

	if(m_renderer == NULL)
	{
		SDL_Log("Problem creating SDL Renderer: %s", SDL_GetError());
		exit(1);
	}

	SDL_RendererInfo info;
	SDL_GetRendererInfo(this->m_renderer, &info);

	cout << "SDL	:	Created Renderer" << endl;
	cout << "SDL	:	Renderer name = " << info.name << endl;
	cout << "SDL	:	Texture formats = " << endl;

	for(int i = 0; i < info.num_texture_formats; i++)
	{
		cout << SDL_GetPixelFormatName(info.texture_formats[i]) << endl;
	}

	this->m_screen_surface = SDL_CreateTexture	(	this->m_renderer,
													SDL_PIXELFORMAT_ARGB8888,
													SDL_TEXTUREACCESS_STREAMING,
													this->m_screen_width, this->m_screen_height
												);

	this->load_default_font("8x8Font.fnt");

	SDL_ShowCursor(0);
}

Graphics_System::~Graphics_System()
{
	cout << "DESTROYING GRAPHICS" << endl;
	SDL_DestroyRenderer(this->m_renderer);
	SDL_DestroyWindow(this->m_window);
	SDL_Quit();
}

void Graphics_System::load_default_font(string font_location)
{
	ifstream file(font_location, ios::in | ios::binary);
	file.read(this->m_default_font.data(), 768);

	file.close();
}

void Graphics_System::update()
{
	if(this->m_show_mouse) this->draw_cursor();
	if(this->m_show_fps) this->draw_text(this->m_screen_width - 40, 0, this->m_parent_engine->m_fps, COLOR_RED);
	if(this->m_show_frame_time) this->draw_text(this->m_screen_width - 40, 8, this->m_parent_engine->m_frame_time * 1000, COLOR_RED);

    SDL_UpdateTexture	(	this->m_screen_surface,
    						NULL,
    						&(this->m_screen_pixels[0]),
    						this->m_screen_width * 4
    					);

    SDL_RenderCopy(this->m_renderer, this->m_screen_surface, NULL, NULL);
    SDL_RenderPresent(this->m_renderer);

	SDL_SetRenderDrawColor(this->m_renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	
	SDL_RenderClear(this->m_renderer);
	this->clear_screen();
}

void Graphics_System::set_pixel(unsigned int x, unsigned int y, Color color)
{
	if(x < this->m_screen_width && y < this->m_screen_height && x >= 0 && y >= 0)
	{
		const unsigned int offset = ( this->m_screen_width * 4 * y) + x * 4;

		this->m_screen_pixels[ offset + 0 ] = color.b;    // b
	    this->m_screen_pixels[ offset + 1 ] = color.g;    // g
	    this->m_screen_pixels[ offset + 2 ] = color.r;    // r
	    this->m_screen_pixels[ offset + 3 ] = color.a;    // a
	}
}

void Graphics_System::clear_screen()
{
	fill(this->m_screen_pixels.begin(), this->m_screen_pixels.begin() + this->m_screen_width * this->m_screen_height * 4, 0);
}

void Graphics_System::clear_screen(Color color)
{
	for(int x = 0; x < this->m_screen_width; x ++)
	{
		for(int y = 0; y < this->m_screen_height; y ++)
		{
			this->set_pixel(x, y, color);
		}
	}
}

void Graphics_System::draw_binary_image(unsigned int x, unsigned int y, 
										unsigned int size_x, unsigned int size_y, 
										std::vector<char> image_location, Color color)
{
	for(int y_c = 0; y_c < size_y; y_c ++)
	{
		for(int x_c = 0; x_c < size_x; x_c ++)
		{
			if(image_location[y_c] & (0x80 >> x_c)) 
			{
				this->set_pixel(x + x_c, y + y_c, color);
			}
		}
	}
}

void Graphics_System::draw_cursor()
{
	const std::vector<char>* current_cursor;

	if(this->m_parent_engine->m_input.m_mouse_state & SDL_BUTTON(SDL_BUTTON_LEFT))
		current_cursor = &CURSOR_CLICK;
	else
		current_cursor = &CURSOR;

	draw_binary_image(	(this->m_parent_engine->m_input.m_mouse_x / this->m_pixel_scale) - 4, 
						(this->m_parent_engine->m_input.m_mouse_y / this->m_pixel_scale) - 4,
						8, 8,
						*current_cursor, COLOR_WHITE);
}

void Graphics_System::draw_char(unsigned int x, unsigned int y, char character, Color color)
{
	unsigned int offset = (unsigned int)((character-32) * 8);

	this->draw_binary_image(x, y, 8, 8, std::vector<char>(this->m_default_font.begin()+offset, this->m_default_font.begin()+offset+8), color);
}

void Graphics_System::draw_text(unsigned int x, unsigned int y, string char_string, Color color)
{
	for(int i = 0; i < char_string.length(); i++)
	{
		this->draw_char(x + 8 * i, y, char_string[i], color);
	}
}

void Graphics_System::draw_text(unsigned int x, unsigned int y, int value, Color color)
{
	char buffer[32];

	sprintf(buffer, "%d", value);

	this->draw_text(x, y, string(buffer), color);
}

void Graphics_System::draw_text(unsigned int x, unsigned int y, double value, Color color)
{
	char buffer[32];

	sprintf(buffer, "%g", value);

	this->draw_text(x, y, string(buffer), color);
}