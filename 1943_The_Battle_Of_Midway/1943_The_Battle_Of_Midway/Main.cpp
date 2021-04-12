#include "SDL/include/SDL.h"

#include "Application.h"

enum class MainState
{
	MAIN_CREATION = 1,
	MAIN_START,
	MAIN_UPDATE,
	MAIN_FINISH,
	MAIN_EXIT
};

Application *App = nullptr;

int main(int argc, char* argv[])
{
	MainState state = MainState ::MAIN_CREATION;
	int main_result = EXIT_FAILURE;

	while (state != MainState::MAIN_EXIT)
	{
		switch (state)
		{
		case MainState::MAIN_CREATION:
			break;
		case MainState::MAIN_START:
			break;
		case MainState::MAIN_UPDATE:
			break;
		case MainState::MAIN_FINISH:
			break;
		case MainState::MAIN_EXIT:
			break;
		default:
			break;
		}
	}
}