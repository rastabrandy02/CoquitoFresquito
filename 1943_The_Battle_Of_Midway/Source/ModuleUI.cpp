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
	char lookupTable1[] = { "0123456789 " };
	char lookupTable2[] = { "! @,_./0123456789$;< ?abcdefghijklmnopqrstuvwxyz" };
	char lookupTable3[] = { "0123456789abcdefghijklmnopqrstuvwxyz " };
	char lookupTable4[] = { "1234567890.:,' (!?)+-*=" };

	scoreFont = App->fonts->Load("Assets/score_font_1.png", lookupTable1, 1);
	scoreFontPowerUps = App->fonts->Load("Assets/score_fontPowerUps.png", lookupTable1, 1);
	scoreFontHiScore = App->fonts->Load("Assets/score_font.png", lookupTable1, 1);
	textFont = App->fonts->Load("Assets/textFont.png", lookupTable3, 1);
	textFontPowerUps = App->fonts->Load("Assets/textFontPowerUps.png", lookupTable3, 1);
	textFontHiScore = App->fonts->Load("Assets/textFont_1.png", lookupTable3, 1);
	testFont = App->fonts->Load("Assets/rtype_font.png", lookupTable2, 1);

	healtBar1 = App->textures->Load("Assets/Lifebars/life_bar_1.png");
	healtBar2 = App->textures->Load("Assets/Lifebars/life_bar_2.png");
	healtBar3 = App->textures->Load("Assets/Lifebars/life_bar_3.png");
	healtBar4 = App->textures->Load("Assets/Lifebars/life_bar_4.png");
	healtBar5 = App->textures->Load("Assets/Lifebars/life_bar_5.png");
	healtBar6 = App->textures->Load("Assets/Lifebars/life_bar_6.png");
	healtBar7 = App->textures->Load("Assets/Lifebars/life_bar_7.png");
	healtBar8 = App->textures->Load("Assets/Lifebars/life_bar_8.png");
	healtBar9 = App->textures->Load("Assets/Lifebars/life_bar_9.png");
	timersAuto = 240;
	

	return ret;
}

update_status ModuleUI::PostUpdate()
{
	switch (App->player->life)
	{
	case 9:
		App->render->Blit(healtBar1, 0, 458, NULL, 0.0f, false);
		break;
	case 8:
		App->render->Blit(healtBar2, 0, 458, NULL, 0.0f, false);
		break;
	case 7:
		App->render->Blit(healtBar3, 0, 458, NULL, 0.0f, false);
		break;
	case 6:
		App->render->Blit(healtBar4, 0, 458, NULL, 0.0f, false);
		break;
	case 5:
		App->render->Blit(healtBar5, 0, 458, NULL, 0.0f, false);
		break;
	case 4:
		App->render->Blit(healtBar6, 0, 458, NULL, 0.0f, false);
		break;
	case 3:
		App->render->Blit(healtBar7, 0, 458, NULL, 0.0f, false);
	case 2:
		App->render->Blit(healtBar8, 0, 458, NULL, 0.0f, false);
		break;
	case 1:
		App->render->Blit(healtBar9, 0, 458, NULL, 0.0f, false);
		break;
	default:
		break;
	}
	
	counter++;
	if ((counter / 60) % 2 == 0)
	{
		App->fonts->BlitText(250, 458, textFont,"insert coin");
	}
	if (autopw)
	{
		App->fonts->BlitText(0, 488, textFontPowerUps, "auto");
	}
	else if (way)
	{
		timersAuto--;
		timersWay = timersAuto / 60;
		//sprintf_s(powerupText, "%2d", timersWay);
		sprintf_s(powerupText, "%2d", App->player->threeWayBullets);

		App->fonts->BlitText(0, 488, textFontPowerUps, "way");
		App->fonts->BlitText(50, 488, scoreFontPowerUps, powerupText);
	}
	else
	{
		timersAuto = 240;
	}
	if (score >= hiScore)
	{
		hiScore = score;
	}
	sprintf_s(scoreText, "%7d", score);

	sprintf_s(hiScoreText, "%7d", hiScore);
	App->fonts->BlitText(25, 30, scoreFont, scoreText);
	App->fonts->BlitText(10, 9, textFont, "1player");
	App->fonts->BlitText(300, 9, textFont, "2player");
	App->fonts->BlitText(360, 30, scoreFont, "0");
	App->fonts->BlitText(150, 9, textFontHiScore, "hiscore");
	App->fonts->BlitText(165, 30, scoreFontHiScore, hiScoreText);
	//App->fonts->BlitText(300, 10, testFont, fpsText);
	if (App->player->intro)
	{
		
		App->fonts->BlitText(130, 240, textFont, "offensive target");
		App->fonts->BlitText(180, 260, textFontHiScore, "tone");
		App->fonts->BlitText(130, 280, textFont, "may you fight bravely");
		
	}
	if (App->player->end)
	{
		App->fonts->BlitText(100, 240, textFont, "visual contact with");
		App->fonts->BlitText(90, 260, textFont, "surface foreces confirmed");
		App->fonts->BlitText(130, 280, textFont, "comencing attack");
	}
	return update_status::UPDATE_CONTINUE;
}

