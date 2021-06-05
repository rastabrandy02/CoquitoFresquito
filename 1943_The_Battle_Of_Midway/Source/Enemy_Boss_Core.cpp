#include "Enemy_Boss_Core.h"
#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"


Enemy_Boss_Core::Enemy_Boss_Core(int x, int y) : Enemy(x, y)
{
	ship.PushBack({ 492, 306, 32, 30 });
	health = 5;
	currentAnim = &ship;
	App->collisions->AddCollider({ 0, 0, 32, 30 }, Collider::Type::ENEMY, (Module*)App->enemies);
}

void Enemy_Boss_Core::Update()
{
	Enemy::Update();
}
