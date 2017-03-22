#ifndef __VGRESOURCESCACHE_H__
#define __VGRESOURCESCACHE_H__

#include "VGMacros.h"
#include <unordered_map>
#include <memory>

NS_VG_BEGIN

class Texure2D;

class __declspec(dllexport) ResourcesCache
{
public:
	/// Create new Texture2D and add it to the cache.
	/// If already exists the texture with provided filename It will return the cached one.
	/// Caller is not responsible of the ownership of the pointer.
	const Texture2D* AddTexture(const char* filename);

private:
	std::unordered_map<std::string, std::unique_ptr<Texture2D>> _textures2D;
};

NS_VG_END

#endif // __VGRESOURCESCACHE_H__

