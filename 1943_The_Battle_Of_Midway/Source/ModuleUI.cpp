#include "ModuleUI.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModulePlayer.h"
#include "ModuleRender.h"
#include "ModuleInput.h"

#include <stdio.h>
ModuleUI::ModuleUI(bool isEnabled) : Module(isEnabled)
{
}

ModuleUI::~ModuleUI()
{
}

bool ModuleUI::Start()
{
	bool ret = true;
	char lookupTable1[] = { "01234567890" };
	char lookupTable2[] = { "! @,_./0123456789$;< ?abcdefghijklmnopqrstuvwxyz" };
	char lookupTable3[] = { "abcdefghijklmnopqrstuvwxyz" };
	char lookupTable4[] = { "1234567890.:,' (!?)+-*=" };
	scoreFont = App->fonts->Load("Assets/rtype_font.png", lookupTable2, 1);
	textFont = App->fonts->Load("Assets/font.png", lookupTable3, 1);

	healtBar1 = App->textures->Load("Assets/Lifebars/life_bar_1.png");
	healtBar2 = App->textures->Load("Assets/Lifebars/life_bar_2.png");
	healtBar3 = App->textures->Load("Assets/Lifebars/life_bar_3.png");
	healtBar4 = App->textures->Load("Assets/Lifebars/life_bar_4.png");
	healtBar5 = App->textures->Load("Assets/Lifebars/life_bar_5.png");
	healtBar6 = App->textures->Load("Assets/Lifebars/life_bar_6.png");
	healtBar7 = App->textures->Load("Assets/Lifebars/life_bar_7.png");
	healtBar8 = App->textures->Load("Assets/Lifebars/life_bar_8.png");
	healtBar9 = App->textures->Load("Assets/Lifebars/life_bar_9.png");


	return ret;
}

update_status ModuleUI::PostUpdate()
{
	switch (App->player->life)
	{
	case 9:
		App->render->Blit(healtBar1, 0, 488, NULL, 0.0f, false);
		break;
	case 8:
		App->render->Blit(healtBar2, 0, 488, NULL, 0.0f, false);
		break;
	case 7:
		App->render->Blit(healtBar3, 0, 488, NULL, 0.0f, false);
		break;
	case 6:
		App->render->Blit(healtBar4, 0, 488, NULL, 0.0f, false);
		break;
	case 5:
		App->render->Blit(healtBar5, 0, 488, NULL, 0.0f, false);
		break;
	case 4:
		App->render->Blit(healtBar6, 0, 488, NULL, 0.0f, false);
		break;
	case 3:
		App->render->Blit(healtBar7, 0, 488, NULL, 0.0f, false);
	case 2:
		App->render->Blit(healtBar8, 0, 488, NULL, 0.0f, false);
		break;
	case 1:
		App->render->Blit(healtBar9, 0, 488, NULL, 0.0f, false);
		break;
	default:
		break;
	}

	sprintf_s(scoreText, "%7d", score);
	sprintf_s(fpsText, "fps %.2f", fps);
	App->fonts->BlitText(40, 40, scoreFont, scoreText);
	App->fonts->BlitText(10, 10, textFont, "player");
	App->fonts->BlitText(300, 10, scoreFont, fpsText);
	return update_status::UPDATE_CONTINUE;
}

void ModuleUI::DebugDrawGamepadInfo()
{
	GamePad& pad = App->input->pads[0];

	sprintf_s(scoreText, 150, "pad 0 %s, press 1/2/3 for rumble", (pad.enabled) ? "plugged" : "not detected");
	App->fonts->BlitText(5, 10, scoreFont, scoreText);

	sprintf_s(scoreText, 150, "buttons %s %s %s %s %s %s %s %s %s %s %s",
		(pad.a) ? "a" : "",
		(pad.b) ? "b" : "",
		(pad.x) ? "x" : "",
		(pad.y) ? "y" : "",
		(pad.start) ? "start" : "",
		(pad.back) ? "back" : "",
		(pad.guide) ? "guide" : "",
		(pad.l1) ? "lb" : "",
		(pad.r1) ? "rb" : "",
		(pad.l3) ? "l3" : "",
		(pad.r3) ? "r3" : ""
	);
	App->fonts->BlitText(5, 20, scoreFont, scoreText);

	sprintf_s(scoreText, 150, "dpad %s %s %s %s",
		(pad.up) ? "up" : "",
		(pad.down) ? "down" : "",
		(pad.left) ? "left" : "",
		(pad.right) ? "right" : ""
	);
	App->fonts->BlitText(5, 30, scoreFont, scoreText);

	sprintf_s(scoreText, 150, "left trigger  %0.2f", pad.l2);
	App->fonts->BlitText(5, 40, scoreFont, scoreText);
	sprintf_s(scoreText, 150, "right trigger %0.2f", pad.r2);
	App->fonts->BlitText(5, 50, scoreFont, scoreText);

	sprintf_s(scoreText, 150, "left thumb    %.2fx, %0.2fy", pad.left_x, pad.left_y);
	App->fonts->BlitText(5, 60, scoreFont, scoreText);

	sprintf_s(scoreText, 150, "   deadzone   %0.2f", pad.left_dz);
	App->fonts->BlitText(5, 70, scoreFont, scoreText);

	sprintf_s(scoreText, 150, "right thumb   %.2fx, %0.2fy", pad.right_x, pad.right_y);
	App->fonts->BlitText(5, 80, scoreFont, scoreText);

	sprintf_s(scoreText, 150, "   deadzone   %0.2f", pad.right_dz);
	App->fonts->BlitText(5, 90, scoreFont, scoreText);
}