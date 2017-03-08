#include "VGUtils.h"
#include <initializer_list>

NS_VG_BEGIN

template<typename U, typename ... T>
bool one_of(U&& u, T && ... t)
{
	bool match = false;
	(void)std::initializer_list<bool>{ (match = match || u == t)... };
	return match;
}

NS_VG_BEGIN
