#ifndef __VGSERVICELOCATOR_H__
#define __VGSERVICELOCATOR_H__

#include "VGMacros.h"
#include "resources/VGResourcesCache.h"
#include "rendering/VGRenderContext.h"
#include "rendering/VGGLProgramCache.h"
#include "base/VGEventManager.h"
#include "base/VGInputManager.h"

#include <memory>

NS_VG_BEGIN

class DLLAPI ServiceLocator
{
public:
	ServiceLocator();

	void InitServices();

	/**
	* @return Returns pointer to ResourcesCache.
	*/
	ResourcesCache* const ResourcesCacheService() const { return _resourcesCacheService.get(); }
	/**
	* @return Returns pointer to RenderContext.
	*/
	RenderContext* const RenderContextService() const { return _renderContextService.get(); }
	/**
	* @return Returns pointer to GLProgramCache.
	*/
	GLProgramCache* const GLProgramCacheService() const { return _glProgramCacheService.get(); }
	/**
	* @return Returns pointer to EventManager.
	*/
	EventManager* const EventMgrService() const { return _eventMgrService.get(); }
	/**
	* @return Returns pointer to InputManager. 
	*/
	InputManager* const InputMgrService() const { return _inputMgrService.get(); }

private:
	std::unique_ptr<ResourcesCache> _resourcesCacheService;
	std::unique_ptr<RenderContext> _renderContextService;
	std::unique_ptr<GLProgramCache> _glProgramCacheService;
	std::unique_ptr<EventManager> _eventMgrService;
	std::unique_ptr<InputManager> _inputMgrService;
};

NS_VG_END

#endif // __VGSERVICELOCATOR_H__

