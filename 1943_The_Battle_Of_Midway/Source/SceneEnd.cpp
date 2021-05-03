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
	planeAnim.PushBack({ 113, 53, 36, 10 });
	planeAnim.PushBack({ 182, 49, 42, 24 });
	planeAnim.PushBack({ 257, 58, 36, 37 });
	planeAnim.PushBack({ 70, 117, 49, 41 });
	planeAnim.PushBack({ 161, 122, 62, 43 });
	planeAnim.PushBack({ 247, 116, 103, 57 });
	planeAnim.PushBack({ 72, 191, 104, 89 });
	planeAnim.PushBack({ 203, 188, 118, 178 });
	planeAnim.speed = 0.1f;
	planeAnim.loop = false;
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


	planeTex = App->textures->Load("Assets/Art/Endings/plane.png");

	currentAnim = &planeAnim;



	audio = App->audio->PlayMusic("Assets/Audio/015-Ending.ogg", 0.1f);

	winTexture = App->textures->Load("Assets/end_level.png");

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
	planeAnim.Update();
	return update_status::UPDATE_CONTINUE;
}

// Update: draw background
update_status SceneEnd::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(winTexture, 0, 0, NULL);
	App->render->Blit(planeTex, 200, 200, &planeAnim.GetCurrentFrame(), 0.0f, false);
	return update_status::UPDATE_CONTINUE;
}

bool SceneEnd::CleanUp()
{
	planeAnim.Reset();
	App->textures->Unload(winTexture);
	return true;
}
