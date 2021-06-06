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
	App->enemies->AddEnemy(ENEMY_TYPE::GREENPLANE, 350, -100);
	App->enemies->AddEnemy(ENEMY_TYPE::GREENPLANE, 300, -120);
	App->enemies->AddEnemy(ENEMY_TYPE::GREENPLANE, 250, -140);
	App->enemies->AddEnemy(ENEMY_TYPE::GREENPLANE, 200, -160);
	App->enemies->AddEnemy(ENEMY_TYPE::GREENPLANE, 50, -100);
	App->enemies->AddEnemy(ENEMY_TYPE::GREENPLANE, 100, -120);
	App->enemies->AddEnemy(ENEMY_TYPE::GREENPLANE, 150, -140);
	
	App->enemies->AddEnemy(ENEMY_TYPE::GREENPLANE, 350, -220);
	App->enemies->AddEnemy(ENEMY_TYPE::GREENPLANE, 300, -200);
	App->enemies->AddEnemy(ENEMY_TYPE::GREENPLANE, 250, -180);
	App->enemies->AddEnemy(ENEMY_TYPE::GREENPLANE, 50, -220);
	App->enemies->AddEnemy(ENEMY_TYPE::GREENPLANE, 100, -200);
	App->enemies->AddEnemy(ENEMY_TYPE::GREENPLANE, 150, -180);

	App->enemies->AddEnemy(ENEMY_TYPE::GREENPLANE, 50, -400);
	App->enemies->AddEnemy(ENEMY_TYPE::GREENPLANE, 80, -430);
	App->enemies->AddEnemy(ENEMY_TYPE::GREENPLANE, 110, -460);
	App->enemies->AddEnemy(ENEMY_TYPE::GREENPLANE, 140, -490);
	App->enemies->AddEnemy(ENEMY_TYPE::GREENPLANE, 200, -400);
	App->enemies->AddEnemy(ENEMY_TYPE::GREENPLANE, 230, -430);
	App->enemies->AddEnemy(ENEMY_TYPE::GREENPLANE, 260, -460);
	App->enemies->AddEnemy(ENEMY_TYPE::GREENPLANE, 290, -490);

	App->enemies->AddEnemy(ENEMY_TYPE::GREENPLANE, 110, -720);
	App->enemies->AddEnemy(ENEMY_TYPE::GREENPLANE, 140, -690);
	App->enemies->AddEnemy(ENEMY_TYPE::GREENPLANE, 170, -660);
	App->enemies->AddEnemy(ENEMY_TYPE::GREENPLANE, 200, -630);
	App->enemies->AddEnemy(ENEMY_TYPE::GREENPLANE, 250, -720);
	App->enemies->AddEnemy(ENEMY_TYPE::GREENPLANE, 280, -690);
	App->enemies->AddEnemy(ENEMY_TYPE::GREENPLANE, 320, -660);
	App->enemies->AddEnemy(ENEMY_TYPE::GREENPLANE, 350, -630);

	App->enemies->AddEnemy(ENEMY_TYPE::GREENPLANE, 350, -780);
	App->enemies->AddEnemy(ENEMY_TYPE::GREENPLANE, 300, -800);
	App->enemies->AddEnemy(ENEMY_TYPE::GREENPLANE, 250, -820);
	App->enemies->AddEnemy(ENEMY_TYPE::GREENPLANE, 200, -840);
	App->enemies->AddEnemy(ENEMY_TYPE::GREENPLANE, 50, -780);
	App->enemies->AddEnemy(ENEMY_TYPE::GREENPLANE, 100, -800);
	App->enemies->AddEnemy(ENEMY_TYPE::GREENPLANE, 150, -820);

	App->enemies->AddEnemy(ENEMY_TYPE::GREENPLANE, 300, -1200);
	App->enemies->AddEnemy(ENEMY_TYPE::GREENPLANE, 320, -1220);
	App->enemies->AddEnemy(ENEMY_TYPE::GREENPLANE, 340, -1240);
	App->enemies->AddEnemy(ENEMY_TYPE::GREENPLANE, 100, -1200);
	App->enemies->AddEnemy(ENEMY_TYPE::GREENPLANE, 80, -1220);
	App->enemies->AddEnemy(ENEMY_TYPE::GREENPLANE, 60, -1240);
	App->enemies->AddEnemy(ENEMY_TYPE::GREENPLANE, 300, -1200);
	App->enemies->AddEnemy(ENEMY_TYPE::GREENPLANE, 320, -1220);
	App->enemies->AddEnemy(ENEMY_TYPE::GREENPLANE, 340, -1240);
	App->enemies->AddEnemy(ENEMY_TYPE::GREENPLANE, 100, -1200);
	App->enemies->AddEnemy(ENEMY_TYPE::GREENPLANE, 80, -1220);
	App->enemies->AddEnemy(ENEMY_TYPE::GREENPLANE, 60, -1240);

	App->enemies->AddEnemy(ENEMY_TYPE::REDLOOPPLANE, 75, -500);
	App->enemies->AddEnemy(ENEMY_TYPE::REDLOOPPLANE, 300, -500);
	App->enemies->AddEnemy(ENEMY_TYPE::REDLOOPPLANE, 125, -550);
	App->enemies->AddEnemy(ENEMY_TYPE::REDLOOPPLANE, 250, -550);
	App->enemies->AddEnemy(ENEMY_TYPE::REDLOOPPLANE, 160, -600);
	App->enemies->AddEnemy(ENEMY_TYPE::REDLOOPPLANE, 210, -600);

	App->enemies->AddEnemy(ENEMY_TYPE::REDLOOPPLANE, 130, -1050);
	App->enemies->AddEnemy(ENEMY_TYPE::REDLOOPPLANE, 150, -1070);
	App->enemies->AddEnemy(ENEMY_TYPE::REDLOOPPLANE, 170, -1090);
	App->enemies->AddEnemy(ENEMY_TYPE::REDLOOPPLANE, 230, -1050);
	App->enemies->AddEnemy(ENEMY_TYPE::REDLOOPPLANE, 250, -1070);
	App->enemies->AddEnemy(ENEMY_TYPE::REDLOOPPLANE, 270, -1090);

	App->enemies->AddEnemy(ENEMY_TYPE::REDLOOPPLANE, 145, -1730);
	App->enemies->AddEnemy(ENEMY_TYPE::REDLOOPPLANE, 84, -1750);
	App->enemies->AddEnemy(ENEMY_TYPE::REDLOOPPLANE, 84, -1780);
	App->enemies->AddEnemy(ENEMY_TYPE::REDLOOPPLANE, 65, -1850);
	App->enemies->AddEnemy(ENEMY_TYPE::REDLOOPPLANE, 308, -1850);
	App->enemies->AddEnemy(ENEMY_TYPE::REDLOOPPLANE, 268, -1900);
	App->enemies->AddEnemy(ENEMY_TYPE::REDLOOPPLANE, 116, -1900);
	App->enemies->AddEnemy(ENEMY_TYPE::REDLOOPPLANE, 300, -1900);

	App->enemies->AddEnemy(ENEMY_TYPE::REDLOOPPLANE, 75, -3500);
	App->enemies->AddEnemy(ENEMY_TYPE::REDLOOPPLANE, 300, -3500);
	App->enemies->AddEnemy(ENEMY_TYPE::REDLOOPPLANE, 125, -3550);
	App->enemies->AddEnemy(ENEMY_TYPE::REDLOOPPLANE, 250, -3550);
	App->enemies->AddEnemy(ENEMY_TYPE::REDLOOPPLANE, 160, -3600);
	App->enemies->AddEnemy(ENEMY_TYPE::REDLOOPPLANE, 210, -3600);

	App->enemies->AddEnemy(ENEMY_TYPE::GREENBOMBER, 175, -1000);
	App->enemies->AddEnemy(ENEMY_TYPE::GREENBOMBER, 175, -2000);

	App->enemies->AddEnemy(ENEMY_TYPE::SHIP, 175, -2300);
	App->enemies->AddEnemy(ENEMY_TYPE::SHIP, 110, -2700);
	App->enemies->AddEnemy(ENEMY_TYPE::SHIP, 75, -3000);
	App->enemies->AddEnemy(ENEMY_TYPE::SHIP, 300, -3000);
	App->enemies->AddEnemy(ENEMY_TYPE::SHIP, 135, -3400);
	App->enemies->AddEnemy(ENEMY_TYPE::SHIP, 275, -3700);
	App->enemies->AddEnemy(ENEMY_TYPE::SHIP, 75, -3900);
	

	App->enemies->AddEnemy(ENEMY_TYPE::BOSS, 150, -4450);

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	App->player->Enable();
	App->particles->Enable();
	App->enemies->Enable();
	App->UI->Enable();




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