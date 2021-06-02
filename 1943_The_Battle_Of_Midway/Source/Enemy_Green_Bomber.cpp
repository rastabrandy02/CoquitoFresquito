#include "Enemy_Green_Bomber.h"

#include "Application.h"
#include "ModuleCollisions.h"

Enemy_Green_Bomber:: Enemy_Green_Bomber(int x, int y) : Enemy(x, y)
{
	


	//Idle
	flyAnim.PushBack({ 815,975, 110, 90 });
	flyAnim.speed = 0.1f;
	flyAnim.loop = false;
	//Goes down
	/*flyAnim.PushBack({ 930, 975, 110, 90 });
	flyAnim.PushBack({ 830, 1070, 100, 90 });
	flyAnim.PushBack({ 940, 1075, 100, 80 });
	flyAnim.PushBack({ 830, 1190, 90, 70 });
	flyAnim.PushBack({ 950, 1190, 85, 65 });*/

	downAnim.PushBack({ 930, 975, 110, 90 });
	downAnim.PushBack({ 830, 1070, 100, 90 });
	downAnim.PushBack({ 940, 1075, 100, 80 });
	downAnim.PushBack({ 830, 1190, 90, 70 });
	downAnim.PushBack({ 950, 1190, 85, 65 });

	downAnim.speed = 0.1f;
	downAnim.loop = false;

	stayAnim.PushBack({ 950, 1190, 85, 65 });
	stayAnim.speed = 0.1f;
	stayAnim.loop = false;
	//Goes up
	/*flyAnim.PushBack({ 830, 1190, 90, 70 });
	flyAnim.PushBack({ 940, 1075, 100, 80 });
	flyAnim.PushBack({ 820,885,100,90 });
	flyAnim.PushBack({ 930,885, 100, 90 });*/

	upAnim.PushBack({ 950, 1190, 85, 65 });
	upAnim.PushBack({ 830, 1190, 90, 70 });
	upAnim.PushBack({ 940, 1075, 100, 80 });
	upAnim.PushBack({ 820, 885, 100, 80 });
	upAnim.PushBack({ 930, 885, 105, 85 });

	//upAnim.PushBack({ 815,975, 110, 90 });

	upAnim.speed = 0.1f;
	upAnim.loop = false;
	//Idle
	//flyAnim.PushBack({ 815,975, 110, 90 });
	

	

	currentAnim = &flyAnim;

	/*path.PushBack({ 0.0f, 1.0f }, 180, &flyAnim);
	path.PushBack({ 0.0f, 1.0f }, 60, &downAnim);
	path.PushBack({ 0.0f, 1.0f }, 60, &upAnim);
	path.loop = true;*/

	collider = App->collisions->AddCollider({ 0, 0, 110, 90 }, Collider::Type::ENEMY, (Module*)App->enemies);
	health = 10;
}

void Enemy_Green_Bomber::Update()
{

	position.y -= 1;
	
	if (timer < fase[1])
	{
		currentAnim = &flyAnim;
	}
	if (timer >= fase[1] && timer < fase[2])
	{
		
		currentAnim = &downAnim;
		invincible = true;
		collider->type = Collider::Type::NONE;
	}
	if (timer >= fase[2] && timer < fase[3])
	{
		downAnim.Reset();
		currentAnim = &stayAnim;
	}
	if (timer >= fase[3] && timer < fase[4])
	{
		stayAnim.Reset();
		currentAnim = &upAnim;
		invincible = false;
		collider->type = Collider:: Type::ENEMY;
	}
	if (timer >= fase[4])
	{
		upAnim.Reset();
		timer = fase[0];
		currentAnim = &flyAnim;
	}
	timer++;
	/*path.Update();
	position = spawnPos + path.GetRelativePosition();
	currentAnim = path.GetCurrentAnimation();*/


	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}