#ifndef __VGSDL_H__
#define __VGSDL_H__

#include "sdl/SDL.h"
#include "VGMacros.h"
#include <memory>
#include "VGTypes.h"

NS_VG_BEGIN

struct __declspec(dllexport) VG_SDL_Deleter
{
public:
	inline void operator()(SDL_Window* window) const { SDL_DestroyWindow(window); }
};

inline std::unique_ptr<SDL_Window, VG_SDL_Deleter> VG_SDL_CreateWindow(const char* title, const uint32 posx, const uint32 posy, const uint32 width, const uint32 height, uint32 flags)
{
	return std::unique_ptr<SDL_Window, VG_SDL_Deleter>(
		SDL_CreateWindow(title, posx, posy, width, height, flags),
		VG_SDL_Deleter());
}

NS_VG_END

#endif // __VGSDL_H__
