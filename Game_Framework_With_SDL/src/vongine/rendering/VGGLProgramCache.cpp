#include "VGGLProgramCache.h"

NS_VG_BEGIN

void GLProgramCache::Init()
{
	AddProgram("PositionTextureColor_noMVP.vert", "PositionTextureColor.frag", GLProgramName::POSITIONTEXTURECOLOR_noMVP);
}

void GLProgramCache::AddProgram(const char* vertexFilename, const char* fragmentFilename, const GLProgramName programName)
{
	std::unique_ptr<GLProgram> program = std::make_unique<GLProgram>();

	// Build program with vert/frag shaders
	bool success = program->Build(vertexFilename, fragmentFilename);

	if (success) // Insert program if building was correct
	{
		_programs.insert({ programName, std::move(program) });
	}
}

const GLProgram* GLProgramCache::GetProgram(const GLProgramName programName) const
{
	auto programFound = _programs.find(programName);
	if (programFound != _programs.end())
	{
		return programFound->second.get();
	}

	return nullptr;
}

NS_VG_END
