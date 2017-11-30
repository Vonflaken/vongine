#include "VGFMOD.h"
#include "base/VGLogger.h"

#include "fmod/fmod_errors.h"

NS_VG_BEGIN

void VG_FMOD_ErrCheck(const FMOD_RESULT res, const char* file, int line, const char* funcName)
{
	if (res != FMOD_OK)
	{
		VG_Log("FMOD error at %s(%d) in function '%s': %s", file, line, funcName, FMOD_ErrorString(res));
	}
}

NS_VG_END
