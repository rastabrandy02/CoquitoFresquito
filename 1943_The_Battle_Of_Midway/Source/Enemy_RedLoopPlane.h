#ifndef __ENEMY_REDLOOPLANE_H__
#define __ENEMY_REDLOOPLANE_H__
#pragma once
#include "Enemy.h"
#include "Path.h"
class Enemy_RedLoopPlane : public Enemy
{
public:

	// Constructor (x y coordinates in the world)
	// Creates animation data and the collider
	Enemy_RedLoopPlane(int x, int y);

	// The enemy is going to perform a sinusoidal movement
	void Update() override;

private:
	// The position (as ratio) in the wave at a specific moment
	float Radius = 10.0f;
	float Angle = 0.0f;

	// The enemy animation
	Animation flyAnim;
	Animation turnAnim;
	Animation backwardAnim;

	Path path;
};

#endif // __ENEMY_REDLOOPLANE_H__