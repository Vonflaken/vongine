#ifndef __VGFileUtils_H__
#define __VGFileUtils_H__

#include "VGMacros.h"
#include <string>

NS_VG_BEGIN

class __declspec(dllexport) FileUtils
{
public:
	FileUtils();

	/// Returns a path to the provided file
	const std::string GetFullPathOf(const std::string& filename) const;

private:
	/// Name of the folder where is located all game resources
	const char* _resourcesPath;
};

NS_VG_END

#endif // __VGFileUtils_H__

