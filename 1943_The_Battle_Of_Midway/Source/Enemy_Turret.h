#ifndef __ENEMY_TURRET_H__
#define __ENEMY_TURRET_H__

#include "Enemy.h"
#include "Path.h"

class Enemy_Turret : public Enemy
{
public:

	// Constructor (x y coordinates in the world)
	// Creates animation data and the collider
	Enemy_Turret(int x, int y);

	// The enemy is going to perform a sinusoidal movement
	void Update() override;

private:
	// The enemy animation
	Animation angle[16];
};

#endif // __ENEMY_REDBIRD_H__

