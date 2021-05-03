#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Globals.h"

#define NUM_MODULES 15

class Module;
class ModuleWindow;
class ModuleInput;
class ModuleTextures;
class ModuleAudio;
class ModulePlayer;
class SceneInit;
class SceneIntro;
class SceneLevel1;
class SceneEnd;
class ModuleParticles;
class ModuleCollisions;
class ModuleEnemies;
class ModuleFadeToBlack;
class ModuleFonts;
class ModuleRender;

class Application
{

public:

	//Constructor. Creates all necessary modules for the application
	Application();

	//Destructor. Removes all module objects
	~Application();

	//Initializes all modules
	bool Init();

	//Updates all modules (PreUpdate, Update and PostUpdate)
	update_status Update();

	//Releases all the application data
	bool CleanUp();

public:
	// An array to store all modules
	Module* modules[NUM_MODULES];

	// All the modules stored individually
	ModuleWindow* window = nullptr;
	ModuleInput* input = nullptr;
	ModuleTextures* textures = nullptr;
	ModuleAudio* audio = nullptr;

	ModulePlayer* player = nullptr;
	//ModuleScene* scene = nullptr;

	SceneInit* sceneInit = nullptr;
	SceneIntro* sceneIntro = nullptr;
	SceneLevel1* sceneLevel_1 = nullptr;
	SceneEnd* sceneEnd = nullptr;

	ModuleEnemies* enemies = nullptr;
	ModuleParticles* particles = nullptr;

	ModuleCollisions* collisions = nullptr;
	ModuleFadeToBlack* fade = nullptr;
	ModuleFonts* fonts = nullptr;

	ModuleRender* render = nullptr;
};

// Global var made extern for Application ---
extern Application* App;

#endif // __APPLICATION_H__