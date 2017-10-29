#include "VGServiceLocator.h"

NS_VG_BEGIN

ServiceLocator::ServiceLocator()
: _resourcesCacheService(std::make_unique<ResourcesCache>())
, _renderContextService(std::make_unique<RenderContext>())
, _glProgramCacheService(std::make_unique<GLProgramCache>())
, _eventMgrService(std::make_unique<EventManager>())
, _inputMgrService(std::make_unique<InputManager>())
{}

void ServiceLocator::InitServices()
{
	_glProgramCacheService->Init();
}

NS_VG_END
