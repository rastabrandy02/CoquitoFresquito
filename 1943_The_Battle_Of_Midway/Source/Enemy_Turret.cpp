#include "Enemy_Turret.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"
#include <math.h>
#include <stdio.h>
#define PI 3.14159265

Enemy_Turret::Enemy_Turret(int x, int y) : Enemy(x, y)
{
	angle[0].PushBack({ 22, 158, 30, 35 });
	angle[1].PushBack({ 56, 159, 28, 35 });
	angle[2].PushBack({ 88, 159, 31, 32 });
	angle[3].PushBack({ 122, 162, 31, 27 });
	angle[4].PushBack({ 154, 162, 34, 27 });
	angle[5].PushBack({ 20, 196, 33, 28 });
	angle[6].PushBack({ 56, 196, 31, 28 });
	angle[7].PushBack({ 92, 195, 27, 29 });
	angle[8].PushBack({ 125, 195, 28, 29 });
	angle[9].PushBack({ 156, 194, 26, 30 });
	angle[10].PushBack({ 22, 231, 30, 27 });
	angle[11].PushBack({ 54, 232, 33, 26 });
	angle[12].PushBack({ 88, 232, 33, 26 });
	angle[13].PushBack({ 121, 232, 33, 26 });
	angle[14].PushBack({ 155, 227, 34, 31 });
	angle[15].PushBack({ 24, 260, 30, 32 });

	currentAnim = &angle[8];

	collider = App->collisions->AddCollider({ 0,0, 30, 32 }, Collider::Type::ENEMY, (Module*)App->enemies);
	health = 3;

}

void Enemy_Turret::Update()
{
	iPoint vect = position - App->player->position;
	float degrees = (atan(vect.y / vect.x) * 180)/PI;
	if (vect.x < 0)
		degrees += 180;
	else if (vect.x > 0 && vect.y < 0)
		degrees += 360;
	printf("%f\n", degrees);

	if (0 <= degrees && degrees< 22.5f)
		currentAnim = &angle[12];
	else if (22.5f <= degrees && degrees < 2 * 22.5f)
		currentAnim = &angle[13];
	else if (2 * 22.5f <= degrees && degrees < 3 * 22.5f)
		currentAnim = &angle[14];
	else if (3 * 22.5f <= degrees && degrees < 4 * 22.5f)
		currentAnim = &angle[15];
	else if (4 * 22.5f <= degrees && degrees < 5 * 22.5f)
		currentAnim = &angle[0];
	else if (5 * 22.5f <= degrees && degrees < 6 * 22.5f)
		currentAnim = &angle[1];
	else if (6 * 22.5f <= degrees && degrees < 7 * 22.5f)
		currentAnim = &angle[2];
	else if ((7 * 22.5f) <= degrees && degrees < (8 * 22.5f))
		currentAnim = &angle[2];
	else if (8 * 22.5f <= degrees && degrees < 9 * 22.5f)
		currentAnim = &angle[3];
	else if (9 * 22.5f <= degrees && degrees < 10 * 22.5f)
		currentAnim = &angle[4];
	else if (10 * 22.5f <= degrees && degrees < 11 * 22.5f)
		currentAnim = &angle[5];
	else if (11 * 22.5f <= degrees && degrees < 12* 22.5f)
		currentAnim = &angle[6];
	else if (12 * 22.5f <= degrees && degrees < 13 * 22.5f)
		currentAnim = &angle[7];
	else if (13 * 22.5f <= degrees && degrees < 14 * 22.5f)
		currentAnim = &angle[8];
	else if (14 * 22.5f <= degrees && degrees < 15 * 22.5f)
		currentAnim = &angle[9];
	else if (15 * 22.5f <= degrees)
		currentAnim = &angle[10];

	position = spawnPos;

	Enemy::Update();
}
