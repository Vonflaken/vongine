#include "VGServiceLocator.h"

NS_VG_BEGIN

ServiceLocator::ServiceLocator()
: _fileUtilsService(std::make_unique<FileUtils>()) 
, _resourcesCacheService(std::make_unique<ResourcesCache>())
, _renderContextService(std::make_unique<RenderContext>())
{}

NS_VG_END
