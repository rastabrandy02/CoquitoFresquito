#include "ModuleEnemies.h"

#include "Application.h"

#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"

#include "Enemy.h"
#include "Enemy_GreenPlane.h"
#include "Enemy_RedLoopPlane.h"
#include "Enemy_Green_Bomber.h"
#include "Enemy_Turret.h"
#include "Enemy_Ship.h"
#include "Enemy_Boss.h"
#include "Enemy_Boss_Core.h"
#include "Enemy_Turret_Boss.h"


#define SPAWN_MARGIN 500


ModuleEnemies::ModuleEnemies(bool startEnabled) : Module(startEnabled)
{
	for(uint i = 0; i < MAX_ENEMIES; ++i)
		enemies[i] = nullptr;
}

ModuleEnemies::~ModuleEnemies()
{

}

bool ModuleEnemies::Start()
{
	texture = App->textures->Load("Assets/enemy_sprite.png");
	enemyDestroyedFx = App->audio->LoadFx("Assets/FX/enemy_death.wav");

	return true;
}

update_status ModuleEnemies::PreUpdate()
{
	// Remove all enemies scheduled for deletion
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr && enemies[i]->pendingToDelete)
		{
			delete enemies[i];
			enemies[i] = nullptr;
		}
	}

	return update_status::UPDATE_CONTINUE;
}

update_status ModuleEnemies::Update()
{
	HandleEnemiesSpawn();

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if(enemies[i] != nullptr)
			enemies[i]->Update();
	}

	HandleEnemiesDespawn();

	return update_status::UPDATE_CONTINUE;
}

update_status ModuleEnemies::PostUpdate()
{
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
			enemies[i]->Draw();
	}

	return update_status::UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleEnemies::CleanUp()
{
	LOG("Freeing all enemies");

	for(uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if(enemies[i] != nullptr)
		{
			delete enemies[i];
			enemies[i] = nullptr;
		}
	}
	App->textures->Unload(texture);

	return true;
}

bool ModuleEnemies::AddEnemy(ENEMY_TYPE type, int x, int y)
{
	bool ret = false;

	for(uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if(spawnQueue[i].type == ENEMY_TYPE::NO_TYPE)
		{
			spawnQueue[i].type = type;
			spawnQueue[i].x = x;
			spawnQueue[i].y = y;
			ret = true;
			break;
		}
	}

	return ret;
}

void ModuleEnemies::HandleEnemiesSpawn()
{
	// Iterate all the enemies queue
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (spawnQueue[i].type != ENEMY_TYPE::NO_TYPE)
		{
			// Spawn a new enemy if the screen has reached a spawn position
			if (spawnQueue[i].y * SCREEN_SIZE < App->render->camera.y + (App->render->camera.y * SCREEN_SIZE) + SPAWN_MARGIN)
			{
				LOG("Spawning enemy at %d", spawnQueue[i].x * SCREEN_SIZE);

				SpawnEnemy(spawnQueue[i]);
				spawnQueue[i].type = ENEMY_TYPE::NO_TYPE; // Removing the newly spawned enemy from the queue
			}
		}
	}
}

void ModuleEnemies::HandleEnemiesDespawn()
{
	// Iterate existing enemies
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
		{
			// Delete the enemy when it has reached the end of the screen
			if (App->render->camera.y < -500) {

				if (enemies[i]->position.y * SCREEN_SIZE > (App->render->camera.y) + SPAWN_MARGIN)
				{
					LOG("DeSpawning enemy at %d", enemies[i]->position.x * SCREEN_SIZE);

					enemies[i]->SetToDelete();
				}
			}
		}
	}
}

void ModuleEnemies::SpawnEnemy(const EnemySpawnpoint& info)
{
	// Find an empty slot in the enemies array
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] == nullptr)
		{
			switch (info.type)
			{
				case ENEMY_TYPE::GREENPLANE:
					enemies[i] = new Enemy_GreenPlane(info.x, info.y);
					break;

				case ENEMY_TYPE::REDLOOPPLANE:
					enemies[i] = new Enemy_RedLoopPlane(info.x, info.y);
					break;
				case ENEMY_TYPE::GREENBOMBER:
					enemies[i] = new Enemy_Green_Bomber(info.x, info.y);
					break;
				case ENEMY_TYPE::TURRETSHIP:
					enemies[i] = new Enemy_Turret(info.x, info.y);
					break;
				case ENEMY_TYPE::SHIP:
					enemies[i] = new Enemy_Ship(info.x, info.y);
					break;
				case ENEMY_TYPE::TURRETBOSS:
					enemies[i] = new Enemy_Turret_Boss(info.x, info.y);
					break;
				case ENEMY_TYPE::BOSS:
					enemies[i] = new Enemy_Boss(info.x, info.y);
					break;
				case ENEMY_TYPE::BOSSCORE:
					enemies[i] = new Enemy_Boss_Core(info.x, info.y);
					break;
			
			}
			enemies[i]->texture = texture;
			enemies[i]->destroyedFx = enemyDestroyedFx;
			
			break;
		}
	}
}

void ModuleEnemies::OnCollision(Collider* c1, Collider* c2)
{
	for(uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if(enemies[i] != nullptr && enemies[i]->GetCollider() == c1)
		{
			enemies[i]->OnCollision(c2); //Notify the enemy of a collision
			
			break;
		}
	}
}