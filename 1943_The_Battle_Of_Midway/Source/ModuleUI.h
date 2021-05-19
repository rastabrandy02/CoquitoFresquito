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

	void DebugDrawGamepadInfo();

	float fps = 0;
private:
	 
	uint score = 000;
	int scoreFont = -1;
	int textFont = 0;
	char scoreText[10] = { 0 };
	char fpsText[16] = { 0 };
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

