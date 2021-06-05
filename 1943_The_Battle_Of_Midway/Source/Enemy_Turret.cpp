#include "Enemy_Turret.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleParticles.h"

Enemy_Turret::Enemy_Turret(int x, int y) : Enemy(x, y)
{
	position[0].PushBack({ 22, 158, 30, 35 });
	position[1].PushBack({ 56, 159, 28, 35 });
	position[2].PushBack({ 88, 159, 31, 32 });
	position[3].PushBack({ 122, 162, 31, 27 });
	position[4].PushBack({ 154, 162, 34, 27 });
	position[5].PushBack({ 20, 196, 33, 28 });
	position[6].PushBack({ 56, 196, 31, 28 });
	position[7].PushBack({ 92, 195, 27, 29 });
	position[8].PushBack({ 125, 195, 28, 29 });
	position[9].PushBack({ 156, 194, 26, 30 });
	position[10].PushBack({ 22, 231, 30, 27 });
	position[11].PushBack({ 54, 232, 33, 26 });
	position[12].PushBack({ 88, 232, 33, 26 });
	position[13].PushBack({ 121, 232, 33, 26 });
	position[14].PushBack({ 155, 227, 34, 31 });
	position[15].PushBack({ 24, 260, 30, 32 });

}

void Enemy_Turret::Update()
{

	Enemy::Update();
}
