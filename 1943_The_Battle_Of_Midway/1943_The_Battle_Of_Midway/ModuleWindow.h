#pragma once

#include "Module.h"
#include "SDL/include/SDL.h"

struct SDL_Window;
struct SDL_Surface;

class ModuleWindow : public Module
{
public:
	ModuleWindow();

	~ModuleWindow();

	bool Init() override;

	bool CleanUp() override;

	SDL_Window* window = nullptr;

	SDL_Surface* screenSurface = nullptr;
};