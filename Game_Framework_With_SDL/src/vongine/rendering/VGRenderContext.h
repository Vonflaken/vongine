#ifndef __VGRENDERCONTEXT_H__
#define __VGRENDERCONTEXT_H__

#include "VGMacros.h"
#include "base/VGTypes.h"

NS_VG_BEGIN

class __declspec(dllexport) RenderContext
{
public:
	void ActiveTextureUnit(const uint8 unitNumber);

private:
	/// Returns a value representing GL texture unit depends on unit number required
	/// Default return value is texture unit in position 0
	static const uint16 GetGLTextureUnitValue(const uint8 unitNumber);
};

NS_VG_END

#endif
