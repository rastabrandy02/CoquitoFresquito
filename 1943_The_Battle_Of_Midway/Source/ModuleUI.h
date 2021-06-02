#ifndef __MODULE_UI_H__
#define __MODULE_UI_H__

#include "Module.h"
#include "ModuleFonts.h"



struct SDL_Texture;



class ModuleUI : public Module
{
public:

	// Constructor
	ModuleUI(bool isEnabled);

	// Destructor
	~ModuleUI();

	bool Start() override;

	update_status PostUpdate() override;

	bool CleanUp() override;

	void DebugDrawGamepadInfo();

	float fps = 0;
	uint score = 000;
	bool way;
	bool autopw;

private:
	int autoCounter = 0;
	int counter = 0;
	int scoreFont = -1;
	int textFont = 0;
	int testFont = 1;
	char scoreText[150] = { 0 };
	char fpsText[16] = { 0 };
	char text[150] = {"\0"};
	char powerupText[150] = { "\0" };
	int timersAuto;
	int timersWay;
	SDL_Texture* healtBar1 = nullptr;
	SDL_Texture* healtBar2 = nullptr;
	SDL_Texture* healtBar3 = nullptr;
	SDL_Texture* healtBar4 = nullptr;
	SDL_Texture* healtBar5 = nullptr;
	SDL_Texture* healtBar6 = nullptr;
	SDL_Texture* healtBar7 = nullptr;
	SDL_Texture* healtBar8 = nullptr;
	SDL_Texture* healtBar9 = nullptr;
};


#endif 

