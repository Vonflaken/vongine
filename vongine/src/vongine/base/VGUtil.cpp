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
		for (uint32 i = 0; i < str.length() - 1; i++)
		{
			str[i] = str[i + 1]; // Shift one position to left all chars
		}
		// Get rid of two last char because of the previous shift copyied last char to length-2 pos, 
		// so we have to remove the actual last and the copy
		str.erase(str.begin() + str.length() - 2, str.end());
	}

	std::string str_extract_dir(const std::string& path)
	{
		std::string dir = path;
		// Replace "\" with "/"
		str_replace(dir, "\\", "/");

		// Find last "/"
		uint32 slashPos = dir.find_last_of('/');

		// If contains no path, return empty string
		if (slashPos == std::string::npos)
		{
			dir.clear();
		}
		else
		{
			// Remove all characters after the last "/"
			dir.erase(slashPos + 1);
		}

		return dir;
	}

	uint32 str_replace(std::string& str, char const * const target, char const * const replacement)
	{
		uint32 matchesFound = 0;

		uint32 targetLen = strlen(target);
		for (uint32 i = 0; i < str.length(); i++)
		{
			if (str[i] == target[0]) // Compare char in 'i' pos with the first char in 'target'
			{
				// Compare substring of range (start match pos)-(start match pos + 'targetLen') with 'target'
				if (strncmp(str.c_str() + i, target, targetLen) == 0) 
				{
					str.replace(i, i + targetLen, replacement); // Actual replace strings
					matchesFound++;
				}
			}
		}

		return matchesFound;
	}

	std::string str_extract_ext(const std::string& str)
	{
		uint32 dotPos = str.find_last_of('.');
		if (dotPos != std::string::npos)
			return str.substr(dotPos + 1);
		else
			return "";
	}
}

NS_VG_END
