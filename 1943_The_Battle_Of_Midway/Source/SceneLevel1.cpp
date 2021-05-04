#include "SceneLevel1.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleEnemies.h"
#include "ModulePlayer.h"
#include "ModuleFadeToBlack.h"
#include "ModuleInput.h"

#include "SDL/include/SDL_scancode.h"
#include <stdio.h> 
SceneLevel1::SceneLevel1(bool startEnabled) : Module(startEnabled)
{
	
	
}

SceneLevel1::~SceneLevel1()
{

}

// Load assets
bool SceneLevel1::Start()
{
	App->collisions->Enable();
	LOG("Loading background assets");
	timer = 0;
	bool ret = true;
	healtBar1 = App->textures->Load("Assets/Lifebars/life_bar_1.png");
	healtBar2 = App->textures->Load("Assets/Lifebars/life_bar_2.png");
	healtBar3 = App->textures->Load("Assets/Lifebars/life_bar_3.png");
	healtBar4 = App->textures->Load("Assets/Lifebars/life_bar_4.png");
	healtBar5 = App->textures->Load("Assets/Lifebars/life_bar_5.png");
	healtBar6 = App->textures->Load("Assets/Lifebars/life_bar_6.png");
	healtBar7 = App->textures->Load("Assets/Lifebars/life_bar_7.png");
	healtBar8 = App->textures->Load("Assets/Lifebars/life_bar_8.png");
	healtBar9 = App->textures->Load("Assets/Lifebars/life_bar_9.png");


	cloudTexture = App->textures->Load("Assets/CloudsMap.png");
	bgTexture = App->textures->Load("Assets/SeaMap.png");
	App->audio->PlayMusic("Assets/Audio/stage1.ogg", 1.0f);


	// Enemies ---
	App->enemies->AddEnemy(ENEMY_TYPE::REDPLANE, 300, 0);
	App->enemies->AddEnemy(ENEMY_TYPE::REDPLANE, 320, -20);
	App->enemies->AddEnemy(ENEMY_TYPE::REDPLANE, 340, -40);
	App->enemies->AddEnemy(ENEMY_TYPE::REDPLANE, 100, 0);
	App->enemies->AddEnemy(ENEMY_TYPE::REDPLANE, 80, -20);
	App->enemies->AddEnemy(ENEMY_TYPE::REDPLANE, 60, -40);

	App->enemies->AddEnemy(ENEMY_TYPE::REDPLANE, 200, -60);

	App->enemies->AddEnemy(ENEMY_TYPE::REDPLANE, 300, -100);
	App->enemies->AddEnemy(ENEMY_TYPE::REDPLANE, 320, -120);
	App->enemies->AddEnemy(ENEMY_TYPE::REDPLANE, 340, -140);
	App->enemies->AddEnemy(ENEMY_TYPE::REDPLANE, 100, -100);
	App->enemies->AddEnemy(ENEMY_TYPE::REDPLANE, 80, -120);
	App->enemies->AddEnemy(ENEMY_TYPE::REDPLANE, 60, -140);

	App->enemies->AddEnemy(ENEMY_TYPE::REDPLANE, 250, -400);
	App->enemies->AddEnemy(ENEMY_TYPE::REDPLANE, 275, -420);
	App->enemies->AddEnemy(ENEMY_TYPE::REDPLANE, 300, -440);
	App->enemies->AddEnemy(ENEMY_TYPE::REDPLANE, 150, -400);
	App->enemies->AddEnemy(ENEMY_TYPE::REDPLANE, 125, -420);
	App->enemies->AddEnemy(ENEMY_TYPE::REDPLANE, 100, -440);

	App->enemies->AddEnemy(ENEMY_TYPE::REDPLANE, 200, -320);
	App->enemies->AddEnemy(ENEMY_TYPE::REDPLANE, 150, -320);
	App->enemies->AddEnemy(ENEMY_TYPE::REDPLANE, 250, -320);
	App->enemies->AddEnemy(ENEMY_TYPE::REDPLANE, 175, -300);
	App->enemies->AddEnemy(ENEMY_TYPE::REDPLANE, 225, -300);

	App->enemies->AddEnemy(ENEMY_TYPE::REDPLANE, 25, -580);
	App->enemies->AddEnemy(ENEMY_TYPE::REDPLANE, 50, -550);
	App->enemies->AddEnemy(ENEMY_TYPE::REDPLANE, 75, -580);
	App->enemies->AddEnemy(ENEMY_TYPE::REDPLANE, 100, -550);
	App->enemies->AddEnemy(ENEMY_TYPE::REDPLANE, 125, -580);

	App->enemies->AddEnemy(ENEMY_TYPE::REDPLANE, 275, -580);
	App->enemies->AddEnemy(ENEMY_TYPE::REDPLANE, 300, -550);
	App->enemies->AddEnemy(ENEMY_TYPE::REDPLANE, 325, -580);
	App->enemies->AddEnemy(ENEMY_TYPE::REDPLANE, 350, -550);
	App->enemies->AddEnemy(ENEMY_TYPE::REDPLANE, 375, -580);
	
	App->collisions->AddCollider({ 0, -5400, 400, 200 }, Collider::Type::WIN);

	App->enemies->AddEnemy(ENEMY_TYPE::REDLOOPPLANE, 150, -110);
	App->enemies->AddEnemy(ENEMY_TYPE::REDLOOPPLANE, 150, -80);
	App->enemies->AddEnemy(ENEMY_TYPE::REDLOOPPLANE, 150, -50);

	App->enemies->AddEnemy(ENEMY_TYPE::REDLOOPPLANE, 250, -110);
	App->enemies->AddEnemy(ENEMY_TYPE::REDLOOPPLANE, 250, -80);
	App->enemies->AddEnemy(ENEMY_TYPE::REDLOOPPLANE, 250, -50);

	App->enemies->AddEnemy(ENEMY_TYPE::REDLOOPPLANE, 50, -600);
	App->enemies->AddEnemy(ENEMY_TYPE::REDLOOPPLANE, 75, -600);
	App->enemies->AddEnemy(ENEMY_TYPE::REDLOOPPLANE, 100, -600);
	App->enemies->AddEnemy(ENEMY_TYPE::REDLOOPPLANE, 275, -600);
	App->enemies->AddEnemy(ENEMY_TYPE::REDLOOPPLANE, 300, -600);
	App->enemies->AddEnemy(ENEMY_TYPE::REDLOOPPLANE, 325, -600);


	App->enemies->AddEnemy(ENEMY_TYPE::REDLOOPPLANE, 275, -1000);
	App->enemies->AddEnemy(ENEMY_TYPE::REDLOOPPLANE, 75, -1000);

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	App->player->Enable();
	App->enemies->Enable();

	



	return ret;
}

