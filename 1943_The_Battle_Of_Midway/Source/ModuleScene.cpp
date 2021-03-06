#include "ModuleScene.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleEnemies.h"

ModuleScene::ModuleScene()
{

}

ModuleScene::~ModuleScene()
{

}

// Load assets
bool ModuleScene::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	bgTexture = App->textures->Load("Assets/background.png");
	App->audio->PlayMusic("Assets/stage1.ogg", 1.0f);

	App->collisions->AddCollider({ 0, 0, 1000, 1000 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 240, 0, 1000, 1000 }, Collider::Type::WALL);
	

	// Enemies ---
	App->enemies->AddEnemy(ENEMY_TYPE::REDPLANE, 200, -170);


	return ret;
}

update_status ModuleScene::Update()
{
	App->render->camera.y -= 3;

	return update_status::UPDATE_CONTINUE;
}

// Update: draw background
update_status ModuleScene::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 0, 0, NULL);

	return update_status::UPDATE_CONTINUE;
}