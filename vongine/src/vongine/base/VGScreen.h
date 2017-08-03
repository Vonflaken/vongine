#ifndef __VGSCREEN_H__
#define __VGSCREEN_H__

#include "VGMacros.h"
#include "VGTypes.h"
#include "VGSDL.h"

#include <memory>

NS_VG_BEGIN

class DLLAPI Screen
{
public:
	Screen();

	/**
	  @return Newly generated window
	*/
	SDL_Window* CreateWindow(const uint32 width, const uint32 height);

	const Size& GetSize() const { return _size; }
	SDL_Window* GetWindow() { return _window.get(); }

private:
	Size _size;
	std::unique_ptr<SDL_Window, VG_SDL_Deleter> _window;
};

NS_VG_END

#endif // __VGSCREEN_H__
