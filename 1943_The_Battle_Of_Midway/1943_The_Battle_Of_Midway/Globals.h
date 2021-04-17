#pragma once
#include "SDL/include/SDL.h"
#include <iostream>
using namespace std;

enum class UpdateResult
{
	UPDATE_CONTINUE = 1,
	UPDATE_STOP,
	UPDATE_ERROR
};

#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0


#define SCREEN_WIDTH 384
#define SCREEN_HEIGHT 224

#define SCREEN_SIZE 3
#define WIN_FULLSCREEN 0
#define WIN_FULLSCREEN_DESKTOP 0
#define WIN_BORDERLESS 0
#define WIN_RESIZABLE 0
#define VSYNC 1