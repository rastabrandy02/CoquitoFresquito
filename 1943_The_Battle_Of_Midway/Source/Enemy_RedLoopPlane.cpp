#include "Enemy_RedLoopPlane.h"

#include "Application.h"
#include "ModuleCollisions.h"

Enemy_RedLoopPlane::Enemy_RedLoopPlane(int x, int y): Enemy(x, y)
{
	flyAnim.PushBack({ 1073,1172,27,26 });
	flyAnim.PushBack({ 1080,1283, 29, 25 });
	flyAnim.speed = 0.2f;
	flyAnim.loop = true;

	backwardAnim.PushBack({ 525, 551, 27, 24 });
	backwardAnim.PushBack({ 526, 527, 27, 24 });
	backwardAnim.speed = 0.1f;
	backwardAnim.loop = true;

	turnAnim.PushBack({ 1273, 1243, 27, 26 });
	turnAnim.PushBack({ 1243, 1243, 30, 25 });
	turnAnim.PushBack({ 1215, 1244, 29, 23 });
	turnAnim.PushBack({ 1188, 1243, 27, 24 });
	turnAnim.PushBack({ 1159, 1244, 29, 20 });
	turnAnim.PushBack({ 1131, 1243, 29, 24 });
	turnAnim.PushBack({ 1105, 1242, 27, 27 });
	turnAnim.PushBack({ 1275, 1282, 32, 25 });
	turnAnim.PushBack({ 1249, 1284, 28, 22 });
	turnAnim.PushBack({ 1221, 1284, 28, 21 });
	turnAnim.PushBack({ 1192, 1284, 28, 21 });
	turnAnim.PushBack({ 1165, 1283, 28, 24 });
	turnAnim.PushBack({ 1136, 1283, 29, 24 });
	turnAnim.PushBack({ 1109, 1282, 25, 25 });
	turnAnim.loop = false;
	turnAnim.speed = 0.1f;


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
	}
	if (timer >360)
	{
		waveRatio = 0.0f;
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