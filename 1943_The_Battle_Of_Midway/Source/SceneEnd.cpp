#include "SceneEnd.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"

#include "ModulePlayer.h"
#include "ModuleFadeToBlack.h"
#include "ModuleInput.h"
#include "Path.h"
#include <stdio.h>

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
	char lookupTable3[] = { "0123456789abcdefghijklmnopqrstuvwxyz" };
	textFont = App->fonts->Load("Assets/textfontbig.png", lookupTable3, 1);

	audio = App->audio->PlayMusic("Assets/Audio/015-Ending.ogg", 0.1f);

	winTexture = App->textures->Load("Assets/end_level.png");
	loseTexture = App->textures->Load("Assets/Death_Screen.png");

	App->render->camera.x = 0;
	App->render->camera.y = 0;
	position.x = 100;
	position.y = 100;

	path.PushBack({ 0.2f, 0.0f }, 1,&planeAnim);
	path.PushBack({ 0.2f, 0.0f }, 1, &planeAnim);
	path.PushBack({ 0.2f, 0.2f }, 1, &planeAnim);
	path.PushBack({ 0.2f, 0.2f }, 1, &planeAnim);
	path.PushBack({ -0.2f, 0.2f }, 2, &planeAnim);
	path.PushBack({ -0.2f, -0.2f }, 1, &planeAnim);
	path.PushBack({ -0.2f, -0.2f }, 1, &planeAnim);
	path.PushBack({ 0.0f, 0.0f }, 3000, &planeAnim);


	
	path.loop = false;

	

	return ret;
}

update_status SceneEnd::Update()
{
	GamePad& pad = App->input->pads[0];
	position += path.GetRelativePosition();
	
	if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN || pad.a)
	{
		App->fade->FadeToBlack(this, (Module*)App->sceneIntro, 90);
	}
	planeAnim.Update();
	path.Update();

	return update_status::UPDATE_CONTINUE;
}

// Update: draw background
update_status SceneEnd::PostUpdate()
{
	// Draw everything --------------------------------------
	if (App->player->life != 0)
	{
		App->render->Blit(winTexture, 0, 0, NULL);
		App->render->Blit(planeTex, position.x, position.y, &planeAnim.GetCurrentFrame(), 0.0f, false);
		if (App->render->percentage <= 25)
		{
			App->fonts->BlitText(100, 200, textFont, "mission");
			App->fonts->BlitText(95, 230, textFont, "compleated");
		}
		else
		{
			
			sprintf_s(text, "%i", (100 - App->render->percentage));
			App->fonts->BlitText(100, 200, textFont, "mission");
			App->fonts->BlitText(95, 230, textFont, "failed");
			App->fonts->BlitText(95, 260, textFont, text);
			App->fonts->BlitText(120, 260, textFont, "compleated");
		}
	}
	else
	{
		App->render->Blit(loseTexture, 0, 0, NULL);
	}
	return update_status::UPDATE_CONTINUE;
}

bool SceneEnd::CleanUp()
{
	planeAnim.Reset();
	
	App->textures->Unload(winTexture);
	App->textures->Unload(planeTex);
	return true;
}
