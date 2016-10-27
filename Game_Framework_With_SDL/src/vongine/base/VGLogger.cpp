#include "VGLogger.h"
#include <stdio.h>
#include "VGTypes.h"

NS_VG_BEGIN

void VgLogBasic(const char* format, va_list args)
{
#ifndef WINDOWS_PLATFORM
	vprintf(format, args);
#endif
}

void VgLogWindows(const char* format, va_list args)
{
#if WINDOWS_PLATFORM
	char buffer[256];
	vsnprintf(buffer, 256, format, args);
	OutputDebugString(buffer);
#endif
}

void VgLog(const char* format, ...)
{
	va_list args;
	va_start(args, format);

	// Add a new line character to the end of every message
	uint32 len = strlen(format);
	char* buffer = static_cast<char*>(malloc(len + 2)); // +2 because of new line char and end of str char
	memcpy(buffer, format, len);
	*(buffer + len) = '\n'; // Set new line char
	*(buffer + len + 1) = '\0'; // Set end of str char

	VgLogWindows(buffer, args);
	VgLogBasic(buffer, args);

	free(buffer);
	va_end(args);
}

NS_VG_END
