#ifndef __MODULE_PLAYER_H__
#define __MODULE_PLAYER_H__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"

struct SDL_Texture;
struct Collider;

class ModulePlayer : public Module
{
public:
	// Constructor
	ModulePlayer(bool startEnabled);

	// Destructor
	~ModulePlayer();

	// Called when the module is activated
	// Loads the necessary textures for the player
	bool Start() override;

	// Called at the middle of the application loop
	// Processes new input and handles player movement
	update_status Update() override;

	// Called at the end of the application loop
	// Performs the render call of the player sprite
	update_status PostUpdate() override;

	// Collision callback, called when the player intersects with another collider
	void OnCollision(Collider* c1, Collider* c2) override;

	void AddScore();

	bool CleanUp() override;
	uint life = 9;

	// Position of the player in the map
	iPoint position;

	// The speed in which we move the player (pixels per frame)
	int speed = 2;

	// The player spritesheet loaded into an SDL_Texture
	SDL_Texture* texture = nullptr;
	
	
	// The pointer to the current player animation
	// It will be switched depending on the player's movement direction
	Animation* currentAnimation = nullptr;

	// A set of animations
	Animation idleAnim;
	Animation downAnim;
	Animation introAnim;

	Animation leftAnim;
	Animation rightAnim;

	// The player's collider
	Collider* collider = nullptr;

	// A flag to detect when the player has been destroyed
	bool destroyed = false;
	bool godMode = false;

	// A countdown to when the player gets destroyed. After a while, the game exits
	uint destroyedCountdown = 120;

	// Sound effects indices
	uint laserFx = 0;
	uint deathPlayerFx = 0;
	uint basicShotFx = 0;

	// Font score index
	int score;

	int shotMaxCountDown = 20;
	int shotCountDown = 0;

	int playerDeadParticle = 0;

	bool powerUpThreeWay = false;
	int threeWayTimer = 0;
	int threeWayBullets = 0;

	bool powerUpAuto = false;
	int autoCoolDown = 0;
	int autoTimer = 0;

	bool debugGamepadInfo = false;
	bool playerMove = true;
	bool intro = true;
	bool end = false;
	int endTimer = 0;
};

#endif //!__MODULE_PLAYER_H__