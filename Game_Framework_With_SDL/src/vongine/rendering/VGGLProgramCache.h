#ifndef __VGPROGRAMCACHE_H__
#define __VGPROGRAMCACHE_H__

#include "VGMacros.h"
#include <unordered_map>
#include "rendering/VGGLProgram.h"
#include <memory>

NS_VG_BEGIN

class __declspec(dllexport) GLProgramCache
{
public:
	/// Create all programs from built-in shaders and store them in the _programs map
	void Init();

	/// Create program and store it
	/// Internally create temporal shaders from filenames provided for building the program
	void AddProgram(const char* vertexFilename, const char* fragmentFilename, const GLProgramName programName);

	/// Return program matching programName or nullptr if not found
	const GLProgram* GetProgram(const GLProgramName programName) const;

private:
	std::unordered_map<GLProgramName, std::unique_ptr<GLProgram>> _programs; // Contains programs from all shaders built-in in the engine plus user additions
};

NS_VG_END

#endif // __VGPROGRAMCACHE_H__
