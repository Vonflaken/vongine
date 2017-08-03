#include "VGApplication.h"
#include "base/VGLogger.h"
#include "base/VGScreen.h"
#include "base/VGCoreManager.h"
#include "rendering/VGRenderContext.h"

#include "VGSDL.h"
#include "ogl/glew.h"

NS_VG_BEGIN

Application& Application::GetInstance()
{
	static Application* instance = new Application();
	return *instance;
}

bool Application::Init()
{
	// Initialize SDL's Video subsystem
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		VGLOG_ERROR("Failed to init SDL");
		return false;
	}

	SetGLAttributes();	

	CoreManager& coreMgr = CoreManager::GetInstance();
	// Creates window and GL ctx
	if (!coreMgr.InitWithScreenSize(1024, 720))
	{
		VGLOG_ERROR("Failed to initialize CoreManager");
		return false;
	}

	// Enable VSync
	if (SDL_GL_SetSwapInterval(1) != 0)
		VGLOG_INFO("VSync is not supported in this system.");

	// Init GLEW
#ifndef __APPLE__
	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if (err != GLEW_OK)
	{
		VGLOG_ERROR("Failed to init GLEW: '%s'", glewGetErrorString(err));
		return false;
	}
#endif // __APPLE__

	coreMgr.InitServices();

	// Set default clear color
	Color3i col = { 150, 150, 150 };
	coreMgr.RenderContext()->SetClearColor(col);

	return true;
}

bool Application::Run()
{
	if (!Init())
		return false;

	// Call function where client initializes stuff which concerns to his game
	if (_engineLoadedCallback)
	{
		_engineLoadedCallback();
	}

	CoreManager& coreMgr = CoreManager::GetInstance(); // Cache instance

	// Game loop
	while (true)
	{
		// TODO: Add frame time
		// Start frame time clock

		bool shouldQuitApp;
		coreMgr.ProcessFrame(&shouldQuitApp);

		// Calculate frame time

		// Set frame time

		if (shouldQuitApp)
			return false;

		SDL_Delay(1);
	};

	Cleanup();

	return true;
}

void Application::SetGLAttributes()
{
	// Set our OpenGL version.
	// SDL_GL_CONTEXT_CORE gives us only the newer version, deprecated functions are disabled
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	// 3.2 is part of the modern versions of OpenGL, but most video cards whould be able to run it
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

	// Turn on double buffering with a 24bit Z buffer.
	// You may need to change this to 16 or 32 for your system
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
}

void Application::Cleanup()
{
	SDL_Quit();
}

NS_VG_END
