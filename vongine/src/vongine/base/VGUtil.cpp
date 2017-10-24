#include "VGUtils.h"

#include <sstream>

NS_VG_BEGIN

namespace utils
{
	void str_split(const std::string& str, const char delimiter, std::vector<std::string>& elems)
	{
		std::istringstream iss(str);
		std::string item;
		while (std::getline(iss, item, delimiter))
		{
			elems.push_back(item);
		}
	}
}

NS_VG_END
