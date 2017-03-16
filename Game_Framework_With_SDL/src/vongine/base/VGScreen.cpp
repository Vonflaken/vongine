#include "VGScreen.h"

NS_VG_BEGIN

Screen::Screen()
: _width(0)
, _height(0)
, _window(nullptr, VG_SDL_Deleter())
{
}

void Screen::CreateSDLWindow(const uint32 width, const uint32 height)
{
	_width = width;
	_height = height;

	_window = VG_SDL_CreateWindow("My Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
}

NS_VG_END
