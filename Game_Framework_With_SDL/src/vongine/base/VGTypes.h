#ifndef __VGTYPES_H__
#define __VGTYPES_H__

typedef signed char int8;
typedef signed short int16;
typedef signed int int32;
typedef signed long int64;
typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;
typedef unsigned long uint64;


enum class InternalImageFormat
{
	R8G8B8A8,		// RGBA 8-bits per component
	R8G8B8,			// RGB 8-bits per component
	G8A8,			// Gray + Alpha 8-bits per component
	G8				// Gray 8-bits per component
};


///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// Wrapper types for OpenGL defines

#include "ogl/glew.h"

enum TextureFilter
{
	POINT = GL_NEAREST, 
	BILINEAR = GL_LINEAR
};

enum TextureWrap
{
	REPEAT_X, 
	REPEAT_Y, 
	// Consumable by OpenGL
	REPEAT = GL_REPEAT, 
	CLAMP = GL_CLAMP
};

#endif // __VGTYPES_H__
