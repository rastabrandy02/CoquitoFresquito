#include "Enemy.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleRender.h"
#include "ModuleEnemies.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"
#include <stdlib.h>

Enemy::Enemy(int x, int y) : position(x, y)
{
	spawnPos = position;
}

Enemy::~Enemy()
{
	if (collider != nullptr)
		collider->pendingToDelete = true;
}

const Collider* Enemy::GetCollider() const
{
	return collider;
}

void Enemy::Update()
{
	if (currentAnim != nullptr)
		currentAnim->Update();

	if (collider != nullptr)
		collider->SetPos(position.x, position.y);
	
	
}

void Enemy::Draw()
{
	if (currentAnim != nullptr)
		App->render->Blit(texture, position.x, position.y, &(currentAnim->GetCurrentFrame()));
}

void Enemy::OnCollision(Collider* collider)
{
	if(!invincible) health--;
	if (health <= 0)
	{
		App->particles->AddParticle(App->particles->enemyExplosion, position.x, position.y);
		int random = rand() % 100;
		
		if (powerUp)
		{
			if (random <= 3)
			{
				App->particles->AddParticle(App->particles->powerUp_Auto, position.x, position.y, Collider::Type::PU_AUTO);
			}
			else if (random >= 50 && random <= 55)
			{
				App->particles->AddParticle(App->particles->powerUp_ThreeWay, position.x, position.y, Collider::Type::PU_THREEWAY);
			}
			else if (random >= 96)
			{
				App->particles->AddParticle(App->particles->powerUp_Pow, position.x, position.y, Collider::Type::PU_POW);
			}
		}
		App->audio->PlayFx(destroyedFx);

		SetToDelete();
	}
	
}

void Enemy::SetToDelete()
{
	pendingToDelete = true;
	if (collider != nullptr)
		collider->pendingToDelete = true;
}