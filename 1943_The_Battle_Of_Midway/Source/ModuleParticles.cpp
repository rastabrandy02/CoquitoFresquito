#include "ModuleParticles.h"

#include "Application.h"

#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleCollisions.h"
#include "ModulePlayer.h"

#include "SDL/include/SDL_timer.h"
#include <stdio.h>

ModuleParticles::ModuleParticles(bool startEnabled) : Module(startEnabled)
{
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
		particles[i] = nullptr;
}

ModuleParticles::~ModuleParticles()
{

}

bool ModuleParticles::Start()
{
	LOG("Loading particles");

	


	//basicShotTex = App->textures->Load("Assets/particles_auto.png");
	basicShotTex = App->textures->Load("Assets/particles_powerUps.png");

	basicShot.anim.PushBack({ 722, 95, 6, 24 });
	basicShot.speed.y = -5;
	basicShot.lifetime = 120;

	anglePosShot.anim.PushBack({ 727, 71, 18, 24 });
	anglePosShot.speed.y = -5;
	anglePosShot.speed.x = 5;
	anglePosShot.lifetime = 120;

	angleNegShot.anim.PushBack({ 727, 94, 18, 24 });
	angleNegShot.speed.y = -5;
	angleNegShot.speed.x = -5;
	angleNegShot.lifetime = 120;



	playerDeath.anim.PushBack({ 14, 21, 30, 25 });
	playerDeath.anim.PushBack({ 46, 21, 37, 27 });
	playerDeath.anim.PushBack({ 83, 23, 37, 27 });
	playerDeath.anim.PushBack({ 120, 22, 39, 30 });

	playerDeath.anim.PushBack({ 7, 73, 36, 32 });
	playerDeath.anim.PushBack({ 42, 71, 39, 32 });
	playerDeath.anim.PushBack({ 82, 70, 38, 34 });
	playerDeath.anim.PushBack({ 121, 67, 39, 37 });

	playerDeath.anim.PushBack({ 8, 124, 37, 37 });
	playerDeath.anim.PushBack({ 47, 126, 36, 38 });
	playerDeath.anim.PushBack({ 82, 124, 37, 40 });
	playerDeath.anim.PushBack({ 118, 124, 41, 39 });

	playerDeath.anim.PushBack({ 9, 183, 40, 36 });
	playerDeath.anim.PushBack({ 48, 185, 38, 32 });
	playerDeath.anim.PushBack({ 85, 188, 37, 31 });
	playerDeath.anim.PushBack({ 123, 192, 39, 28 });

	playerDeath.anim.loop = false;
	playerDeath.anim.speed = 0.f;
	
	enemyExplosion.anim.PushBack({ 181, 20, 27, 25 });
	enemyExplosion.anim.PushBack({ 215, 22, 30, 27 });
	enemyExplosion.anim.PushBack({ 248, 21, 33, 28 });
	enemyExplosion.anim.PushBack({ 181, 70, 33, 29 });
	enemyExplosion.anim.PushBack({ 215, 68, 36, 30 });
	enemyExplosion.anim.PushBack({ 250, 67, 34, 32 });
	enemyExplosion.anim.PushBack({ 238, 124, 38, 34 });
	enemyExplosion.anim.speed = 0.1f;
	enemyExplosion.anim.loop = false;

	

	powerUp_Auto.anim.PushBack({ 605, 278, 23, 21 });
	powerUp_Auto.anim.PushBack({ 627, 278, 23, 21 });
	powerUp_Auto.anim.PushBack({ 649, 278, 23, 21 });
	powerUp_Auto.anim.PushBack({ 671, 278, 23, 21 });
	powerUp_Auto.anim.loop = true;
	powerUp_Auto.anim.speed = 0.1f;
	powerUp_Auto.lifetime = 600;

	powerUp_ThreeWay.anim.PushBack({ 613, 198, 20, 17 });
	powerUp_ThreeWay.anim.PushBack({ 632, 198, 20, 17 });
	powerUp_ThreeWay.anim.PushBack({ 651, 198, 20, 17 });
	powerUp_ThreeWay.anim.PushBack({ 670, 198, 20, 17 });
	powerUp_ThreeWay.anim.loop = true;
	powerUp_ThreeWay.anim.speed = 0.1f;
	powerUp_ThreeWay.lifetime = 600;

	powerUp_Pow.anim.PushBack({ 605, 346, 20, 17 });
	powerUp_Pow.anim.PushBack({ 624, 346, 20, 17 });
	powerUp_Pow.anim.PushBack({ 643, 346, 20, 17 });
	powerUp_Pow.anim.PushBack({ 662, 346, 20, 17 });
	powerUp_Pow.anim.PushBack({ 681, 346, 20, 17 });
	powerUp_Pow.anim.PushBack({ 700, 346, 20, 17 });
	powerUp_Pow.anim.PushBack({ 719, 346, 20, 17 });
	powerUp_Pow.anim.loop = true;
	powerUp_Pow.anim.speed = 0.1f; 
	powerUp_Pow.lifetime = 600;
	
	enemyShot.anim.PushBack({ 38, 403, 8, 8 });
	enemyShot.anim.PushBack({ 47, 403, 8, 8 });
	enemyShot.anim.PushBack({ 61, 403, 8, 8 });
	enemyShot.anim.speed = 0.1f;
	enemyShot.anim.loop = true;
	
	biplaneDeath.anim.PushBack({ 316, 67, 61, 57 });
	biplaneDeath.anim.PushBack({ 380, 68, 61, 60 });
	biplaneDeath.anim.PushBack({ 449, 65, 61, 60 });
	biplaneDeath.anim.PushBack({ 516, 66, 61, 63 });
	biplaneDeath.anim.PushBack({ 516, 66, 61, 63 });
	biplaneDeath.anim.PushBack({ 320, 196, 61, 63 });
	biplaneDeath.anim.PushBack({ 384, 196, 61, 63 });
	biplaneDeath.anim.PushBack({ 441, 201, 61, 63 });
	biplaneDeath.anim.PushBack({ 517, 200, 61, 63 });
	biplaneDeath.anim.speed = 0.1f;
	biplaneDeath.anim.loop = false;

	enemyShot.speed.y = 2.0f;
	enemyShot.lifetime = 350;
	return true;
}

