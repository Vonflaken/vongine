#include "VGScene.h"

NS_VG_BEGIN

void Scene::Render()
{
	for (auto it = _cameras.begin(); it != _cameras.end(); it++)
	{
		Camera::s_renderingCamera = *it;

		(*it)->Use();

		Prepare(glm::mat4(), 0);

		(*it)->Dispose();
	}

	Camera::s_renderingCamera = nullptr;
}

NS_VG_END
