#include "SceneLevel2.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleEnemies.h"
#include "ModulePlayer.h"
#include "ModuleFadeToBlack.h"
#include "ModuleInput.h"
#include "ModuleUI.h"
#include "ModuleParticles.h"
#include "SDL/include/SDL_scancode.h"
#include <stdio.h> 

SceneLevel2::SceneLevel2(bool startEnabled) : Module(startEnabled)
{


}

SceneLevel2::~SceneLevel2()
{

}

// Load assets
bool SceneLevel2::Start()
{
	App->collisions->Enable();
	LOG("Loading background assets");
	timer = 0;
	bool ret = true;


	bgTexture = App->textures->Load("Assets/SeaMap.png");
	App->audio->PlayMusic("Assets/Audio/stage2.ogg", 1.0f);


	// Enemies ---
	App->enemies->AddEnemy(ENEMY_TYPE::GREENBOMBER, 175, -1000);
	App->enemies->AddEnemy(ENEMY_TYPE::GREENBOMBER, 175, -2000);

	App->enemies->AddEnemy(ENEMY_TYPE::SHIP, 175, -2300);
	App->enemies->AddEnemy(ENEMY_TYPE::SHIP, 75, -3000);
	App->enemies->AddEnemy(ENEMY_TYPE::SHIP, 300, -3000);
	App->enemies->AddEnemy(ENEMY_TYPE::SHIP, 275, -3700);
	App->enemies->AddEnemy(ENEMY_TYPE::SHIP, 75, -3900);
	

	App->enemies->AddEnemy(ENEMY_TYPE::BOSS, 150, -4450);

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	App->player->Enable();
	App->enemies->Enable();
	App->UI->Enable();
	App->particles->Enable();




	return ret;
}

update_status SceneLevel2::Update()
{
	introTimer++;
	if (introTimer <= 160)
	{
		App->player->end = false;
	}
	if (App->render->camera.y >= -4500)
	{
		App->render->camera.y -= 1;
		App->player->playerMove = true;
	}
	else
	{
		App->player->playerMove = false;
		endTime++;
	}
	
	if(endTime == 3600 || App->render->percentage <= 0)
	{
		App->fade->FadeToBlack(this, (Module*)App->sceneEnd, 60);
	}
	

	if (App->input->keys[SDL_SCANCODE_F2] == KEY_STATE::KEY_DOWN)
	{
		App->fade->FadeToBlack(this, (Module*)App->sceneEnd, 60);
	}
	if (App->player->life <= 0)
	{
		timer++;
		if (timer == 300)
		{
			App->fade->FadeToBlack(this, (Module*)App->sceneEnd, 60);
		}
	}
	return update_status::UPDATE_CONTINUE;
}

// Update: draw background
update_status SceneLevel2::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 0, -5600, NULL);


	return update_status::UPDATE_CONTINUE;
}

void SceneLevel2::OnCollision(Collider* c1, Collider* c2)
{

}

bool SceneLevel2::CleanUp()
{
	App->player->Disable();
	App->enemies->Disable();
	App->collisions->Disable();
	App->UI->Disable();
	App->particles->Disable();
	App->textures->Unload(bgTexture);

	return true;
}