

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
		{
			cout << "---Application Creation---\n" << endl;
			App = new Application();
			state = MainState::MAIN_START;
		} 
		break;

		case MainState::MAIN_START:
		{
			cout << "---Application Start---" << endl;
			if (App->Init() == false)
			{
				cout << "ERROR---> Application Init" << endl;
			}
			else
			{
				state = MainState::MAIN_UPDATE;
			}
		}
			break;
		case MainState::MAIN_UPDATE:
		{
			UpdateResult updateState = App->Update();
			if (updateState == UpdateResult::UPDATE_ERROR)
			{
				cout << "ERROR---> Application Update" << endl;
				updateState = UpdateResult::UPDATE_STOP;
			}
			else if (updateState == UpdateResult::UPDATE_STOP)
			{
				state = MainState::MAIN_FINISH;
			}
		}
			break;
		case MainState::MAIN_FINISH:
		{
			cout << "---Application Finish---" << endl;
			if (App->CleanUp() == true)
			{
				main_result = EXIT_SUCCESS;
			}
			else
			{
				cout << "ERROR---> Application Exit" << endl;
			}
			state = MainState::MAIN_EXIT;
		}
			break;
		case MainState::MAIN_EXIT:
			break;
		default:
		{
			state = MainState:: MAIN_FINISH;
		}
			break;
		}
	}
	cout << "---Application Exit Succesful---" << endl;
	delete App;
	return main_result;
}