#include "Enemy_Ship.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleParticles.h"
#include "ModuleEnemies.h"

Enemy_Ship::Enemy_Ship(int x, int y) : Enemy(x, y)
{
	ship.PushBack({ 175, 1223, 56, 296 });
	App->enemies->AddEnemy(ENEMY_TYPE::TURRETSHIP, x + 5, y + 44);
	App->enemies->AddEnemy(ENEMY_TYPE::TURRETSHIP, x + 5, y + 138);
	App->enemies->AddEnemy(ENEMY_TYPE::TURRETSHIP, x + 5, y + 185);
	App->enemies->AddEnemy(ENEMY_TYPE::TURRETSHIP, x + 5, y + 213);
	App->enemies->AddEnemy(ENEMY_TYPE::TURRETSHIP, x + 5, y + 240);

	App->collisions->AddCollider({ 0,0, 56, 296 }, Collider::Type::NONE);

	health = 1;
	currentAnim = &ship;
	powerUp = false;
}

void Enemy_Ship::Update()
{
	Enemy::Update();
}
