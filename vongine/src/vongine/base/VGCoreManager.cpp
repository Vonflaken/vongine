#include "VGCoreManager.h"
#include "base/VGScene.h"
#include "VGScreen.h"
#include "2d/VGSprite.h"

NS_VG_BEGIN

#ifdef VG_DEBUG
#define DRAW_COLLISION_SHAPE
#endif // VG_DEBUG

CoreManager& CoreManager::GetInstance()
{
	static CoreManager* instance = new CoreManager();
	return *instance;
}

CoreManager::CoreManager()
: _serviceLocator(std::make_unique<ServiceLocator>())
, _runningScene(nullptr) 
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

void CoreManager::ProcessFrame(const float deltaTime)
{
	_deltaTime = deltaTime;
	
	{ // Check simple collisions between Sprites
		if (Sprite::s_spritesWithCollision.size() > 1)
		{ // At least 2 Sprites in collection
			std::vector<std::vector<std::weak_ptr<Sprite>>::iterator> removeLater; // Iterators pointing to elements that should be removed from sprite collision collection
			for (auto sprIt = Sprite::s_spritesWithCollision.begin();
				sprIt != Sprite::s_spritesWithCollision.end() - 1;
				sprIt++)
			{ // Check one Sprite against all the others
				auto wptrSpr = *sprIt;
				if (wptrSpr.expired())
				{ // Sprite doesn't exist anymore, remove it
					removeLater.push_back(sprIt);
					continue;
				}
				if (!wptrSpr.lock()->IsActive()) // Go next if this is not active
					continue;
#ifdef DRAW_COLLISION_SHAPE
				// Draw collision shape
				wptrSpr.lock()->GetCollision()->DrawDebugShape();
#endif
				for (auto otherSprIt = sprIt + 1;
					otherSprIt != Sprite::s_spritesWithCollision.end();
					otherSprIt++)
				{
					auto wptrOtherSptr = *otherSprIt;
					if (!wptrOtherSptr.expired() && wptrOtherSptr.lock()->IsActive()) // Don't check against inactive Sprites
					{ // Do actual check
						wptrSpr.lock()->CheckCollision(wptrOtherSptr.lock().get());
					}
				}
			}
			// Check edge case, did last member expire?
			auto lastIt = Sprite::s_spritesWithCollision.end() - 1;
			if ((*lastIt).expired())
			{
				removeLater.push_back(lastIt);
			}
			else
			{
#ifdef DRAW_COLLISION_SHAPE
				// Draw collision shape of last Sprite in collection
				(*lastIt).lock()->GetCollision()->DrawDebugShape();
#endif
			}
			// Remove expired Sprites from collision collection
			for (uint32 i = 0; i < removeLater.size(); i++)
			{
				Sprite::s_spritesWithCollision.erase(removeLater[i]);
			}
		}
	}

	EventMgr()->ProcessEvents();

	if (_runningScene)
		_runningScene->Render();

	// Switch scenes
	if (_nextScene)
	{
		_runningScene = _nextScene;
		_nextScene = nullptr;

		_runningScene->OnStartRecursive();
		_runningScene->OnAttach();
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
