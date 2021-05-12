#include "SceneInit.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"

#include "ModulePlayer.h"
#include "ModuleFadeToBlack.h"
#include "ModuleInput.h"

#include "SDL/include/SDL_scancode.h"

SceneInit::SceneInit(bool startEnabled) : Module(startEnabled)
{

}

SceneInit::~SceneInit()
{

}

// Load assets
bool SceneInit::Start()
{
	LOG("Loading background assets");

	bool ret = true;
	bool audio = true;


	bgTexture = App->textures->Load("Assets/Intro_screen.png");
	audio = App->audio->PlayMusic("Assets/Audio/015-Ending.ogg", 0.1f);


	App->render->camera.x = 0;
	App->render->camera.y = 0;

	
	return ret;
}

update_status SceneInit::Update()
{
	App->render->camera.x = 0;
	App->render->camera.y = 0;
	timer++;
	if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN || timer == 200)
	{
		App->fade->FadeToBlack(this, (Module*)App->sceneIntro, 60);
	}


	return update_status::UPDATE_CONTINUE;
}

// Update: draw background
update_status SceneInit::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 0, 0, NULL);

	return update_status::UPDATE_CONTINUE;
}

bool SceneInit::CleanUp()
{
	
	App->textures->Unload(bgTexture);
	return true;
}
