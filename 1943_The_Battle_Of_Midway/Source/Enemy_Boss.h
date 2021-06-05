#ifndef __ENEMY_ENEMYBOSS_H__
#define __ENEMY_ENEMYBOSS_H__

#include "Enemy.h"


class Enemy_Boss : public Enemy
{
public:

	// Constructor (x y coordinates in the world)
	// Creates animation data and the collider
	Enemy_Boss(int x, int y);

	// The enemy is going to perform a sinusoidal movement
	void Update() override;

private:
	// The enemy animation
	Animation ship;
};

#endif 


