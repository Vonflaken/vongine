#include "VGFileUtils.h"

NS_VG_BEGIN

FileUtils::FileUtils()
: _resourcesPath("Resources/")
{}

/// Build a path from the root resources folder to the file provided
const std::string FileUtils::GetFullPathOf(const std::string& filename) const
{
	return _resourcesPath + filename;
}

NS_VG_END
