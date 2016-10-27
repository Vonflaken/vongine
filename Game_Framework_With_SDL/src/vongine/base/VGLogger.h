#ifndef __VGLOGGER_H__
#define __VGLOGGER_H__

#include "VGMacros.h"

#ifdef WINDOWS_PLATFORM
#include <windows.h>
#endif

NS_VG_BEGIN

void VgLogBasic(const char* format, va_list args);
void VgLogWindows(const char* format, va_list args);
void VgLog(const char* format, ...);

NS_VG_END

#if defined(VG_DEBUG) && VG_DEBUG == 1
#define VGLOG(format, ...) NS_VG::VgLog(format, __VA_ARGS__)
#else
#define VGLOG(format, ...) do {} while (0)
#endif // VG_DEBUG

#endif // __VGLOGGER_H__
