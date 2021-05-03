#include "ModuleParticles.h"

#include "Application.h"

#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleCollisions.h"

#include "SDL/include/SDL_timer.h"

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

	


	basicShotTex = App->textures->Load("Assets/Art/SuperAce/shot_beam.png");

	basicShot.anim.PushBack({ 158, 184, 6, 24 });
	basicShot.speed.y = -5;
	basicShot.lifetime = 180;

	playerDeathTex = App->textures->Load("Assets/Art/VFX/explosion.png");

	playerDeath.anim.PushBack({ 120, 85, 30, 25 });
	playerDeath.anim.PushBack({ 150, 90, 40, 25 });
	playerDeath.anim.PushBack({ 190, 90, 35, 25 });
	playerDeath.anim.PushBack({ 225, 90, 25, 25 });

	playerDeath.anim.PushBack({ 115, 140, 35, 30 });
	playerDeath.anim.PushBack({ 155, 138, 35, 30 });
	playerDeath.anim.PushBack({ 190, 135, 30, 30 });
	playerDeath.anim.PushBack({ 230, 135, 35, 35 });

	playerDeath.anim.PushBack({ 120, 190, 30, 40 });
	playerDeath.anim.PushBack({ 155, 190, 30, 40 });
	playerDeath.anim.PushBack({ 190, 190, 33, 35 });
	playerDeath.anim.PushBack({ 225, 190, 33, 36 });

	playerDeath.anim.PushBack({ 115, 250, 37, 35 });
	playerDeath.anim.PushBack({ 153, 250, 38, 30 });
	playerDeath.anim.PushBack({ 190, 255, 40, 35 });
	playerDeath.anim.PushBack({ 230, 260, 35, 25 });

	playerDeath.anim.loop = false;
	playerDeath.anim.speed = 0.3f;
	
	// Explosion particle
	enemyExplosionTex = App->textures->Load("Assets/Art/VFX/explosion_enemies.png");
	enemyExplosion.anim.PushBack({ 148, 102, 22, 19 });
	enemyExplosion.anim.PushBack({ 181, 103, 26, 20 });
	enemyExplosion.anim.PushBack({ 213, 101, 25, 24 });
	enemyExplosion.anim.PushBack({ 147, 149, 29, 28 });
	enemyExplosion.anim.PushBack({ 169, 207, 33, 30 });
	enemyExplosion.anim.PushBack({ 203, 206, 32, 28 });
	enemyExplosion.anim.speed = 0.1f;
	enemyExplosion.anim.loop = false;

	

	

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

void ModuleParticles::AddParticle(const Particle& particle, int x, int y, Collider::Type colliderType, uint delay)
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
			break;
		}
	}
}