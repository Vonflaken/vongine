#ifndef __VGSCENE_H__
#define __VGSCENE_H__

#include "VGMacros.h"
#include "VGEntity.h"
#include <vector>
#include "rendering/VGCamera.h"

NS_VG_BEGIN

class __declspec(dllexport) Scene : public Entity
{
public:
	static std::shared_ptr<Scene> Create();

	void Render();

private:
	std::vector<std::shared_ptr<Camera>> _cameras;
};

NS_VG_END

#endif // __VGSCENE_H__
