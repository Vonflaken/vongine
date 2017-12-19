#ifndef __VGMATERIAL_H__
#define __VGMATERIAL_H__

#include "VGMacros.h"
#include "base/VGTypes.h"
#include "VGGLUniform.h"
#include "VGBlendingFunctions.h"
#include "VGDepthTestFunctions.h"
#include "VGRenderContext.h"

#include <vector>
#include <memory>

NS_VG_BEGIN

class GLProgram;
class Texture2D;

class DLLAPI Material
{
public:
	Material();

	/**
	* @param uniforms Will move the ownership of Its pointers to a member array.
	*/
	void InitWithUniforms(std::unique_ptr<GLUniform>* uniforms, const uint32 length);

	/**
	* Set gfx config in order to draw an element.
	* Use shader program.
	* Set material uniforms.
	* The first time is called sets vertex attributes of the shader program.
	*/
	virtual void Use();

	void SetProperties(
		const float opacity, 
		const Color3i& color, 
		Texture2D* texture, 
		const BlendFactor src, 
		const BlendFactor dst, 
		const DepthTestFunction depthFunc, 
		const bool writeToDepth, 
		const uint32 propsOverriddenFlags);

	void GetProperties(
		float* opacity, 
		Color3i* color, 
		Texture2D** texture);

	void SetProgram(GLProgram* program) { _program = program; }
	const GLProgram* GetProgram() const { return _program; }
	GLProgram* GetProgram() { return _program; }

	void SetIsTransparent(const bool val) { _isTransparent = val; }
	bool IsTransparent() const { return _isTransparent; }

	void SetCullingFace(const GLCullingFace face) { _cullingFace = face; }

	/**
	* Set new values of given uniform.
	* Search by name.
	*/
	void UpdateUniform(const std::string& name, void const * values);

public:
	enum {
		FLAG_OPACITY			= (1 << 0), 
		FLAG_COLOR				= (1 << 1), 
		FLAG_TEXTURE			= (1 << 2), 
		FLAG_BLENDING			= (1 << 3), 
		FLAG_DEPTH_TEST_FUNC	= (1 << 4), 
		FLAG_WRITE_DEPTH		= (1 << 5)
	};

protected:
	GLProgram* _program;

	/**
	* Vars SET through MaterialProtocol.
	*/
	float _alpha;
	Color3i _tintColor; /// Vertex color
	Texture2D* _texture;
	BlendFactor _blendFactorSrc;
	BlendFactor _blendFactorDst;
	DepthTestFunction _depthFunc;
	bool _writeToDepth; /// Whereas or not fragments should write to depth buffer
	uint32 _propsOverriddenFlags; /// Store per bit if user set certain property

	/**
	* Vars DON'T SET through MaterialProtocol, set through Material itself.
	*/
	bool _isTransparent;
	GLCullingFace _cullingFace;

	std::vector<std::unique_ptr<GLUniform>> _uniforms;
};

NS_VG_END

#endif // __VGMATERIAL_H__
