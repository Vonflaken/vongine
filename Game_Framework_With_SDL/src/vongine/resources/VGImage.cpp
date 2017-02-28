#include "VGImage.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

NS_VG_BEGIN

Image::Image()
: _pixels(nullptr, VG_Free_Deleter())
, _width(0)
, _height(0)
, _isInit(false)
, _numComponents(0)
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

	_isInit = true;
}

NS_VG_END
