#include "Enemy_RedPlane.h"

#include "Application.h"
#include "ModuleCollisions.h"

Enemy_RedPlane::Enemy_RedPlane(int x, int y) : Enemy(x, y)
{
	flyAnim.PushBack({529,598,28,24});
	flyAnim.PushBack({ 530,623, 28, 24 });
	flyAnim.speed = 0.1f;
	flyAnim.loop = true;

	backwardAnim.PushBack({525, 551, 27, 24});
	backwardAnim.PushBack({526, 527, 27, 24});


	currentAnim = &flyAnim;

	path.PushBack({ 0.0f, 1.0f }, 180, &flyAnim);
	path.PushBack({ 0.0f, -2.0f }, 300, &backwardAnim);
	path.loop = true;

	collider = App->collisions->AddCollider({0, 0, 24, 24}, Collider::Type::ENEMY, (Module*)App->enemies);
}

void Enemy_RedPlane::Update()
{
	path.Update();
	position = spawnPos + path.GetRelativePosition();
	currentAnim = path.GetCurrentAnimation();

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}
