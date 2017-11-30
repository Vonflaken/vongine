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
	* @return ResourcesCache Returns pointer to ResourcesCache.
	*/
	ResourcesCache* ResourcesCacheService() const { return _resourcesCacheService.get(); }
	/**
	* @return RenderContext Returns pointer to RenderContext.
	*/
	RenderContext* RenderContextService() const { return _renderContextService.get(); }
	/**
	* @return GLProgramCache Returns pointer to GLProgramCache.
	*/
	GLProgramCache* GLProgramCacheService() const { return _glProgramCacheService.get(); }
	/**
	* @return EventManager Returns pointer to EventManager.
	*/
	EventManager* EventMgrService() const { return _eventMgrService.get(); }
	/**
	* @return InputManager Returns pointer to InputManager. 
	*/
	InputManager* InputMgrService() const { return _inputMgrService.get(); }

private:
	std::unique_ptr<ResourcesCache> _resourcesCacheService;
	std::unique_ptr<RenderContext> _renderContextService;
	std::unique_ptr<GLProgramCache> _glProgramCacheService;
	std::unique_ptr<EventManager> _eventMgrService;
	std::unique_ptr<InputManager> _inputMgrService;
};

NS_VG_END

#endif // __VGSERVICELOCATOR_H__

