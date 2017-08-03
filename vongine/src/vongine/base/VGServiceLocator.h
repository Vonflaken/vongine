#ifndef __VGSERVICELOCATOR_H__
#define __VGSERVICELOCATOR_H__

#include "VGMacros.h"
#include "platform/VGFileUtils.h"
#include "resources/VGResourcesCache.h"
#include "rendering/VGRenderContext.h"
#include "rendering/VGGLProgramCache.h"

#include <memory>

NS_VG_BEGIN

class DLLAPI ServiceLocator
{
public:
	ServiceLocator();

	void InitServices();

	/// Returns pointer to FileUtils instance
	const FileUtils* FileUtilsService() const { return _fileUtilsService.get(); }
	/// Returns pointer to ResourcesCache instance
	ResourcesCache* const ResourcesCacheService() const { return _resourcesCacheService.get(); }
	/// Returns pointer to RenderContext instance
	RenderContext* const RenderContextService() const { return _renderContextService.get(); }
	/// Returns pointer to GLProgramCache instance
	GLProgramCache* const GLProgramCacheService() const { return _glProgramCacheService.get(); }

private:
	std::unique_ptr<FileUtils> _fileUtilsService;
	std::unique_ptr<ResourcesCache> _resourcesCacheService;
	std::unique_ptr<RenderContext> _renderContextService;
	std::unique_ptr<GLProgramCache> _glProgramCacheService;
};

NS_VG_END

#endif // __VGSERVICELOCATOR_H__

