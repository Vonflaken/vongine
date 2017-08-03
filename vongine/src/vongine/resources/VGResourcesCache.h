#ifndef __VGRESOURCESCACHE_H__
#define __VGRESOURCESCACHE_H__

#include "VGMacros.h"
#include "rendering/VGTexture2D.h"

#include <unordered_map>
#include <memory>

NS_VG_BEGIN

class DLLAPI ResourcesCache
{
public:
	/**
	* Create new Texture2D and add it to the cache.
	* If already exists the texture with provided filename It will return the cached one.
	* Caller is not responsible of the ownership of the pointer.
	*/
	Texture2D* AddTexture(const std::string& filename);

private:
	std::unordered_map<std::string, std::unique_ptr<Texture2D>> _textures2D;
};

NS_VG_END

#endif // __VGRESOURCESCACHE_H__

