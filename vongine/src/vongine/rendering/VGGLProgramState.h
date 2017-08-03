#ifndef __VGGLPROGRAMSTATE_H__
#define __VGGLPROGRAMSTATE_H__

#include "VGMacros.h"
#include "base/VGTypes.h"
#include "VGGLUniform.h"

#include <vector>
#include <memory>

NS_VG_BEGIN

/// Config vertex shader input
/// Set shader uniforms
class DLLAPI GLProgramState
{
private:
	struct AttribCfg
	{
		uint32 type;
		uint32 attribLocation;
		uint32 length; /// Number of elements
		uint32 offset;
	};

public:
	GLProgramState();

	/// Set stride of vertex attribs sets
	/// It should to call before config attribs
	void Init(const uint32 stride, const GLuint programID);

	void SetAttribFloat(const uint32 attribLocation, const uint32 length, const uint32 offset);
	/// Bind vertex attributes to active VBO
	void ApplyAttr();

	/// Set uniforms in current shader program
	void ApplyUni(const std::vector<std::unique_ptr<GLUniform>>& uniforms);
	void ApplyUni(GLUniform* uniform);

	uint32 GetStride() const { return _stride; }

private:
	void SetAttrib(const uint32 type, const uint32 attribLocation, const uint32 length, const uint32 offset);

private:
	bool _isInit;

	uint32 _stride;
	GLuint _programID;
	std::vector<AttribCfg> _tempAttribsCfg; /// Array of vertex attribs config values. Delay gl binding until first draw.
};

NS_VG_END

#endif // __VGGLPROGRAMSTATE_H__
