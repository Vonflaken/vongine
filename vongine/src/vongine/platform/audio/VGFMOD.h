#ifndef __VGFMOD_H__
#define __VGFMOD_H__

#include "VGMacros.h"

#include "fmod/fmod.hpp"

NS_VG_BEGIN

/*************************************** Custom DELETERS for FMOD objects */

class DLLAPI VG_FMOD_Deleter
{
public:
	inline void operator()(FMOD::Sound* s) const { s->release();  }
	inline void operator()(FMOD::System* sys) const { sys->close(); sys->release(); }
};
/**************************************************************************/

void VG_FMOD_ErrCheck(const FMOD_RESULT res, const char* file, int line, const char* funcName);
#define VG_FMOD_ERRCHECK(res) VG_FMOD_ErrCheck(res, __FILE__, __LINE__, __FUNCTION__)

NS_VG_END

#endif // __VGFMOD_H__
