#pragma once
#include "Globals.h"

class Module
{
public:
	virtual bool Init();

	virtual bool Start();

	virtual UpdateResult PreUpdate();

	virtual UpdateResult Update();

	virtual UpdateResult PostUpdate();

	virtual bool CleanUp();
};