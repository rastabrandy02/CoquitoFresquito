#include"Application.h"
#include "ModuleWindow.h"

#include "SDL/include/SDL.h"



ModuleWindow:: ModuleWindow() : Module()
{

}

ModuleWindow :: ~ModuleWindow()
{

}

bool ModuleWindow::Init()
{
	cout << "Init window and surface" << endl;
	bool ret = true;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		cout << "ERROR---> SDL Video Initialization" << endl;
	}
	else
	{
		Uint32 flags = SDL_WINDOW_SHOWN;
		if (WIN_FULLSCREEN == true) flags |= SDL_WINDOW_FULLSCREEN;
		
		if (WIN_BORDERLESS == true) flags |= SDL_WINDOW_BORDERLESS;
		
		if (WIN_RESIZABLE == true) flags |= SDL_WINDOW_RESIZABLE;
		
		if (WIN_FULLSCREEN_DESKTOP == true) flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
		
		window = SDL_CreateWindow("1943: The Battle of Midway", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH * SCREEN_SIZE, SCREEN_HEIGHT * SCREEN_SIZE, flags);

		if (window = nullptr)
		{
			cout << "ERROR---> Window creation" << endl;
			ret = false;
		}
		else
		{
			screenSurface = SDL_GetWindowSurface(window);
		}
	}
	return ret;
}

bool ModuleWindow::CleanUp()
{
	if (window != nullptr)
	{
		SDL_DestroyWindow(window);
	}
	cout << "Window destroyed" << endl;

	SDL_Quit();

	return true;

}
