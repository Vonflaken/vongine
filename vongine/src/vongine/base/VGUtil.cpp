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

	void str_trim_char(std::string& str)
	{
		// Get rid of first char
		for (uint32 i = 0; i < str.length - 1; i++)
		{
			str[i] = str[i + 1]; // Shift one position to left all chars
		}
		// Get rid of last char
		str.pop_back();
	}
}

NS_VG_END
