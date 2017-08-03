#include "VGCoreManager.h"
#include "base/VGScene.h"
#include "VGScreen.h"

NS_VG_BEGIN

CoreManager& CoreManager::GetInstance()
{
	static CoreManager* instance = new CoreManager();
	return *instance;
}

CoreManager::CoreManager()
: _serviceLocator(std::make_unique<ServiceLocator>())
, _activeScene(nullptr) 
, _nextScene(nullptr)
, _screen(nullptr)
, _renderer(nullptr)
{}

CoreManager::~CoreManager()
{}

bool CoreManager::InitWithScreenSize(const uint32 width, const uint32 height)
{
	if (!CreateScreenAndGLContext(width, height))
		return false;

	return true;
}

void CoreManager::InitServices()
{
	_serviceLocator->InitServices();
	_renderer.reset(new Renderer());

	auto renderCtx = RenderContext();
	auto screenSize = GetScreenSize();
	// Set viewport
	renderCtx->SetViewport(Rect(0.f, 0.f, screenSize.width, screenSize.height));
	// Set default winding order
	renderCtx->SetWindingOrder(GLWinding::CCW);
	// Set default culling face
	renderCtx->SetCullingFace(GLCullingFace::BACK);
}

bool CoreManager::CreateScreenAndGLContext(const uint32 width, const uint32 height)
{
	if (!_screen)
	{
		_screen.reset(new Screen()); // Create screen
		if (auto window = _screen->CreateWindow(width, height)) // Create app window
		{
			auto ctx = RenderContext()->CreateGLContext(window); // Create GL context
			if (SDL_GL_MakeCurrent(window, ctx) != 0)
			{
				VGLOG_ERROR("SDL_GL_MakeCurrent failed: '%s'", SDL_GetError());
			}
		}
		else
		{
			_screen.release();
			return false;
		}
	}

	return true;
}

void CoreManager::ReplaceScene(const std::shared_ptr<Scene> newScene)
{
	_nextScene = newScene;
}

void CoreManager::ProcessFrame(bool* shouldExitApp)
{
	*shouldExitApp = false;

	// Poll input events
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT)
			*shouldExitApp = true;
	}

	if (_activeScene)
		_activeScene->Render();

	// Switch scenes
	if (_nextScene)
	{
		_activeScene = _nextScene;
		_nextScene = nullptr;
	}
}

SDL_Window* CoreManager::GetWindow()
{ 
	return _screen->GetWindow(); 
}

const Size& CoreManager::GetScreenSize() const 
{ 
	return _screen->GetSize(); 
}

NS_VG_END