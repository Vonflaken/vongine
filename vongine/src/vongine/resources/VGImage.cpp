#include "VGImage.h"
#include "base/VGCoreManager.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "ogl/glew.h"

NS_VG_BEGIN

InternalPixelFormat Image::GetFormatFromNumComponents(const uint32 numComponents)
{
	InternalPixelFormat format = InternalPixelFormat::UNKNOWN;
	switch (numComponents)
	{
	case 1:
	{
		format = InternalPixelFormat::G8;
		break;
	}
	case 2:
	{
		format = InternalPixelFormat::G8A8;
		break;
	}
	case 3:
	{
		format = InternalPixelFormat::R8G8B8;
		break;
	}
	case 4:
	{
		format = InternalPixelFormat::R8G8B8A8;
		break;
	}
	default:
		break;
	}

	return format;
}

int32 Image::GetGLValueFromInternal(const InternalPixelFormat format)
{
	int32 glVal = -1;
	switch (format)
	{
	case InternalPixelFormat::R8G8B8A8: 
		glVal = GL_RGBA;
		break;
	case InternalPixelFormat::R8G8B8: 
		glVal = GL_RGB;
		break;
	case InternalPixelFormat::G8A8: 
		glVal = GL_LUMINANCE_ALPHA;
		break;
	case InternalPixelFormat::G8: 
		glVal = GL_LUMINANCE;
		break;
	case InternalPixelFormat::A8:
		glVal = GL_ALPHA;
		break;
	}
	return glVal;
}

Image::Image()
: _pixels(nullptr, VG_Free_Deleter())
, _width(0)
, _height(0)
, _isInit(false)
, _numComponents(0)
, _format(InternalPixelFormat::UNKNOWN)
{}

bool Image::InitWithFile(const std::string& filename)
{
	if (_isInit || filename.empty()) // Early exist if already initialized or filename is invalid
		return false;

	std::string fullPathToImg = CoreManager::GetInstance().FileUtils()->GetFullPathOfResource(filename);

	// NOTE: Only in OpenGL
	// Flip the y-axis during image loading
	// OpenGL expects 0.0 coord on the y-axis to be on the bottom side
	// Images load with 0.0 coord on the y-axis on the top side
	stbi_set_flip_vertically_on_load(true);

	int32 width, height, numComponents;
	unsigned char* pixelData = stbi_load(fullPathToImg.c_str(), &width, &height, &numComponents, 0); // Load image file and store pixel data
	
	bool loadSuccess = pixelData != nullptr;

	if (loadSuccess)
	{
		_pixels.reset(pixelData); // _pixels now manages pointer to pixelData
		_width = width;
		_height = height;
		_numComponents = numComponents;
		_format = Image::GetFormatFromNumComponents(numComponents);

		_isInit = true;
	}

	return loadSuccess;
}

uint32 Image::GetBPP() const
{
	uint32 bpp = 0;
	if (_format == InternalPixelFormat::R8G8B8A8)
		bpp = 32;
	else if (_format == InternalPixelFormat::R8G8B8)
		bpp = 24;
	else if (_format == InternalPixelFormat::G8A8)
		bpp = 16;
	else if (_format == InternalPixelFormat::G8 || _format == InternalPixelFormat::A8)
		bpp = 8;

	return bpp;
}

NS_VG_END
