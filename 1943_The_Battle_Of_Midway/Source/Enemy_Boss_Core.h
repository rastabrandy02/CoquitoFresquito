#ifndef __ENEMY_ENEMYBOSSCORE_H__
#define __ENEMY_ENEMYBOSSCORE_H__

#include "Enemy.h"


class Enemy_Boss_Core : public Enemy
{
public:

	// Constructor (x y coordinates in the world)
	// Creates animation data and the collider
	Enemy_Boss_Core(int x, int y);

	// The enemy is going to perform a sinusoidal movement
	void Update() override;

private:
	// The enemy animation
	Animation ship;
};

#endif 
