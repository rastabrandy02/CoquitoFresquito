#include "ModuleUI.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModulePlayer.h"
#include "ModuleRender.h"
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
