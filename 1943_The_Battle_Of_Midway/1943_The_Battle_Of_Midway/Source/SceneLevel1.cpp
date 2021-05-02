#include "SceneLevel1.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleEnemies.h"
#include "ModulePlayer.h"

SceneLevel1::SceneLevel1(bool startEnabled) : Module(startEnabled)
{

}

SceneLevel1::~SceneLevel1()
{

}

// Load assets
bool SceneLevel1::Start()
{
	LOG("Loading background assets");

	bool ret = true;
	bool music;

<<<<<<< HEAD
	bgTexture = App->textures->Load("Assets/SeaMap.png");
	cloudTexture = App->textures->Load("Assets/CloudsMap.png");
	App->audio->PlayMusic("Assets/stage1.ogg", 1.0f);
=======
	
	music = App->audio->PlayMusic("Assets/Music/stage1.ogg", 1.0f);
	
>>>>>>> 15cb3c20e05cb07b4659846166ceaa499b2f6871


	// Enemies ---
<<<<<<< HEAD
	App->enemies->AddEnemy(ENEMY_TYPE::REDPLANE, 300, 80);
=======
	App->enemies->AddEnemy(ENEMY_TYPE::REDPLANE, 200, 280);
	bgTexture = App->textures->Load("Assets/background.png");
>>>>>>> 15cb3c20e05cb07b4659846166ceaa499b2f6871

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	App->player->Enable();
	App->enemies->Enable();

	return ret;
}

update_status SceneLevel1::Update()
{
	App->render->camera.y -= 2;

	return update_status::UPDATE_CONTINUE;
}

// Update: draw background
update_status SceneLevel1::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(cloudTexture, 0, -5600, NULL);
	App->render->Blit(bgTexture, 0, -5600, NULL);

	return update_status::UPDATE_CONTINUE;
}

bool SceneLevel1::CleanUp()
{
	App->player->Disable();
	App->enemies->Disable();

	return true;
}