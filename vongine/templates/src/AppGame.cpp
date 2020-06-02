#include "AppGame.h"

#include "vongine.h"

using namespace vongine;


/********************************************************
* Dummy Scene definition.
*/

class FirstScene : public Scene
{
public:
	static std::shared_ptr<FirstScene> Create()
	{
		auto scene = std::make_shared<FirstScene>();
		if (scene->Init(glm::vec3(0.f, 0.f, 0.f)))
		{
			return scene;
		}
		return nullptr;
	}

	bool Init(const glm::vec3& position)
	{
		if (Scene::Init(position))
		{
		
			return true;
		}
		return false;
};


/**********************************************************************
* AppGame class implementation.
*/

bool AppGame::StartGame()
{
	// Config app.
	AppConfigurationObject cfg = { 0 };
	cfg.engineLoadedCallback = VG_MEMBER_CALLBACK_0(AppGame::OnEngineLoadedCallback, this);
	cfg.windowHeight = 1240;
	cfg.windowWidth = 720;
	cfg.flags |= VG_CFG_LOCKWINDOWRESIZE;

	// Init engine.
	return Application::GetInstance().Run(cfg);
}

void AppGame::OnEngineLoadedCallback()
{
	// Create first scene.
	auto scene = FirstScene::Create();
	// Set 'scene' as current running Scene.
	CoreManager::GetInstance().ReplaceScene(scene);
}
