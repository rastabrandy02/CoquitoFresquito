#ifndef __ENEMY_SHIP_H__
#define __ENEMY_SHIP_H__

#include "Enemy.h"
#include "Path.h"

class Enemy_Ship : public Enemy
{
public:

	// Constructor (x y coordinates in the world)
	// Creates animation data and the collider
	Enemy_Ship(int x, int y);

	// The enemy is going to perform a sinusoidal movement
	void Update() override;

private:
	// The enemy animation
	Animation ship;
};

#endif 

