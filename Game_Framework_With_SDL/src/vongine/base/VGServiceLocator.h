#ifndef __VGSERVICELOCATOR_H__
#define __VGSERVICELOCATOR_H__

#include "VGMacros.h"
#include <memory>

NS_VG_BEGIN

class FileUtils;
class ResourcesCache;
class RenderContext;
class GLProgramCache;

class __declspec(dllexport) ServiceLocator
{
public:
	ServiceLocator();

	/// Returns pointer to FileUtils instance
	const FileUtils* FileUtilsService() const { return _fileUtilsService.get(); }
	/// Returns pointer to ResourcesCache instance
	const ResourcesCache* ResourcesCacheService() const { return _resourcesCacheService.get(); }
	/// Returns pointer to RenderContext instance
	const RenderContext* RenderContextService() const { return _renderContextService.get(); }
	/// Returns pointer to GLProgramCache instance
	const GLProgramCache* GLProgramCacheService() const { return _glProgramCacheService.get(); }

private:
	std::unique_ptr<FileUtils> _fileUtilsService;
	std::unique_ptr<ResourcesCache> _resourcesCacheService;
	std::unique_ptr<RenderContext> _renderContextService;
	std::unique_ptr<GLProgramCache> _glProgramCacheService;
};

NS_VG_END

#endif // __VGSERVICELOCATOR_H__

