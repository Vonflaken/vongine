#ifndef __VGUTILS_H__
#define __VGUTILS_H__

#include "VGMacros.h"
#include "VGLogger.h"

#include <stdlib.h>
#include <assert.h>
#include <initializer_list>

NS_VG_BEGIN

struct DLLAPI VG_Free_Deleter
{
public:
	inline void operator()(void* mem) const { free(mem); }
};

struct DLLAPI VG_Array_Deleter
{
public:
	inline void operator()(void* mem) const { delete[] mem; }
};

template<typename U, typename ... T>
bool one_of(U&& u, T && ... t)
{
	bool match = false;
	(void)std::initializer_list<bool>{ (match = match || u == t)... };
	return match;
}

#define VGASSERT(exp, str_literal)	{ \
								if (!(exp)) \
									VGLOG_ERROR("%s", str_literal); \
								assert(exp); \
							}
#define VGSTATIC_ASSERT(exp, str_literal) static_assert(exp, str)

inline bool is_safe_cast_u32_to_s32(const uint32 val)
{
	return val <= INT_MAX;
}

inline bool is_safe_cast_u32_to_float(const uint32 val)
{
	return val <= 2147483520 /* float_max */;
}

inline bool is_safe_cast_s32_to_u32(const int32 val)
{
	return val >= 0;
}

inline bool is_safe_cast_f_to_u32(const float val)
{
	return val >= 0.f;
}

NS_VG_END

#endif // __VGUTILS_H__
