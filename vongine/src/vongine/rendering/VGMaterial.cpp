#include "VGMaterial.h"
#include "VGGLProgram.h"
#include "VGTexture2D.h"
#include "base/VGCoreManager.h"

NS_VG_BEGIN

Material::Material()
: _program(nullptr)
, _alpha(1.f)
, _tintColor(255, 255, 255)
, _texture(nullptr)
, _blendFactorSrc(BlendFactor::NONE)
, _blendFactorDst(BlendFactor::NONE)
, _depthFunc(DepthTestFunction::LESS)
, _writeToDepth(true)
, _propsOverriddenFlags(0)
, _isTransparent(false)
, _cullingFace(GLCullingFace::BACK)
{}

void Material::InitWithUniforms(std::unique_ptr<GLUniform>* uniforms, const uint32 length)
{
	for (uint32 i = 0; i < length; i++)
	{
		_uniforms.push_back(std::move(*(uniforms + i)));
	}
}

void Material::Use()
{
	// Apply vertex attr
	_program->State().ApplyAttr();
	// Use shader program
	_program->Use();
	// Bind texture to default texture unit
	_texture->BindToTexUnit(0);
	// Apply uniforms
	_program->State().ApplyUni(_uniforms);

	auto renderCtx = CoreManager::GetInstance().RenderContext();

	if (_blendFactorSrc != BlendFactor::NONE && _blendFactorDst != BlendFactor::NONE)
	{
		// Enable blending
		renderCtx->EnableBlending(true);
		// Set blending func
		renderCtx->SetBlendingFunction(_blendFactorSrc, _blendFactorDst);
	}
	else
	{
		// Disable blending
		renderCtx->EnableBlending(false);
	}

	// Set depth testing function
	renderCtx->SetDepthFunction(_depthFunc);

	// Set write to depth buffer
	if (IsTransparent() && !(_propsOverriddenFlags & FLAG_WRITE_DEPTH))
	{ // Transparents don't write into the depth buffer, however user can override this behaviour
		renderCtx->EnableWriteDepth(false);
	}
	else
	{
		renderCtx->EnableWriteDepth(_writeToDepth);
	}

	// Culling face cfg
	if (_cullingFace != GLCullingFace::NONE)
	{ // Cull the face that was set
		renderCtx->SetCullingFace(_cullingFace);
	}
	else // Don't cull any face
	{
		renderCtx->DisableCullingFace();
	}
}

void Material::SetProperties(
	const float opacity, 
	const Color3i& color, 
	Texture2D* texture, 
	const BlendFactor src, 
	const BlendFactor dst, 
	const DepthTestFunction depthFunc,
	const bool writeToDepth,
	const uint32 propsOverriddenFlags)
{
	_alpha = opacity;
	_tintColor = color;
	_texture = texture;
	_blendFactorSrc = src;
	_blendFactorDst = dst;
	_depthFunc = depthFunc;
	_writeToDepth = writeToDepth;
	_propsOverriddenFlags = propsOverriddenFlags;
}

void Material::GetProperties(
	float* opacity, 
	Color3i* color, 
	Texture2D** texture)
{
	if (opacity) *opacity = _alpha;
	if (color) *color = _tintColor;
	if (texture) *texture = _texture;
}

void Material::UpdateUniform(const std::string& name, void const * values)
{
	for (uint32 i = 0; i < _uniforms.size(); i++)
	{
		GLUniform* uniform = _uniforms[i].get();
		// Search for uniform matching name
		if (uniform->name == name)
		{
			GLUniformHelpers::SetValue(uniform, values);
		}
	}
}

NS_VG_END
