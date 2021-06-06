#include "Enemy_Ship.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleParticles.h"
#include "ModuleEnemies.h"

Enemy_Ship::Enemy_Ship(int x, int y) : Enemy(x, y)
{
	ship.PushBack({ 164, 1295, 38, 180 });
	App->enemies->AddEnemy(ENEMY_TYPE::TURRETSHIP, x + 3, y + 15);
	App->enemies->AddEnemy(ENEMY_TYPE::TURRETSHIP, x + 3, y + 70);
	App->enemies->AddEnemy(ENEMY_TYPE::TURRETSHIP, x + 3, y + 105);
	App->enemies->AddEnemy(ENEMY_TYPE::TURRETSHIP, x + 3, y + 120);
	App->enemies->AddEnemy(ENEMY_TYPE::TURRETSHIP, x + 3, y + 135);

	collider = App->collisions->AddCollider({ 0,0, 38, 180 }, Collider::Type::NONE);

	health = 1;
	currentAnim = &ship;
	powerUp = false;
}

void Enemy_Ship::Update()
{
	Enemy::Update();
}
