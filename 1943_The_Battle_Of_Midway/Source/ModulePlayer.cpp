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
#include "SceneLevel1.h"

#include "SDL/include/SDL_scancode.h"
#include <stdio.h>


ModulePlayer::ModulePlayer(bool startEnabled) : Module(startEnabled)
{
	// idle animation - just one sprite
	
	idleAnim.PushBack({ 175, 190, 35, 25 });

	leftAnim.PushBack({ 135, 190, 35, 25 });
	leftAnim.PushBack({ 95, 190, 35, 25 });
	leftAnim.loop = false;
	leftAnim.speed = 0.1f;

	rightAnim.PushBack({ 220, 190, 35, 25 });
	rightAnim.PushBack({ 265, 190, 35, 25 });
	rightAnim.loop = false;
	rightAnim.speed = 0.1f;
}

ModulePlayer::~ModulePlayer()
{

}

bool ModulePlayer::Start()
{
	LOG("Loading player textures");

	bool ret = true;

	playerDeadParticle = 0;
	texture = App->textures->Load("Assets/Art/SuperAce/yellow_plane.png");
	currentAnimation = &idleAnim;

	
	deathPlayerFx = App->audio->LoadFx("Assets/FX/death_player.wav");
	basicShotFx = App->audio->LoadFx("Assets/FX/basic_shot.wav");

	position.x = 195;
	position.y = 480;

	life = 9;
	destroyed = false;

	collider = App->collisions->AddCollider({ position.x, position.y, 35, 25 }, Collider::Type::PLAYER, this);

	char lookupTable1[] = { "01234567890" };
	char lookupTable2[] = { "! @,_./0123456789$;< ?abcdefghijklmnopqrstuvwxyz" };
	char lookupTable3[] = { "abcdefghijklmnopqrstuvwxyz" };
	char lookupTable4[] = { "1234567890.:,' (!?)+-*=" };
	scoreFont = App->fonts->Load("Assets/rtype_font.png", lookupTable2, 1);
	textFont = App->fonts->Load("Assets/font.png", lookupTable3, 1);
	
	

	return ret;
}

update_status ModulePlayer::Update()
{
	// Moving the player with the camera scroll
	App->player->position.y -= 1;

	autoCoolDown++;
	autoTimer++;
	if (!destroyed)
	{
		if (position.x >= 0)
		{
			if (App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT)
			{
				position.x -= speed;
				if (currentAnimation != &leftAnim)
				{
					leftAnim.Reset();
					currentAnimation = &leftAnim;
				}
			}
		}

		if (position.x <= 390)

		{
			if (App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT)
			{
				position.x += speed;
				if (currentAnimation != &rightAnim)
				{
					rightAnim.Reset();
					currentAnimation = &rightAnim;
				}
			}
		}
		if (App->input->keys[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT)
		{

			position.y += speed;

		}

		if (App->input->keys[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT)
		{


			position.y -= speed;


		}

		if (autoTimer >= 240) powerUpAuto = false;
		if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN)
		{
			App->particles->AddParticle(App->particles->basicShot, position.x + 10, position.y - 10, Collider::Type::PLAYER_SHOT);
			App->particles->AddParticle(App->particles->basicShot, position.x + 25, position.y - 10, Collider::Type::PLAYER_SHOT);
			App->audio->PlayFx(basicShotFx);
		}
		if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_REPEAT && powerUpAuto)
		{
			if (autoCoolDown >= 7)
			{
				App->particles->AddParticle(App->particles->basicShot, position.x + 10, position.y - 10, Collider::Type::PLAYER_SHOT);
				App->particles->AddParticle(App->particles->basicShot, position.x + 25, position.y - 10, Collider::Type::PLAYER_SHOT);
				App->audio->PlayFx(basicShotFx);
				autoCoolDown = 0;
			}

		}

		// If no up/down movement detected, set the current animation back to idle
		if (App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_IDLE
			&& App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_IDLE)
			currentAnimation = &idleAnim;

		collider->SetPos(position.x, position.y);

		currentAnimation->Update();


		if (App->input->keys[SDL_SCANCODE_F3] == KEY_STATE::KEY_DOWN)
		{
			godMode = !godMode;
		}
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

		}
		
	}
	
	// Draw UI (score) --------------------------------------
	sprintf(scoreText, "%7d", score);
	
	// TODO 3: Blit the text of the score in at the bottom of the screen
	App->fonts->BlitText(40, 40, scoreFont, scoreText);
	App->fonts->BlitText(10, 10, textFont, "player");
	
	

	

	return update_status::UPDATE_CONTINUE;
}

void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{
	if (c1 == collider && destroyed == false && (c2->type == Collider::Type::ENEMY || c2->type == Collider::Type::ENEMY_SHOT))
	{
		life--;
		App->particles->AddParticle(App->particles->enemyExplosion, position.x, position.y, Collider::Type::NONE, 0);
	}

	if (c1->type == Collider::Type::ENEMY && c2->type == Collider::Type::PLAYER_SHOT)
	{
		score += 100;
	}
	if (c1 == collider && c2->type == Collider::Type::PU_AUTO)
	{
		powerUpAuto = true;
		autoTimer = 0;
	}
	if (c1 == collider && c2->type == Collider::Type::WIN)
	{
		App->fade->FadeToBlack((Module*)App->sceneLevel_1, (Module*)App->sceneEnd, 60);
		position.x = 0;
		position.y = 0;
		
	}
}

bool ModulePlayer::CleanUp()
{
	App->textures->Unload(texture);

	return true;
}
