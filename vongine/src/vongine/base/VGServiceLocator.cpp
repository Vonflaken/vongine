#include "VGServiceLocator.h"

NS_VG_BEGIN

ServiceLocator::ServiceLocator()
: _fileUtilsService(std::make_unique<FileUtils>()) 
, _resourcesCacheService(std::make_unique<ResourcesCache>())
, _renderContextService(std::make_unique<RenderContext>())
, _glProgramCacheService(std::make_unique<GLProgramCache>())
{}

void ServiceLocator::InitServices()
{
	_glProgramCacheService->Init();
}

NS_VG_END