bool ModuleUI::CleanUp()
{
	bool ret = true;
	App->textures->Unload(healtBar1);
	App->textures->Unload(healtBar2);
	App->textures->Unload(healtBar3);
	App->textures->Unload(healtBar4);
	App->textures->Unload(healtBar5);
	App->textures->Unload(healtBar6);
	App->textures->Unload(healtBar7);
	App->textures->Unload(healtBar8);
	App->textures->Unload(healtBar9);

	App->fonts->UnLoad(scoreFont);
	App->fonts->UnLoad(textFont);
	App->fonts->UnLoad(scoreFontPowerUps);
	App->fonts->UnLoad(scoreFontHiScore);
	App->fonts->UnLoad(textFontPowerUps);
	App->fonts->UnLoad(textFontHiScore);
	App->fonts->UnLoad(testFont);
	


	return ret;
}

void ModuleUI::DebugDrawGamepadInfo()
{
	GamePad& pad = App->input->pads[0];

	sprintf_s(scoreText, 150, "pad 0 %s, press 1/2/3 for rumble", (pad.enabled) ? "plugged" : "not detected");
	App->fonts->BlitText(5, 200, testFont, scoreText);

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
	App->fonts->BlitText(5, 210, testFont, scoreText);

	sprintf_s(scoreText, 150, "dpad %s %s %s %s",
		(pad.up) ? "up" : "",
		(pad.down) ? "down" : "",
		(pad.left) ? "left" : "",
		(pad.right) ? "right" : ""
	);
	App->fonts->BlitText(5, 220, testFont, scoreText);

	sprintf_s(scoreText, 150, "left trigger  %0.2f", pad.l2);
	App->fonts->BlitText(5, 230, testFont, scoreText);
	sprintf_s(scoreText, 150, "right trigger %0.2f", pad.r2);
	App->fonts->BlitText(5, 240, testFont, scoreText);

	sprintf_s(scoreText, 150, "left thumb    %.2fx, %0.2fy", pad.left_x, pad.left_y);
	App->fonts->BlitText(5, 250, testFont, scoreText);

	sprintf_s(scoreText, 150, "   deadzone   %0.2f", pad.left_dz);
	App->fonts->BlitText(5, 260, testFont, scoreText);

	sprintf_s(scoreText, 150, "right thumb   %.2fx, %0.2fy", pad.right_x, pad.right_y);
	App->fonts->BlitText(5, 270, testFont, scoreText);

	sprintf_s(scoreText, 150, "   deadzone   %0.2f", pad.right_dz);
	App->fonts->BlitText(5, 280, testFont, scoreText);
}
