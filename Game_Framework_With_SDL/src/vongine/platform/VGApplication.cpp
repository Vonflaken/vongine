#include "VGApplication.h"
#include "sdl/SDL.h"
#include "VGLogger.h"
#include "VGScreen.h"

NS_VG_BEGIN

Application& Application::GetInstance()
{
	static Application* instance = new Application();
	return *instance;
}

bool Application::Run()
{
	// Initialize SDL's Video subsystem
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		VGLOG("Failed to init SDL\n");
	}

	// Create our window centered at 512x512 resolution
	auto screen = std::unique_ptr<Screen>(new Screen());
	screen->CreateSDLWindow(512, 512);

	// Call function where client initializes stuff which concerns to his game
	if (_engineLoadedCallback)
	{
		_engineLoadedCallback();
	}

	SDL_Delay(2000);

	SDL_Quit();

	return false;
}

NS_VG_END
