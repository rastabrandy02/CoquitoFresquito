#include "Enemy_RedLoopPlane.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleParticles.h"

Enemy_RedLoopPlane::Enemy_RedLoopPlane(int x, int y): Enemy(x, y)
{
	flyAnim.PushBack({ 1081, 1283, 28, 21 });
	flyAnim.PushBack({ 1081, 1283, 28, 21 });
	flyAnim.speed = 0.2f;
	flyAnim.loop = true;

	/*backwardAnim.PushBack({ 525, 551, 27, 24 });
	backwardAnim.PushBack({ 526, 527, 27, 24 });
	backwardAnim.speed = 0.1f;
	backwardAnim.loop = true;*/

	turnAnim.PushBack({ 1161, 1244, 28, 21 });
	turnAnim.PushBack({ 1132, 1245, 28, 21 });
	turnAnim.PushBack({ 1103, 1245, 28, 24 });
	turnAnim.PushBack({ 1075, 1242, 28, 24 });
	turnAnim.PushBack({ 1276, 1281, 28, 24 });
	turnAnim.PushBack({ 1250, 1282, 28, 24 });
	turnAnim.PushBack({ 1103, 1245, 28, 24 });
	turnAnim.PushBack({ 1221, 1283, 28, 24 });
	turnAnim.PushBack({ 1221, 1283, 28, 24 });
	turnAnim.PushBack({ 1194, 1283, 28, 24 });
	turnAnim.PushBack({ 1165, 1283, 28, 24 });
	turnAnim.PushBack({ 1194, 1283, 28, 24 });
	turnAnim.PushBack({ 1137, 1283, 28, 24 });
	turnAnim.PushBack({ 1109, 1283, 28, 24 });
	turnAnim.PushBack({ 1083, 1283, 28, 24 });
	turnAnim.PushBack({ 1103, 1173, 28, 24 });
	turnAnim.PushBack({ 1128, 1173, 28, 24 });
	turnAnim.PushBack({ 1158, 1172, 28, 24 });
	turnAnim.loop = false;
	turnAnim.speed = 0.8f;


	currentAnim = &flyAnim;

	/*path.PushBack({ 0.0f, 1.0f }, 120, &flyAnim);
	path.PushBack({waveHeight * sinf(waveRatio), waveHeight * sinf(waveRatio) }, 60, &turnAnim);
	path.PushBack({ waveHeight * sinf(waveRatio), -1.0f }, 60, &flyAnim);
	path.PushBack({-(waveHeight * sinf(waveRatio)), -(waveHeight * sinf(waveRatio)) }, 60, &turnAnim);
	path.loop = true;*/

	collider = App->collisions->AddCollider({ 0, 0, 24, 24 }, Collider::Type::ENEMY, (Module*)App->enemies);
	health = 1;
}

void Enemy_RedLoopPlane::Update()
{
	
	position.y += 1;
	if (timer <=180)
	{
		position.x = spawnPos.x;

	}
	if (timer >= 180 && timer <= 240)
	{
		waveRatio += waveRatioSpeed;
		position.x = spawnPos.x + (waveHeight * sinf(waveRatio));
		position.y -= 5;
		currentAnim = &turnAnim;
	}
	if (timer >= 240 && timer <= 360)
	{
		//position.x = spawnPos.x + (waveHeight * sinf(waveRatio));
		position.x = spawnPos.x;
		currentAnim = &flyAnim;
		if (!hasAttacked)
		{
			App->particles->AddParticle(App->particles->enemyShot, position.x + 5, position.y - 5, Collider::ENEMY_SHOT);
			hasAttacked = true;
		}
	}
	if (timer >360)
	{
		waveRatio = 0.0f;
		hasAttacked = false;
		timer = 0;
		
	}
	timer++;
	
	/*path.Update();
	position = spawnPos + path.GetRelativePosition();
	currentAnim = path.GetCurrentAnimation();*/


	// Call to the base class. It must be called at the end
	// It will update the collider depending on  the position
	Enemy::Update();
}