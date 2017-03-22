#include "VGServiceLocator.h"
#include "platform/VGFileUtils.h"
#include "resources/VGResourcesCache.h"
#include "rendering/VGRenderContext.h"
#include "rendering/VGGLProgramCache.h"

NS_VG_BEGIN

ServiceLocator::ServiceLocator()
: _fileUtilsService(std::make_unique<FileUtils>()) 
, _resourcesCacheService(std::make_unique<ResourcesCache>())
, _renderContextService(std::make_unique<RenderContext>())
, _glProgramCacheService(std::make_unique<GLProgramCache>())
{}

NS_VG_END
