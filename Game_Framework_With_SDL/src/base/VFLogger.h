#ifndef __VFLogger_H__
#define __VFLogger_H__

#if defined(VF_DEBUG) && VF_DEBUG == 1
#define VFLOG(...) printf(__VA_ARGS__)
#else
#define VFLOG(...) do {} while (0)
#endif // VF_DEBUG

#endif // __VFLogger_H__
