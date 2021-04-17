#include "Application.h"

#include "Module.h"
#include "ModuleWindow.h"

Application::Application()
{
	modules[0] = new ModuleWindow();
}

Application::~Application()
{
	for (int i = 0; i < NUM_MODULES; i++)
	{
		delete modules[i];
		modules[i] = nullptr;
	}
}

bool Application::Init()
{
	bool ret = true;
	for (int i = 0; i < NUM_MODULES && ret; i++)
	{
		ret = modules[i]->Init();
	}
	return ret;
}

UpdateResult Application::Update()
{
	UpdateResult ret = UpdateResult::UPDATE_CONTINUE;

	for (int i = 0; i < NUM_MODULES && ret == UpdateResult::UPDATE_CONTINUE; i++)
	{
		ret = modules[i]->PreUpdate();
	}
	for (int i = 0; i < NUM_MODULES && ret == UpdateResult::UPDATE_CONTINUE; i++)
	{
		ret = modules[i]->Update();
	}
	for (int i = 0; i < NUM_MODULES && ret == UpdateResult::UPDATE_CONTINUE; i++)
	{
		ret = modules[i]->PostUpdate();
	}

	return ret;
}

bool Application::CleanUp()
{
	bool ret = true;
	for (int i = NUM_MODULES - 1; i >= 0 && ret; i--)
	{
		modules[i]->CleanUp();
	}
	return ret;
}