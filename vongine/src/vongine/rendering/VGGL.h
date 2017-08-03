#ifndef __VGGL_H__
#define __VGGL_H__

#include "VGMacros.h"

#include "ogl/glew.h"

#include <string>

NS_VG_BEGIN

/**
* TODO: Put here all GL constants.
* Set GL constants to internal vars.
* Engine and user use them for internals and GL calls without hassles.
*/

namespace GL
{
	/**
	* @return Description of next error in queue related to graphic library, If no errors return empty string
	*/
	std::string GetErrorDesc();
	/**
	* Macro version for avoiding compute function in production
	*/
#if defined(VG_DEBUG) && VG_DEBUG == 1
#define VG_GL_GETERRORDESC() GL::GetErrorDesc()
#else 
#define VG_GL_GETERRORDESC() ""
#endif // VG_DEBUG
}

NS_VG_END

#endif // __VGGL_H__
