#include "Enemy_Boss.h"
#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleParticles.h"
#include "ModuleEnemies.h"

Enemy_Boss::Enemy_Boss(int x, int y) : Enemy(x, y)
{
	ship.PushBack({ 50, 1218, 76, 318 });
	App->enemies->AddEnemy(ENEMY_TYPE::BOSSCORE, x + 20, y + 104);
	App->enemies->AddEnemy(ENEMY_TYPE::TURRETBOSS, x + 25, y + 45);
	App->enemies->AddEnemy(ENEMY_TYPE::TURRETBOSS, x + 25, y + 60);
	App->enemies->AddEnemy(ENEMY_TYPE::TURRETBOSS, x + 25, y + 75);
	App->enemies->AddEnemy(ENEMY_TYPE::TURRETBOSS, x + 25, y + 215);
	App->enemies->AddEnemy(ENEMY_TYPE::TURRETBOSS, x + 25, y + 240);
	App->enemies->AddEnemy(ENEMY_TYPE::TURRETBOSS, x + 5, y + 122);
	App->enemies->AddEnemy(ENEMY_TYPE::TURRETBOSS, x + 5, y + 163);
	App->enemies->AddEnemy(ENEMY_TYPE::TURRETBOSS, x + 50, y + 122);
	App->enemies->AddEnemy(ENEMY_TYPE::TURRETBOSS, x + 50, y + 163);
	

	collider = App->collisions->AddCollider({ 0,0, 56, 296 }, Collider::Type::NONE);

	invincible = true;
	currentAnim = &ship;
	powerUp = false;
}

void Enemy_Boss::Update()
{
	Enemy::Update();
}
