#ifndef __SCENE_END_H__
#define __SCENE_END_H__

#include "Module.h"
#include "Animation.h"
#include "Path.h"
#include "p2Point.h"
#include "ModuleFonts.h"

struct SDL_Texture;

class SceneEnd : public Module
{
public:
	//Constructor
	SceneEnd(bool startEnabled);

	//Destructor
	~SceneEnd();

	// Called when the module is activated
	// Loads the necessary textures for the map background
	bool Start() override;

	// Called at the middle of the application loop
	// Updates the scene's background animations
	update_status Update() override;

	// Called at the end of the application loop.
	// Performs the render call of all the parts of the scene's background
	update_status PostUpdate() override;

	bool CleanUp() override;

private:
	// The scene sprite sheet loaded into an SDL_Texture
	SDL_Texture* winTexture = nullptr;
	SDL_Texture* loseTexture = nullptr;
	SDL_Texture* planeTex = nullptr;
	int  textFont = -1;
	Animation planeAnim;
	Animation* currentAnim = nullptr;
	Path path;
	iPoint position;
};

#endif

