#include "Enemy_RedPlane.h"

#include "Application.h"
#include "ModuleCollisions.h"

Enemy_RedPlane::Enemy_RedPlane(int x, int y) : Enemy(x, y)
{
	flyAnim.PushBack({5,6,24,24});
	flyAnim.PushBack({38, 6, 24, 24});
	flyAnim.PushBack({71, 6, 24, 24});
	flyAnim.PushBack({104, 6, 24, 24});
	flyAnim.PushBack({137, 6, 24, 24});
	flyAnim.PushBack({170, 6, 24, 24});
	flyAnim.PushBack({203, 6, 24, 24});
	flyAnim.PushBack({236, 6, 24, 24});
	flyAnim.speed = 0.2f;

	currentAnim = &flyAnim;

	path.PushBack({ 0.0f, 1.0f }, 180, &flyAnim);
	path.PushBack({ 0.0f, -1.0f }, 300, &flyAnim);
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
