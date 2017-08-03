#ifndef __VGDEPTHTESTFUNCTIONS_H__
#define __VGDEPTHTESTFUNCTIONS_H__

#include "VGMacros.h"
#include "base/VGTypes.h"

NS_VG_BEGIN

enum class DepthTestFunction
{
	ALWAYS, 
	NEVER, 
	LESS, 
	EQUAL, 
	LEQUAL, 
	GREATER, 
	NOTEQUAL, 
	GEQUAL
};

namespace DepthTestFunctionsHelpers
{
	/**
	* @return GL value matching the internal type or -1 if doesn't find a match
	*/
	int32 GetGLValueFromInternal(const DepthTestFunction internalVal);
}

NS_VG_END

#endif // __VGDEPTHTESTFUNCTIONS_H__