update_status SceneLevel1::Update()
{
	App->render->camera.y -= 2;
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
update_status SceneLevel1::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 0, -5600, NULL);
	App->render->Blit(cloudTexture, 0, -5600, NULL, 0.75f);
	
	switch (App->player->life)
	{
	case 9:
		App->render->Blit(healtBar1, 0, 488, NULL, 0.0f, false);
		break;
	case 8:
		App->render->Blit(healtBar2, 0, 488, NULL, 0.0f, false);
		break;
	case 7:
		App->render->Blit(healtBar3, 0, 488, NULL, 0.0f, false);
		break;
	case 6:
		App->render->Blit(healtBar4, 0, 488, NULL, 0.0f, false);
		break;
	case 5:
		App->render->Blit(healtBar5, 0, 488, NULL, 0.0f, false);
		break;
	case 4:
		App->render->Blit(healtBar6, 0, 488, NULL, 0.0f, false);
		break;
	case 3:
		App->render->Blit(healtBar7, 0, 488, NULL, 0.0f, false);
	case 2:
		App->render->Blit(healtBar8, 0, 488, NULL, 0.0f, false);
		break;
	case 1:
		App->render->Blit(healtBar9, 0, 488, NULL, 0.0f, false);
		break;
	default:
		break;
	}


	return update_status::UPDATE_CONTINUE;
}

void SceneLevel1::OnCollision(Collider* c1, Collider* c2)
{
	
}

bool SceneLevel1::CleanUp()
{
	App->player->Disable();
	App->enemies->Disable();
	App->collisions->Disable();
	App->textures->Unload(bgTexture);
	App->textures->Unload(cloudTexture);

	return true;
}