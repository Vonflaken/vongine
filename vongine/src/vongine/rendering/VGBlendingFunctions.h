#ifndef __VGBLENDINGFUNCTIONS_H__
#define __VGBLENDINGFUNCTIONS_H__

#include "VGMacros.h"
#include "base/VGTypes.h"

NS_VG_BEGIN

enum class BlendFactor
{
	NONE, 
	ZERO, 
	ONE, 
	SRC_COLOR, 
	ONE_MINUS_SRC_COLOR, 
	DST_COLOR, 
	ONE_MINUS_DST_COLOR, 
	SRC_ALPHA, 
	ONE_MINUS_SRC_ALPHA, 
	DST_ALPHA, 
	ONE_MINUS_DST_ALPHA
};

namespace BlendingFunctionsHelpers
{
	/**
	* @return GL value matching the internal type or -1 if doesn't find a match
	*/
	int32 GetGLValueFromInternal(const BlendFactor internalVal);
}

NS_VG_END

#endif // __VGBLENDINGFUNCTIONS_H__
