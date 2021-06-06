#include "ModulePlayer.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleFadeToBlack.h"
#include "ModuleFonts.h"
#include "ModuleEnemies.h"
#include "ModuleUI.h"
#include "SceneLevel1.h"
#include "SceneLevel2.h"
#include <stdio.h>

#include "SDL/include/SDL_scancode.h"



ModulePlayer::ModulePlayer(bool startEnabled) : Module(startEnabled)
{
	
	
	idleAnim.PushBack({ 93, 28, 25, 16 });
	idleAnim.PushBack({ 93, 48, 25, 16 });
	idleAnim.loop = true;
	idleAnim.speed = 0.1f;

	leftAnim.PushBack({ 62, 29, 22, 16 });
	leftAnim.PushBack({ 62, 48, 22, 16 });
	leftAnim.PushBack({ 30, 29, 19, 16 });
	leftAnim.PushBack({ 30, 48, 19, 16 });
	leftAnim.loop = false;
	leftAnim.speed = 0.1f;

	rightAnim.PushBack({ 127, 29, 22, 16 });
	rightAnim.PushBack({ 127, 48, 22, 16 });
	rightAnim.PushBack({ 163, 29, 18, 16 });
	rightAnim.PushBack({ 163, 48, 18, 16 });
	rightAnim.loop = false;
	rightAnim.speed = 0.1f;

	downAnim.PushBack({ 24, 144, 46, 19 });
	downAnim.PushBack({ 75, 144, 46, 19 });
	downAnim.PushBack({ 126, 144, 46, 19 });
	downAnim.PushBack({ 175, 144, 46, 19 });
	downAnim.loop = false;
	downAnim.speed = 0.05f;

	introAnim.PushBack({ 271, 121, 7, 7 });
	introAnim.PushBack({ 135, 121, 10, 6 });
	introAnim.PushBack({ 236, 120, 8, 9 });
	introAnim.PushBack({ 99, 120, 13, 9 });
	introAnim.PushBack({ 165, 117, 14, 13 });
	introAnim.PushBack({ 200, 119, 12, 10 });
	introAnim.PushBack({ 25, 75, 25, 13 });
	introAnim.PushBack({ 25, 93, 25, 14 });
	introAnim.PushBack({ 58, 77, 27, 11 });
	introAnim.PushBack({ 58, 93, 27, 13 });
	introAnim.PushBack({ 92, 77, 28, 7 });
	introAnim.PushBack({ 125, 77, 30, 10 });
	introAnim.PushBack({ 159, 79, 30, 15 });
	introAnim.PushBack({ 193, 74, 30, 16 });
	introAnim.PushBack({ 228, 76, 28, 11 });
	introAnim.PushBack({ 273, 79, 26, 6 });
	introAnim.PushBack({ 228, 94, 26, 13 });
	introAnim.PushBack({ 228, 94, 26, 13 });
	introAnim.loop = false;
	introAnim.speed = 0.1f;

	currentAnimation = &idleAnim;

}

ModulePlayer::~ModulePlayer()
{

}

bool ModulePlayer::Start()
{
	LOG("Loading player textures");

	bool ret = true;

	playerDeadParticle = 0;
	texture = App->textures->Load("Assets/superAce.png");
	
	App->UI->score = 0;
	
	deathPlayerFx = App->audio->LoadFx("Assets/FX/death_player.wav");
	basicShotFx = App->audio->LoadFx("Assets/FX/basic_shot.wav");

	position.x = 195;
	position.y = 465;

	life = 9;
	destroyed = false;

	collider = App->collisions->AddCollider({ position.x, position.y, 35, 25 }, Collider::Type::PLAYER, this);

	powerUpAuto = false;
	powerUpThreeWay = false;
	endTimer = 0;
	end = false;
	intro = false;

	return ret;
}

