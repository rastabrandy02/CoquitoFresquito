#include "SceneEnd.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"

#include "ModulePlayer.h"
#include "ModuleFadeToBlack.h"
#include "ModuleInput.h"

#include "SDL/include/SDL_scancode.h"

SceneEnd::SceneEnd(bool startEnabled) : Module(startEnabled)
{

}

SceneEnd::~SceneEnd()
{

}

// Load assets
bool SceneEnd::Start()
{
	LOG("Loading background assets");

	bool ret = true;
	bool audio = true;


	winTexture = App->textures->Load("Assets/end_level.png");
	audio = App->audio->PlayMusic("Assets/Audio/015-Ending.ogg", 0.1f);


	App->render->camera.x = 0;
	App->render->camera.y = 0;


	return ret;
}

update_status SceneEnd::Update()
{
	App->render->camera.x = 0;
	App->render->camera.y = 0;
	if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN)
	{
		App->fade->FadeToBlack(this, (Module*)App->sceneIntro, 90);
	}

	return update_status::UPDATE_CONTINUE;
}

// Update: draw background
update_status SceneEnd::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(winTexture, 0, 0, NULL);

	return update_status::UPDATE_CONTINUE;
}

bool SceneEnd::CleanUp()
{

	App->textures->Unload(winTexture);
	return true;
}
