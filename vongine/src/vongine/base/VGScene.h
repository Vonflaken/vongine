#ifndef __VGSCENE_H__
#define __VGSCENE_H__

#include "VGMacros.h"
#include "VGEntity.h"
#include "rendering/VGCamera.h"

#include <vector>

NS_VG_BEGIN

class DLLAPI Scene : public Entity
{
public:
	/**
	* Creates a scene with an ortho camera by default
	*/
	static std::shared_ptr<Scene> Create();

	bool Init(const glm::vec3& position) override;

	void Render();

	void AddCamera(std::shared_ptr<Camera> cam);
	/**
	* @return bool Whereas or not camera was removed successfuly from scene graph and cameras array.
	*/
	bool RemoveCamera(const std::shared_ptr<Camera>& cam);

private:
	std::vector<std::shared_ptr<Camera>> _cameras;
};

NS_VG_END

#endif // __VGSCENE_H__
