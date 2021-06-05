#include "Enemy_Turret_Boss.h"
#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"
#include "ModuleRender.h"
#include <math.h>

#define PI 3.14159265


Enemy_Turret_Boss::Enemy_Turret_Boss(int x, int y) : Enemy(x, y)
{
	angle[0].PushBack({ 445, 151, 23, 26 });
	angle[1].PushBack({ 478, 151, 24, 26 });
	angle[2].PushBack({ 510, 153, 29, 23 });
	angle[3].PushBack({ 544, 155, 29, 21 });
	angle[4].PushBack({ 443, 192, 28, 18 });
	angle[5].PushBack({ 477, 190, 27, 20 });
	angle[6].PushBack({ 510, 189, 26, 22 });
	angle[7].PushBack({ 446, 189, 21, 24 });
	angle[8].PushBack({ 447, 226, 18, 21 });
	angle[9].PushBack({ 479, 224, 21, 23 });
	angle[10].PushBack({ 510, 224, 26, 22 });
	angle[11].PushBack({ 541, 226, 28, 20 });
	angle[12].PushBack({ 439, 262, 29, 18 });
	angle[13].PushBack({ 473, 262, 29, 20 });
	angle[14].PushBack({ 508, 258, 29, 26 });
	angle[15].PushBack({ 546, 257, 24, 23 });

	currentAnim = &angle[8];

	collider = App->collisions->AddCollider({ 0,0, 30, 32 }, Collider::Type::ENEMY, (Module*)App->enemies);
	health = 3;
	degrees = 0;

}

void Enemy_Turret_Boss::Update()
{
	iPoint vect = position - App->player->position;
	
	if (vect.x != 0)
	{
		degrees = (atan(vect.y / vect.x) * 180) / PI;
		if (vect.x < 0)
			degrees += 180;
		else if (vect.x > 0 && vect.y < 0)
			degrees += 360;
	}
	else
		degrees = 270;

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
	if (health <= 0)
	{
		App->particles->AddParticle(App->particles->enemyExplosion, position.x, position.y, Collider::Type::NONE);
		App->render->percentage -= 9;
	}
	Enemy::Update();
}


