#ifndef __SCENE_LEVEL2_H__
#define __SCENE_LEVEL2_H__

#include "Module.h"
#include "Animation.h"

struct SDL_Texture;

class SceneLevel2 : public Module
{
public:
	//Constructor
	SceneLevel2(bool startEnabled);

	//Destructor
	~SceneLevel2();

	// Called when the module is activated
	// Loads the necessary textures for the map background
	bool Start() override;

	// Called at the middle of the application loop
	// Updates the scene's background animations
	update_status Update() override;

	// Called at the end of the application loop.
	// Performs the render call of all the parts of the scene's background
	update_status PostUpdate() override;

	void OnCollision(Collider* c1, Collider* c2) override;
	// Disables the player and the enemies
	bool CleanUp();

public:

	// The scene sprite sheet loaded into an SDL_Texture
	SDL_Texture* bgTexture = nullptr;
	SDL_Texture* healtBar1 = nullptr;
	SDL_Texture* healtBar2 = nullptr;
	SDL_Texture* healtBar3 = nullptr;
	SDL_Texture* healtBar4 = nullptr;
	SDL_Texture* healtBar5 = nullptr;
	SDL_Texture* healtBar6 = nullptr;
	SDL_Texture* healtBar7 = nullptr;
	SDL_Texture* healtBar8 = nullptr;
	SDL_Texture* healtBar9 = nullptr;
	int timer = 0;


};

#endif