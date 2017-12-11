#ifndef __VGSDL_H__
#define __VGSDL_H__

#include "VGMacros.h"
#include "base/VGTypes.h"
#include "base/VGLogger.h"

#include "sdl/SDL.h"

#include <memory>

NS_VG_BEGIN

/*************************************** VG_SDL_Deleter */

struct DLLAPI VG_SDL_Deleter
{
public:
	/// Delete SDL_Window
	inline void operator()(SDL_Window* window) const { SDL_DestroyWindow(window); }
	/// Delete SDL_RWops
	inline void operator()(SDL_RWops* rwops) const { SDL_RWclose(rwops); }
	/// Delete SDL_GLContext
	inline void operator()(SDL_GLContext glctx) const { SDL_GL_DeleteContext(glctx); }
};

typedef void(*VG_SDL_Free)(void*);
/*************************************** End VG_SDL_Deleter */


/*************************************** Factory functions */
inline std::unique_ptr<SDL_Window, VG_SDL_Deleter> VG_SDL_CreateWindow(const char* title, const uint32 posx, const uint32 posy, const uint32 width, const uint32 height, uint32 flags)
{
	return std::unique_ptr<SDL_Window, VG_SDL_Deleter>(
		SDL_CreateWindow(title, posx, posy, width, height, flags),
		VG_SDL_Deleter());
}

inline std::unique_ptr<SDL_RWops, VG_SDL_Deleter> VG_SDL_CreateFileRWops(const char* file, const char* mode)
{
	return std::unique_ptr<SDL_RWops, VG_SDL_Deleter>(
		SDL_RWFromFile(file, mode),
		VG_SDL_Deleter());
}

inline std::unique_ptr<void, VG_SDL_Deleter> VG_SDL_CreateGLContext(SDL_Window* window)
{
	return std::unique_ptr<void, VG_SDL_Deleter>(
		SDL_GL_CreateContext(window),
		VG_SDL_Deleter());
}
/*************************************** End factory functions */


/**
* Convert C true/false to specific SDL type (SDL_bool).
*/
#define VG_SDL_BOOL(comparation) (comparation) ? SDL_TRUE : SDL_FALSE

NS_VG_END

#endif // __VGSDL_H__
