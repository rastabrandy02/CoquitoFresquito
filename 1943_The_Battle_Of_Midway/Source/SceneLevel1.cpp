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
#include "ModuleUI.h"

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
	


	cloudTexture = App->textures->Load("Assets/CloudsMap.png");
	bgTexture = App->textures->Load("Assets/SeaMap.png");
	App->audio->PlayMusic("Assets/Audio/stage1.ogg", 1.0f);

	App->collisions->AddCollider({ 0, -5400, 400, 200 }, Collider::Type::LVL2);

	// Enemies ---
	
	/*App->enemies->AddEnemy(ENEMY_TYPE::GREENPLANE, 300, 0);
	App->enemies->AddEnemy(ENEMY_TYPE::GREENPLANE, 320, -20);
	App->enemies->AddEnemy(ENEMY_TYPE::GREENPLANE, 340, -40);
	App->enemies->AddEnemy(ENEMY_TYPE::GREENPLANE, 100, 0);
	App->enemies->AddEnemy(ENEMY_TYPE::GREENPLANE, 80, -20);
	App->enemies->AddEnemy(ENEMY_TYPE::GREENPLANE, 60, -40);
	App->enemies->AddEnemy(ENEMY_TYPE::GREENPLANE, 300, -100);
	App->enemies->AddEnemy(ENEMY_TYPE::GREENPLANE, 320, -120);
	App->enemies->AddEnemy(ENEMY_TYPE::GREENPLANE, 340, -140);
	App->enemies->AddEnemy(ENEMY_TYPE::GREENPLANE, 100, -100);
	App->enemies->AddEnemy(ENEMY_TYPE::GREENPLANE, 80, -120);
	App->enemies->AddEnemy(ENEMY_TYPE::GREENPLANE, 60, -140);

	App->enemies->AddEnemy(ENEMY_TYPE::REDLOOPPLANE, 150, -110);
	App->enemies->AddEnemy(ENEMY_TYPE::REDLOOPPLANE, 150, -80);
	App->enemies->AddEnemy(ENEMY_TYPE::REDLOOPPLANE, 150, -50);
	App->enemies->AddEnemy(ENEMY_TYPE::REDLOOPPLANE, 250, -110);
	App->enemies->AddEnemy(ENEMY_TYPE::REDLOOPPLANE, 250, -80);
	App->enemies->AddEnemy(ENEMY_TYPE::REDLOOPPLANE, 250, -50);



	App->enemies->AddEnemy(ENEMY_TYPE::GREENPLANE, 300, -590);
	App->enemies->AddEnemy(ENEMY_TYPE::GREENPLANE, 330, -610);
	App->enemies->AddEnemy(ENEMY_TYPE::GREENPLANE, 360, -630);
	App->enemies->AddEnemy(ENEMY_TYPE::GREENPLANE, 110, -590);
	App->enemies->AddEnemy(ENEMY_TYPE::GREENPLANE, 80, -610);
	App->enemies->AddEnemy(ENEMY_TYPE::GREENPLANE, 50, -630);

	App->enemies->AddEnemy(ENEMY_TYPE::REDLOOPPLANE, 150, -650);
	App->enemies->AddEnemy(ENEMY_TYPE::REDLOOPPLANE, 150, -670);
	App->enemies->AddEnemy(ENEMY_TYPE::REDLOOPPLANE, 150, -690);
	App->enemies->AddEnemy(ENEMY_TYPE::REDLOOPPLANE, 250, -650);
	App->enemies->AddEnemy(ENEMY_TYPE::REDLOOPPLANE, 250, -670);
	App->enemies->AddEnemy(ENEMY_TYPE::REDLOOPPLANE, 250, -690);

	App->enemies->AddEnemy(ENEMY_TYPE::GREENPLANE, 100, -700);
	App->enemies->AddEnemy(ENEMY_TYPE::GREENPLANE, 100, -670);
	App->enemies->AddEnemy(ENEMY_TYPE::GREENPLANE, 230, -700);
	App->enemies->AddEnemy(ENEMY_TYPE::GREENPLANE, 230, -680);
	App->enemies->AddEnemy(ENEMY_TYPE::GREENPLANE, 300, -650);
	App->enemies->AddEnemy(ENEMY_TYPE::GREENPLANE, 320, -690);
	App->enemies->AddEnemy(ENEMY_TYPE::GREENPLANE, 340, -670);
	App->enemies->AddEnemy(ENEMY_TYPE::GREENPLANE, 150, -690);
	App->enemies->AddEnemy(ENEMY_TYPE::GREENPLANE, 80, -690);
	App->enemies->AddEnemy(ENEMY_TYPE::GREENPLANE, 60, -670);



	App->enemies->AddEnemy(ENEMY_TYPE::GREENBOMBER, 165, -900);

	App->enemies->AddEnemy(ENEMY_TYPE::GREENPLANE, 290, -1050);
	App->enemies->AddEnemy(ENEMY_TYPE::GREENPLANE, 320, -1090);
	App->enemies->AddEnemy(ENEMY_TYPE::GREENPLANE, 350, -1070);
	App->enemies->AddEnemy(ENEMY_TYPE::GREENPLANE, 110, -1090);
	App->enemies->AddEnemy(ENEMY_TYPE::GREENPLANE, 80, -1090);
	App->enemies->AddEnemy(ENEMY_TYPE::GREENPLANE, 50, -1070);

	App->enemies->AddEnemy(ENEMY_TYPE::REDLOOPPLANE, 130, -1050);
	App->enemies->AddEnemy(ENEMY_TYPE::REDLOOPPLANE, 150, -1070);
	App->enemies->AddEnemy(ENEMY_TYPE::REDLOOPPLANE, 170, -1090);
	App->enemies->AddEnemy(ENEMY_TYPE::REDLOOPPLANE, 230, -1050);
	App->enemies->AddEnemy(ENEMY_TYPE::REDLOOPPLANE, 250, -1070);
	App->enemies->AddEnemy(ENEMY_TYPE::REDLOOPPLANE, 270, -1090);

	App->enemies->AddEnemy(ENEMY_TYPE::GREENPLANE, 290, -1100);
	App->enemies->AddEnemy(ENEMY_TYPE::GREENPLANE, 320, -1130);
	App->enemies->AddEnemy(ENEMY_TYPE::GREENPLANE, 350, -1160);
	App->enemies->AddEnemy(ENEMY_TYPE::GREENPLANE, 120, -1100);
	App->enemies->AddEnemy(ENEMY_TYPE::GREENPLANE, 90, -1130);
	App->enemies->AddEnemy(ENEMY_TYPE::GREENPLANE, 60, -1160);



	App->enemies->AddEnemy(ENEMY_TYPE::GREENBOMBER, 50, -1200);
	App->enemies->AddEnemy(ENEMY_TYPE::GREENBOMBER, 350, -1400);

	App->enemies->AddEnemy(ENEMY_TYPE::REDLOOPPLANE, 130, -1250);
	App->enemies->AddEnemy(ENEMY_TYPE::REDLOOPPLANE, 150, -1270);
	App->enemies->AddEnemy(ENEMY_TYPE::REDLOOPPLANE, 170, -1290);
	App->enemies->AddEnemy(ENEMY_TYPE::REDLOOPPLANE, 230, -1250);
	App->enemies->AddEnemy(ENEMY_TYPE::REDLOOPPLANE, 250, -1270);
	App->enemies->AddEnemy(ENEMY_TYPE::REDLOOPPLANE, 270, -1290);



	App->enemies->AddEnemy(ENEMY_TYPE::GREENPLANE, 300, -1500);
	App->enemies->AddEnemy(ENEMY_TYPE::GREENPLANE, 320, -1520);
	App->enemies->AddEnemy(ENEMY_TYPE::GREENPLANE, 340, -1540);
	App->enemies->AddEnemy(ENEMY_TYPE::GREENPLANE, 100, -1500);
	App->enemies->AddEnemy(ENEMY_TYPE::GREENPLANE, 80, -1520);
	App->enemies->AddEnemy(ENEMY_TYPE::GREENPLANE, 60, -1540);
	App->enemies->AddEnemy(ENEMY_TYPE::GREENPLANE, 300, -1500);
	App->enemies->AddEnemy(ENEMY_TYPE::GREENPLANE, 320, -1520);
	App->enemies->AddEnemy(ENEMY_TYPE::GREENPLANE, 340, -1540);
	App->enemies->AddEnemy(ENEMY_TYPE::GREENPLANE, 100, -1500);
	App->enemies->AddEnemy(ENEMY_TYPE::GREENPLANE, 80, -1520);
	App->enemies->AddEnemy(ENEMY_TYPE::GREENPLANE, 60, -1540);

	App->enemies->AddEnemy(ENEMY_TYPE::REDLOOPPLANE, 150, -1610);
	App->enemies->AddEnemy(ENEMY_TYPE::REDLOOPPLANE, 150, -1680);
	App->enemies->AddEnemy(ENEMY_TYPE::REDLOOPPLANE, 150, -1650);
	App->enemies->AddEnemy(ENEMY_TYPE::REDLOOPPLANE, 250, -1610);
	App->enemies->AddEnemy(ENEMY_TYPE::REDLOOPPLANE, 250, -1680);
	App->enemies->AddEnemy(ENEMY_TYPE::REDLOOPPLANE, 250, -1650);

	App->enemies->AddEnemy(ENEMY_TYPE::GREENBOMBER, 50, -1900);

	App->enemies->AddEnemy(ENEMY_TYPE::GREENPLANE, 300, -1700);
	App->enemies->AddEnemy(ENEMY_TYPE::GREENPLANE, 320, -1720);
	App->enemies->AddEnemy(ENEMY_TYPE::GREENPLANE, 340, -1740);
	App->enemies->AddEnemy(ENEMY_TYPE::GREENPLANE, 100, -1700);
	App->enemies->AddEnemy(ENEMY_TYPE::GREENPLANE, 80, -1720);
	App->enemies->AddEnemy(ENEMY_TYPE::GREENPLANE, 60, -1740);
	App->enemies->AddEnemy(ENEMY_TYPE::GREENPLANE, 300, -1700);
	App->enemies->AddEnemy(ENEMY_TYPE::GREENPLANE, 320, -1720);
	App->enemies->AddEnemy(ENEMY_TYPE::GREENPLANE, 340, -1740);
	App->enemies->AddEnemy(ENEMY_TYPE::GREENPLANE, 100, -1700);
	App->enemies->AddEnemy(ENEMY_TYPE::GREENPLANE, 80, -1720);
	App->enemies->AddEnemy(ENEMY_TYPE::GREENPLANE, 60, -1740);

	App->enemies->AddEnemy(ENEMY_TYPE::GREENBOMBER, 50, -2400);
	App->enemies->AddEnemy(ENEMY_TYPE::GREENBOMBER, 350, -2600);

	App->enemies->AddEnemy(ENEMY_TYPE::REDLOOPPLANE, 150, -2010);
	App->enemies->AddEnemy(ENEMY_TYPE::REDLOOPPLANE, 150, -2080);
	App->enemies->AddEnemy(ENEMY_TYPE::REDLOOPPLANE, 150, -2050);
	App->enemies->AddEnemy(ENEMY_TYPE::REDLOOPPLANE, 250, -2010);
	App->enemies->AddEnemy(ENEMY_TYPE::REDLOOPPLANE, 250, -2080);
	App->enemies->AddEnemy(ENEMY_TYPE::REDLOOPPLANE, 250, -2050);

	App->enemies->AddEnemy(ENEMY_TYPE::GREENPLANE, 300, -2300);
	App->enemies->AddEnemy(ENEMY_TYPE::GREENPLANE, 320, -2320);
	App->enemies->AddEnemy(ENEMY_TYPE::GREENPLANE, 340, -2340);
	App->enemies->AddEnemy(ENEMY_TYPE::GREENPLANE, 100, -2300);
	App->enemies->AddEnemy(ENEMY_TYPE::GREENPLANE, 80, -2320);
	App->enemies->AddEnemy(ENEMY_TYPE::GREENPLANE, 60, -2340);
	App->enemies->AddEnemy(ENEMY_TYPE::GREENPLANE, 300, -2300);
	App->enemies->AddEnemy(ENEMY_TYPE::GREENPLANE, 320, -2320);
	App->enemies->AddEnemy(ENEMY_TYPE::GREENPLANE, 340, -2340);
	App->enemies->AddEnemy(ENEMY_TYPE::GREENPLANE, 100, -2300);
	App->enemies->AddEnemy(ENEMY_TYPE::GREENPLANE, 80, -2320);
	App->enemies->AddEnemy(ENEMY_TYPE::GREENPLANE, 60, -2340);

<<<<<<< Updated upstream
	App->enemies->AddEnemy(ENEMY_TYPE::GREENBOMBER, 50, -4600);
	App->enemies->AddEnemy(ENEMY_TYPE::GREENBOMBER, 350, -4400);

	App->enemies->AddEnemy(ENEMY_TYPE::REDLOOPPLANE, 150, -3010);
	App->enemies->AddEnemy(ENEMY_TYPE::REDLOOPPLANE, 150, -3080);
	App->enemies->AddEnemy(ENEMY_TYPE::REDLOOPPLANE, 150, -3050);
	App->enemies->AddEnemy(ENEMY_TYPE::REDLOOPPLANE, 250, -3010);
	App->enemies->AddEnemy(ENEMY_TYPE::REDLOOPPLANE, 250, -3080);
	App->enemies->AddEnemy(ENEMY_TYPE::REDLOOPPLANE, 250, -3050);
=======
	App->enemies->AddEnemy(ENEMY_TYPE::GREENBOMBER, 50, -4500);
	App->enemies->AddEnemy(ENEMY_TYPE::GREENBOMBER, 350, -4500);*/
>>>>>>> Stashed changes

	App->enemies->AddEnemy(ENEMY_TYPE::TURRETSHIP, 200, 0);

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	App->player->Enable();
	App->enemies->Enable();
	App->UI->Enable();

	



	return ret;
}

update_status SceneLevel1::Update()
{
	App->render->camera.y -= 1;
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
	App->UI->Disable();
	App->textures->Unload(bgTexture);
	App->textures->Unload(cloudTexture);

	return true;
}