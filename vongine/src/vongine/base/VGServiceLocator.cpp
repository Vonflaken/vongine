#include "VGServiceLocator.h"

NS_VG_BEGIN

ServiceLocator::ServiceLocator()
: _resourcesCacheService(new ResourcesCache())
, _renderContextService(new RenderContext())
, _glProgramCacheService(new GLProgramCache())
, _eventMgrService(new EventManager())
, _inputMgrService(new InputManager())
{}

void ServiceLocator::InitServices()
{
	// Program Cache
	_glProgramCacheService->Init();
	// Event Mgr
	_eventMgrService->Init(_inputMgrService.get());
	// Input Mgr
	_inputMgrService->Init();
}

NS_VG_END