update_status ModulePlayer::Update()
{
	if (App->sceneLevel_1->IsEnabled() && App->sceneLevel_1->introTimer <= 240)
	{
		if (currentAnimation = &introAnim)
		{
			introAnim.Reset();
			currentAnimation = &introAnim;
		}
		intro = true;
	}
	GamePad& pad = App->input->pads[0];
	// Moving the player with the camera scroll
	if (playerMove)
		App->player->position.y -= 1;
	

	// Debug key for gamepad rumble testing purposes
	if (App->input->keys[SDL_SCANCODE_1] == KEY_STATE::KEY_DOWN)
	{
		App->input->ShakeController(0, 12, 0.33f);
	}

	// Debug key for gamepad rumble testing purposes
	if (App->input->keys[SDL_SCANCODE_2] == KEY_STATE::KEY_DOWN)
	{
		App->input->ShakeController(0, 36, 0.66f);
	}

	// Debug key for gamepad rumble testing purposes
	if (App->input->keys[SDL_SCANCODE_3] == KEY_STATE::KEY_DOWN)
	{
		App->input->ShakeController(0, 60, 1.0f);
	}

	autoCoolDown++;
	autoTimer++;
	
	
	if (!destroyed && !intro && !end)
	{
		if (position.x >= 0)
		{
			if (App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT || pad.left_x < 0.0f)
			{
				position.x -= speed;
				if (currentAnimation != &leftAnim)
				{
					leftAnim.Reset();
					currentAnimation = &leftAnim;
					printf("left\n");
				}
			}
		}

		if (position.x <= 365)

		{
			if (App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT || pad.left_x > 0.0f)
			{
				position.x += speed;
				if (currentAnimation != &rightAnim)
				{
					rightAnim.Reset();
					currentAnimation = &rightAnim;
					printf("right\n");
				}
			}
		}
		if (App->input->keys[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT || pad.left_y > 0.0f)
		{
			if (position.y < App->render->camera.y + 465)
			{
				position.y += speed;
			}
			

		}

		if (App->input->keys[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT || pad.left_y < 0.0f)
		{

			if (position.y > App->render->camera.y + 50)
			{
				position.y -= speed;
			}
			


		}

		if (autoTimer >= 240) powerUpAuto = false;
		
		if (threeWayBullets <= 0) powerUpThreeWay = false;
		if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN || pad.a == true)
		{
			if (!powerUpThreeWay && shotCountDown == 0)
			{
				App->particles->AddParticle(App->particles->basicShot, position.x + 8, position.y - 10, Collider::Type::PLAYER_SHOT);
				App->particles->AddParticle(App->particles->basicShot, position.x + 23, position.y - 10, Collider::Type::PLAYER_SHOT);
				App->audio->PlayFx(basicShotFx);
				App->input->ShakeController(0, 60, 0.33f);
				shotCountDown = shotMaxCountDown;
				App->UI->way = false;
				App->UI->autopw = false;
			}
			
		}
		if ((App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN || pad.a == true) && powerUpThreeWay && shotCountDown == 0)
		{
			
			
				App->particles->AddParticle(App->particles->basicShot, position.x + 8, position.y - 10, Collider::Type::PLAYER_SHOT);
				App->particles->AddParticle(App->particles->basicShot, position.x + 23, position.y - 10, Collider::Type::PLAYER_SHOT);
				App->particles->AddParticle(App->particles->anglePosShot, position.x + 23, position.y - 10, Collider::Type::PLAYER_SHOT);
				App->particles->AddParticle(App->particles->angleNegShot, position.x + 8, position.y - 10, Collider::Type::PLAYER_SHOT);
				App->audio->PlayFx(basicShotFx);
				App->input->ShakeController(0, 60, 0.33f);
				shotCountDown = shotMaxCountDown;
				App->UI->way = true;
				threeWayBullets--;
			
		}
		if ((App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_REPEAT || pad.a == true) && powerUpAuto && !powerUpThreeWay)
		{
			if (autoCoolDown >= 7)
			{
				App->particles->AddParticle(App->particles->basicShot, position.x + 8, position.y - 10, Collider::Type::PLAYER_SHOT);
				App->particles->AddParticle(App->particles->basicShot, position.x + 23, position.y - 10, Collider::Type::PLAYER_SHOT);
				App->audio->PlayFx(basicShotFx);
				App->input->ShakeController(0, 60, 0.33f);
				autoCoolDown = 0;
				App->UI->autopw = true;
			}
		}
		if ((App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_REPEAT || pad.a == true) && powerUpAuto && powerUpThreeWay)
		{
			if (autoCoolDown >= 7)
			{
				App->particles->AddParticle(App->particles->basicShot, position.x + 8, position.y - 10, Collider::Type::PLAYER_SHOT);
				App->particles->AddParticle(App->particles->basicShot, position.x + 23, position.y - 10, Collider::Type::PLAYER_SHOT);
				App->particles->AddParticle(App->particles->anglePosShot, position.x + 23, position.y - 10, Collider::Type::PLAYER_SHOT);
				App->particles->AddParticle(App->particles->angleNegShot, position.x + 8, position.y - 10, Collider::Type::PLAYER_SHOT);
				App->audio->PlayFx(basicShotFx);
				App->input->ShakeController(0, 1, 0.33f);
				autoCoolDown = 0;
				App->UI->way = true;
				threeWayBullets--;
			}
		}

		// If no up/down movement detected, set the current animation back to idle
		if (!intro)
		{
			if (pad.enabled)
			{
				if (pad.left_x == 0.0f && pad.left_y == 0.0f) currentAnimation = &idleAnim;
			}
			if (App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_IDLE && App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_IDLE)
				currentAnimation = &idleAnim;
		}
		collider->SetPos(position.x, position.y);

		currentAnimation->Update();

		if (App->input->keys[SDL_SCANCODE_F4] == KEY_DOWN)
			debugGamepadInfo = !debugGamepadInfo;

		if (App->input->keys[SDL_SCANCODE_F3] == KEY_STATE::KEY_DOWN)
		{
			godMode = !godMode;
		}
	}
	if (shotCountDown > 0) --shotCountDown;
	if (end) currentAnimation = &downAnim;
	if (position.y <= -5200)
	{
		end = true;
		endTimer++;

		App->fade->FadeToBlack((Module*)App->sceneLevel_1, (Module*)App->sceneLevel_2, 60);
	}
	return update_status::UPDATE_CONTINUE;
}

update_status ModulePlayer::PostUpdate()
{
	
	if (!destroyed)
	{
		SDL_Rect rect = currentAnimation->GetCurrentFrame();
		App->render->Blit(texture, position.x, position.y, &rect);
	}
	
	if(life <= 0)
	{
		playerDeadParticle++;
		if (playerDeadParticle == 1)
		{
			destroyed = true;
			App->particles->AddParticle(App->particles->playerDeath, position.x, position.y, Collider::Type::NONE, 0);
			App->audio->PlayFx(deathPlayerFx);
			playerDeadParticle = 2;
			App->input->ShakeController(0, 60, 1.0f);
		}
		
	}
	if (debugGamepadInfo == true) App->UI->DebugDrawGamepadInfo();

	return update_status::UPDATE_CONTINUE;
}

void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{
	if (c1 == collider && destroyed == false && (c2->type == Collider::Type::ENEMY || c2->type == Collider::Type::ENEMY_SHOT))
	{
		
		App->particles->AddParticle(App->particles->enemyExplosion, position.x, position.y, Collider::Type::NONE, 0);
		if (godMode == false) life--;
		App->input->ShakeController(0, 60, 0.66f);
	}

	if (c1 == collider && c2->type == Collider::Type::ENEMY)
	{
		AddScore();
	}
	if (c1 == collider && c2->type == Collider::Type::PU_AUTO)
	{
		powerUpAuto = true;
		autoTimer = 0;
	}
	if (c1 == collider && c2->type == Collider::Type::PU_THREEWAY)
	{
		powerUpThreeWay = true;
		threeWayBullets = 50;
		
	}
	if (c1 == collider && c2->type == Collider::Type::PU_POW)
	{
		if(life < 9)
		life += 1;
	}
	if (c1 == collider && c2->type == Collider::Type::WIN)
	{
		App->fade->FadeToBlack((Module*)App->sceneLevel_1, (Module*)App->sceneEnd, 60);
		position.x = 0;
		position.y = 0;
		
	}if (c1 == collider && c2->type == Collider::Type::LVL2)
	{
		end = true;
		endTimer++;
		
		App->fade->FadeToBlack((Module*)App->sceneLevel_1, (Module*)App->sceneLevel_2, 60);
		position.x = 0;
		position.y = 0;
		LOG("Collider");
		
	}
}

bool ModulePlayer::CleanUp()
{
	App->textures->Unload(texture);

	return true;
}

void ModulePlayer::AddScore()
{
	App->UI->score += 100;
}
