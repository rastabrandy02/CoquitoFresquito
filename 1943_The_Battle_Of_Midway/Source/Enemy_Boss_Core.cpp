#include "Enemy_Boss_Core.h"
#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"
#include "ModuleRender.h"


Enemy_Boss_Core::Enemy_Boss_Core(int x, int y) : Enemy(x, y)
{
	ship.PushBack({ 492, 306, 32, 30 });
	health = 5;
	currentAnim = &ship;
	collider = App->collisions->AddCollider({ 0, 0, 32, 30 }, Collider::Type::ENEMY, (Module*)App->enemies);
	health = 5;
}

void Enemy_Boss_Core::Update()
{
	if (health <= 0)
	{
		App->render->percentage -= 25;
		App->particles->AddParticle(App->particles->enemyExplosion, position.x, position.y, Collider::Type::NONE);

	}
	
	Enemy::Update();
}
