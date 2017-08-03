#include "VGLogger.h"

#include <stdio.h>

#ifdef WINDOWS_PLATFORM
#include <windows.h>
#endif

NS_VG_BEGIN

void VG_Log(const char* format...)
{
	va_list args;
	va_start(args, format);

	VG_LogBase(format, args);
	VG_LogWindows(format, args);

	va_end(args);
}

void VG_LogBase(const char* format, va_list args)
{
#ifndef WINDOWS_PLATFORM
	vprintf(format, args);
#endif
}

void VG_LogWindows(const char* format, va_list args)
{
#if WINDOWS_PLATFORM
	char buffer[1028];
	vsnprintf(buffer, 1028, format, args);
	OutputDebugString(buffer);
#endif
}

NS_VG_END