update_status ModuleParticles::PreUpdate()
{
	// Remove all particles scheduled for deletion
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if (particles[i] != nullptr && particles[i]->pendingToDelete)
		{
			delete particles[i];
			particles[i] = nullptr;
		}
	}
	
	return update_status::UPDATE_CONTINUE;
}

bool ModuleParticles::CleanUp()
{
	LOG("Unloading particles");

	// Delete all remaining active particles on application exit 
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if(particles[i] != nullptr)
		{
			delete particles[i];
			particles[i] = nullptr;
		}
	}

	return true;
}

void ModuleParticles::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		// Always destroy particles that collide
		if (particles[i] != nullptr && particles[i]->collider == c1)
		{
			delete particles[i];
			particles[i] = nullptr;
			if (c1->type == Collider::Type::PLAYER_SHOT && c2->type == Collider::Type::ENEMY)
			{
				
				App->player->AddScore();
			}
			break;
		}
	}
}

update_status ModuleParticles::Update()
{
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Particle* particle = particles[i];

		if(particle == nullptr)	continue;

		// Call particle Update. If it has reached its lifetime, destroy it
		if(particle->Update() == false)
		{
			delete particle;
			particles[i] = nullptr;
		}
		
	}

	return update_status::UPDATE_CONTINUE;
}

update_status ModuleParticles::PostUpdate()
{
	//Iterating all particle array and drawing any active particles
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Particle* particle = particles[i];

		if (particle != nullptr && particle->isAlive)
		{
			App->render->Blit(basicShotTex, particle->position.x, particle->position.y, &(particle->anim.GetCurrentFrame()));
		}
	}

	return update_status::UPDATE_CONTINUE;
}

void ModuleParticles::AddParticle(const Particle& particle, int x, int y, Collider::Type colliderType, uint delay, bool track)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		//Finding an empty slot for a new particle
		if (particles[i] == nullptr)
		{
			Particle* p = new Particle(particle);

			p->frameCount = -(int)delay;			// We start the frameCount as the negative delay
			p->position.x = x;						// so when frameCount reaches 0 the particle will be activated
			p->position.y = y;

			//Adding the particle's collider
			if (colliderType != Collider::Type::NONE)
				p->collider = App->collisions->AddCollider(p->anim.GetCurrentFrame(), colliderType, this);

			particles[i] = p;
			p->spawnPos.x = x;
			p->spawnPos.y = y;
			
			if (track)
			{
				if ((App->player->position.x - x) < 0) p->speed.x = -1.0f;
				else if ((App->player->position.x - x) > 0)p->speed.x = 1.0f;
				else p->speed.x = 0.0f;

				if (((App->player->position.y^2) - (y^2)) < 0) p->speed.y = -2.0f;
				else if (((App->player->position.y ^ 2) - (y ^ 2)) > 0) p->speed.y = 2.0f;
				else p->speed.y = 0.0f;

			}
			break;
		}
	}
	
}