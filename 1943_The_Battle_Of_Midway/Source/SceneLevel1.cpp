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
	healthBarAnim.PushBack({ 274, 69, 250, 24 });
	
}

SceneLevel1::~SceneLevel1()
{

}

// Load assets
bool SceneLevel1::Start()
{
	LOG("Loading background assets");

	bool ret = true;
	healtBar = App->textures->Load("Assets/life_bar.png");

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


	App->enemies->AddEnemy(ENEMY_TYPE::REDPLANE, 300, -100);
	App->enemies->AddEnemy(ENEMY_TYPE::REDPLANE, 320, -120);
	App->enemies->AddEnemy(ENEMY_TYPE::REDPLANE, 340, -140);
	App->enemies->AddEnemy(ENEMY_TYPE::REDPLANE, 100, -100);
	App->enemies->AddEnemy(ENEMY_TYPE::REDPLANE, 80, -120);
	App->enemies->AddEnemy(ENEMY_TYPE::REDPLANE, 60, -140);

	
	App->collisions->AddCollider({ 0, -5400, 400, 200 }, Collider::Type::WIN);

	App->enemies->AddEnemy(ENEMY_TYPE::REDLOOPPLANE, 150, -100);

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
	
	return update_status::UPDATE_CONTINUE;
}

// Update: draw background
update_status SceneLevel1::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 0, -5600, NULL);
	App->render->Blit(cloudTexture, 0, -5600, NULL, 0.75f);
	App->render->Blit(healtBar, 0, 300, &healthBarAnim.GetCurrentFrame(), 0.0f, false);


	return update_status::UPDATE_CONTINUE;
}

void SceneLevel1::OnCollision(Collider* c1, Collider* c2)
{
	
}

bool SceneLevel1::CleanUp()
{
	App->player->Disable();
	App->enemies->Disable();
	
	App->textures->Unload(bgTexture);
	App->textures->Unload(cloudTexture);

	return true;
}