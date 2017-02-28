#ifndef __VGResourcesCache_H__
#define __VGResourcesCache_H__

#include "VGMacros.h"
#include <unordered_map>
#include "rendering/VGTexture2D.h"
#include <memory>

NS_VG_BEGIN

class __declspec(dllexport) ResourcesCache
{
public:
	/// Create new Texture2D and add it to the cache.
	/// If already exists the texture with provided filename It will return the cached one.
	/// Caller is not responsible of the ownership of the pointer.
	const Texture2D* AddTexture(const std::string& filename);

private:
	std::unordered_map<const std::string, const std::unique_ptr<Texture2D>> _textures2D;
};

NS_VG_END

#endif // __VGResourcesCache_H__

