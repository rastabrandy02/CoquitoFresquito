#include "SceneIntro.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"

#include "ModulePlayer.h"
#include "ModuleFadeToBlack.h"
#include "ModuleInput.h"

#include "SDL/include/SDL_scancode.h"

SceneIntro::SceneIntro(bool startEnabled) : Module(startEnabled)
{

}

SceneIntro::~SceneIntro()
{

}

// Load assets
bool SceneIntro::Start()
{
	LOG("Loading background assets");

	bool ret = true;
	bool audio = true;

	bgTexture = App->textures->Load("Assets/title_screen.png");
	audio = App->audio->PlayMusic("Assets/Audio/16-Credits.ogg", 1.0f);



	App->render->camera.x = 0;
	App->render->camera.y = 0;

	return ret;
}

update_status SceneIntro::Update()
{
	GamePad& pad = App->input->pads[0];
	App->render->camera.x = 0;
	App->render->camera.y = 0;
	if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN || pad.a)
	{
		App->fade->FadeToBlack(this, (Module*)App->sceneLevel_1, 90);
	}

	return update_status::UPDATE_CONTINUE;
}

// Update: draw background
update_status SceneIntro::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 0, 0, NULL);

	return update_status::UPDATE_CONTINUE;
}

bool SceneIntro::CleanUp()
{
	
	App->textures->Unload(bgTexture);
	return true;
}
