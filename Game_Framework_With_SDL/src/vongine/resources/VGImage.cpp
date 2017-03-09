#include "VGImage.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

NS_VG_BEGIN

InternalImageFormat Image::GetFormatFromNumComponents(const uint32 numComponents)
{
	InternalImageFormat format = InternalImageFormat::UNKNOWN;
	switch (numComponents)
	{
	case 1:
	{
		format = InternalImageFormat::G8;
		break;
	}
	case 2:
	{
		format = InternalImageFormat::G8A8;
		break;
	}
	case 3:
	{
		format = InternalImageFormat::R8G8B8;
		break;
	}
	case 4:
	{
		format = InternalImageFormat::R8G8B8A8;
		break;
	}
	default:
		break;
	}

	return format;
}

Image::Image()
: _pixels(nullptr, VG_Free_Deleter())
, _width(0)
, _height(0)
, _isInit(false)
, _numComponents(0)
, _format(InternalImageFormat::UNKNOWN)
{}

void Image::InitWithFile(const char* filename)
{
	if (_isInit)
		return;

	int32 width, height, numComponents = 0;

	unsigned char* pixelData = stbi_load(filename, &width, &height, &numComponents, 0); // Load image file and store pixel data
	
	if (!pixelData) // Something went wrong at load the file
		return;

	_pixels.reset(&pixelData); // _pixels now manages pointer to pixelData
	_width = width;
	_height = height;
	_numComponents = numComponents;
	_format = Image::GetFormatFromNumComponents(numComponents);

	_isInit = true;
}

NS_VG_END
