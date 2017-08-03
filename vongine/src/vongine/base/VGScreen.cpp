#include "VGScreen.h"

NS_VG_BEGIN

Screen::Screen()
: _window(nullptr, VG_SDL_Deleter())
{}

SDL_Window* Screen::CreateWindow(const uint32 width, const uint32 height)
{
	_size.width = width;
	_size.height = height;

	auto window = VG_SDL_CreateWindow(
		"Vongine game", 
		SDL_WINDOWPOS_CENTERED, 
		SDL_WINDOWPOS_CENTERED, 
		width, 
		height, 
		SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

	if (window)
	{
		// Set new window
		_window = std::move(window);
	}
	else
	{
		VGLOG_ERROR("Unable to create SDL_window: '%s'", SDL_GetError());

		return nullptr;
	}

	return _window.get();
}

NS_VG_END
