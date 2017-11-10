#ifndef __VGUTILS_H__
#define __VGUTILS_H__

#include "VGMacros.h"
#include "VGLogger.h"

#include <stdlib.h>
#include <assert.h>
#include <initializer_list>
#include <string>
#include <vector>

NS_VG_BEGIN

namespace utils
{
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

#define VGASSERT(exp, str_literal)	do { \
	if (!(exp)) \
		VGLOG_ERROR("%s", str_literal); \
	assert(exp); \
} while(0)

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

	inline bool is_even(const int32 val)
	{
		return !(val % 2);
	}

	void str_split(const std::string& str, const char delimiter, std::vector<std::string>& elems);

	inline bool str_starts_with(const char* prefix, const char* str)
	{
		return strncmp(prefix, str, strlen(prefix)) == 0;
	}

	/**
	* Remove first char from both sides of the string.
	*/
	void str_trim_char(std::string& str);

	std::string str_extract_dir(const std::string& path);

	/**
	* Replaces each substring of 'str' that matches the 'target' string literal with the 
	* specified 'replacement' string literal.
	* @return uint32 Number of substrings replaced.
	*/
	uint32 str_replace(std::string& str, char const * const target, char const * const replacement);

	/**
	* Seek for file extension in 'str'.
	* @return std::string Extension string without dot or empty string if extension not found.
	*/
	std::string str_extract_ext(const std::string& str);
}

NS_VG_END

#endif // __VGUTILS_H__
