#ifndef __VGRESOURCESCACHE_H__
#define __VGRESOURCESCACHE_H__

#include "VGMacros.h"
#include "rendering/VGTexture2D.h"
#include "resources/VGFont.h"
#include "resources/VGAudioSound.h"

#include "platform/audio/VGFMOD.h"

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

	/**
	* Create new Font and add it to the cache.
	* For bitmap fonts: filename provided must be from font configuration text file.
	* For TrueType fonts: filename provided must be from font "ttf" extension file.
	* If already exists the font with provided filename It will return the cached one.
	* Caller is not responsible of the ownership of the pointer.
	*/
	Font* AddFont(const std::string& filename);

	/**
	* Create new AudioSound and add it to the cache.
	* If already exists the font with provided filename It will return the cached one.
	* Caller is not responsible of the ownership of the pointer.
	*/
	AudioSound* AddAudioSound(const std::string& filename, const FMOD_MODE modeFlags, const bool isStream);

private:
	std::unordered_map<std::string, std::unique_ptr<Texture2D>> _textures2D;
	std::unordered_map<std::string, std::unique_ptr<Font>> _fonts;
	std::unordered_map<std::string, std::unique_ptr<AudioSound>> _audioSounds;
};

NS_VG_END

#endif // __VGRESOURCESCACHE_H__

