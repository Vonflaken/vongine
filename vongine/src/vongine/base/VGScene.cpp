#include "VGScene.h"
#include "rendering/VGCamera.h"
#include "base/VGCoreManager.h"
#include "base/VGUtils.h"
#include "rendering/VGGL.h"
#include "ui/VGUICanvas.h"
#include "ui/VGUIManager.h"

#include <algorithm>

NS_VG_BEGIN

using namespace utils;

/**
* Comparison function for sorting cameras based on camera order
* Asc order
*/
inline bool CameraOrderComp(const std::shared_ptr<Camera> first, const std::shared_ptr<Camera> last)
{
	return first->GetCameraOrder() < last->GetCameraOrder();
}

std::shared_ptr<Scene> Scene::Create()
{
	auto scene = std::make_shared<Scene>();
	if (scene->Init(glm::vec3(0.f, 0.f, 0.f)))
	{
		return scene;
	}
	return nullptr;
}

bool Scene::Init(const glm::vec3& position)
{
	bool isOK = Entity::Init(position);

	// Self set in order to be able to propagate root scene to children
	SetScene(std::static_pointer_cast<Scene>(shared_from_this()));

	const Size& screenSize = CoreManager::GetInstance().GetScreenSize();

	// Add default cam
	auto cam = Camera::CreateOrtho(0.f, (float)screenSize.width, 0.f, (float)screenSize.height, 0.1f, 100.f);
	cam->SetPosition(glm::vec3(0.f, 0.f, 10.f));
	AddCamera(cam);

	// Add default canvas
	auto canvas = ui::Canvas::Create(screenSize); // Create Canvas
	ui::UIManager::GetInstance().ReplaceRootWidget(canvas, this); // Set Canvas as root widget

	return isOK;
}

void Scene::Render()
{
	auto renderer = CoreManager::GetInstance().GetRenderer();

	// Sort cameras
	std::sort(_cameras.begin(), _cameras.end(), CameraOrderComp);
	// Render cameras
	for (auto it = _cameras.begin(); it != _cameras.end(); it++)
	{
		Camera::s_renderingCamera = *it;

		(*it)->Use();

		// Update entities in scene and add render commands to renderer
		Prepare(glm::mat4(), 0, 0);

		// Actual draw elements
		renderer->Draw();

		(*it)->Dispose();
	}

	// Swap render buffers
	SDL_GL_SwapWindow(CoreManager::GetInstance().GetWindow());

	Camera::s_renderingCamera = nullptr;
}

void Scene::AddCamera(std::shared_ptr<Camera> cam)
{
	_cameras.push_back(cam);
	// Also add to scene hierarchy
	AddChild(cam);
}

bool Scene::RemoveCamera(const std::shared_ptr<Camera>& cam)
{
	bool found = false;

	// Remove from cameras array
	for (auto it = _cameras.begin(); it != _cameras.end(); it++)
	{
		if (*it == cam)
		{
			_cameras.erase(it);
			found = true;
		}
	}

	// Remove from scene graph
	found &= DetachChildRecursive(cam);

	return found;
}

NS_VG_END
