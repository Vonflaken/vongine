#ifndef __VGLogger_H__
#define __VGLogger_H__

#if defined(VG_DEBUG) && VG_DEBUG == 1
#define VGLOG(...) printf(__VA_ARGS__)
#else
#define VGLOG(...) do {} while (0)
#endif // VG_DEBUG

#endif // __VGLogger_H__
