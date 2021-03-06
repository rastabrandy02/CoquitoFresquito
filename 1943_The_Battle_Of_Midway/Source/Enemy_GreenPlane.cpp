#include "Enemy_GreenPlane.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleParticles.h"

Enemy_GreenPlane::Enemy_GreenPlane(int x, int y) : Enemy(x, y)
{
	flyAnim.PushBack({529,598,28,24});
	flyAnim.PushBack({ 530,623, 28, 24 });
	flyAnim.speed = 0.1f;
	flyAnim.loop = true;


	backwardAnim.PushBack({525, 551, 27, 24});
	backwardAnim.PushBack({526, 527, 27, 24});
	backwardAnim.speed = 0.1f;
	backwardAnim.loop = true;

	
	turnAnim.PushBack({ 701, 698, 29, 24 });
	turnAnim.PushBack({ 701, 698, 29, 24 });
	turnAnim.PushBack({ 673, 697, 29, 24 });
	turnAnim.PushBack({ 673, 697, 29, 24 });
	turnAnim.PushBack({ 644, 697, 29, 24 });
	turnAnim.PushBack({ 617, 696, 29, 24 });
	turnAnim.PushBack({ 590, 700, 29, 24 });
	turnAnim.PushBack({ 590, 700, 29, 24 });
	turnAnim.PushBack({ 562, 696, 28, 23 });
	turnAnim.PushBack({ 562, 696, 28, 23 });
	turnAnim.PushBack({ 617, 696, 29, 24 });
	turnAnim.PushBack({ 644, 697, 29, 24 });
	turnAnim.PushBack({ 727, 653, 28, 23 });
	turnAnim.loop = true;
	turnAnim.speed = 0.08f;


	currentAnim = &flyAnim;

	path.PushBack({ 0.0f, 1.0f }, 180, &flyAnim);
	path.PushBack({ -0.1f, -1.0f }, 60, &turnAnim);
	path.PushBack({ 0.0f, -2.0f }, 200, &backwardAnim);
	path.loop = true;

	collider = App->collisions->AddCollider({0, 0, 24, 24}, Collider::Type::ENEMY, (Module*)App->enemies);
	health = 1;
}

void Enemy_GreenPlane::Update()
{
	path.Update();
	position = spawnPos + path.GetRelativePosition();
	currentAnim = path.GetCurrentAnimation();
	if (attackTimer >= 840)
	{
		App->particles->AddParticle(App->particles->enemyShot, position.x + 5, position.y - 5, Collider::ENEMY_SHOT);
		attackTimer = 0;
	}
	attackTimer++;
	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}
