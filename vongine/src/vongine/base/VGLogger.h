#ifndef __VGLOGGER_H__
#define __VGLOGGER_H__

#include "VGMacros.h"
#include "base/VGTypes.h"

#include <stdarg.h>

NS_VG_BEGIN

void VG_Log(const char* format, ...);

void VG_LogBase(const char* format, va_list args);
void VG_LogWindows(const char* format, va_list args);

#if defined(VG_DEBUG) && VG_DEBUG == 1
#define VGLOG_INFO(format, ...) VG_Log(format"\n", ##__VA_ARGS__)
#define VGLOG_ERROR(format, ...) VG_Log("Vongine error at %s(%i) in function '%s': " format "\n", __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__)
#define VGLOG_DEBUG(format, ...) VG_Log("Vongine debug at %s(%i) in function '%s': " format "\n", __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__)
// Conditional logs
#define VGLOG_ERROR_IF(cond, format, ...) if ((cond)) VG_Log("VG_ERROR %s(%i) in function '%s': " format "\n", __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__)
#else
#define VGLOG_INFO(format, ...) do {} while (0)
#define VGLOG_ERROR(format, ...) do {} while (0)
#define VGLOG_DEBUG(format, ...) do {} while (0)
// Conditional logs
#define VGLOG_ERROR_IF(cond, format, ...) do {} while (0)
#endif // VG_DEBUG

NS_VG_END

#endif // __VGLOGGER_H__
