#pragma once
#include "Globals.h"


#define NUM_MODULES 1
class Module;

class Application
{
 public:
	 Application() {};
	 ~Application() {};
	 bool Init();
	 UpdateResult Update();
	 bool CleanUp();

	 Module* modules[NUM_MODULES];

	 

};
extern Application* App;