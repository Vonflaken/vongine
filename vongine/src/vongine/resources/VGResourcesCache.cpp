#include "VGResourcesCache.h"
#include "resources/VGImage.h"
#include "resources/VGBitmapFont.h"

NS_VG_BEGIN

Texture2D* ResourcesCache::AddTexture(const std::string& filename)
{
	// Check if texture already exists
	auto textureFound = _textures2D.find(filename);
	if (textureFound != _textures2D.end())
	{
		return textureFound->second.get();
	}

	// Create a new texture2D from filename
	// Load image file
	Image image;
	image.InitWithFile(filename);

	if (image.IsInit()) // Load was successful
	{
		// Create texture object
		auto texture = std::make_unique<Texture2D>();
		texture->InitWithImage(&image);

		if (texture->IsInit()) // Generation was successful
		{
			// Add texture to hash table
			auto result = _textures2D.insert({ filename, std::move(texture) });
			// Return newly inserted texture
			return result.first->second.get();
		}
	}

	return nullptr;
}

Font* ResourcesCache::AddFont(const std::string& filename)
{
	// Check if font already exists
	auto fontFound = _fonts.find(filename);
	if (fontFound != _fonts.end())
	{
		return fontFound->second.get();
	}

	auto font = std::unique_ptr<Font>(nullptr);
	bool isOK = false;

	std::string fileExt = str_extract_ext(filename);
	if (fileExt == "ttf")
	{
		// TrueType font file
	}
	else
	{
		// Bitmap font
		font.reset(new BitmapFont());
		isOK = font->InitWithFilename(filename);
	}

	// Check font is correctly constructed
	if (isOK)
	{
		// Add font to hash table
		auto result = _fonts.insert({ filename, std::move(font) });
		// Return newly inserted font
		return result.first->second.get();
	}

	return nullptr;
}

NS_VG_END
