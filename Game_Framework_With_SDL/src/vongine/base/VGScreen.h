#ifndef __VGSCREEN_H__
#define __VGSCREEN_H__

#include "VGMacros.h"
#include "VGTypes.h"
#include "sdl/SDL.h"
#include <memory>
#include "VGSDL.h"

NS_VG_BEGIN

class __declspec(dllexport) Screen
{
public:
	Screen();

	void CreateSDLWindow(const uint32 width, const uint32 height);

private:
	uint32 _width, _height;
	std::unique_ptr<SDL_Window, VG_SDL_Deleter> _window;
};

NS_VG_END

#endif // __VGSCREEN_H__
