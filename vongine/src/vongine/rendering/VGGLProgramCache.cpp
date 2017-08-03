#include "VGGLProgramCache.h"
#include "VGVertexTypes.h"

NS_VG_BEGIN

void GLProgramCache::Init()
{
	// Config programs
	GLProgram* program = AddProgram("PositionTextureColor_noMVP.vert", "PositionTextureColor.frag", GLProgramName::POSITIONTEXTURECOLOR_noMVP);
	if (program)
	{
		program->State().Init(sizeof(VERTEX_P3F_C4F_T2F), program->GetProgramID());
		program->State().SetAttribFloat(0, 3, 0);
		program->State().SetAttribFloat(1, 4, 12);
		program->State().SetAttribFloat(2, 2, 28);
	}
}

GLProgram* GLProgramCache::AddProgram(const char* vertexFilename, const char* fragmentFilename, const GLProgramName programName)
{
	std::unique_ptr<GLProgram> program = std::make_unique<GLProgram>();

	// Build program with vert/frag shaders
	bool success = program->Build(vertexFilename, fragmentFilename);

	if (success) // Insert program if building was correct
	{
		GLProgram* progPtr = program.get();
		_programs.insert({ programName, std::move(program) });
		return progPtr;
	}

	return nullptr;
}

GLProgram* GLProgramCache::GetProgram(const GLProgramName programName) const
{
	auto programFound = _programs.find(programName);
	if (programFound != _programs.end())
	{
		return programFound->second.get();
	}

	return nullptr;
}

NS_VG_END
