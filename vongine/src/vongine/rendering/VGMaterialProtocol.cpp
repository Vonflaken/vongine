#include "VGMaterialProtocol.h"
#include "VGMaterial.h"
#include "VGTexture2D.h"

#include "glm/glm.hpp"

NS_VG_BEGIN

MaterialProtocol::MaterialProtocol()
: _isDirty(true)
, _alpha(1.f)
, _tintColor(255, 255, 255)
, _texture(nullptr)
, _blendFactorSrc(BlendFactor::NONE)
, _blendFactorDst(BlendFactor::NONE)
, _depthFunc(DepthTestFunction::LESS)
, _writeToDepth(true)
, _propsOverriddenFlags(0)
{}

void MaterialProtocol::ApplyToMaterial(Material* mat)
{
	if (_isDirty)
	{
		_isDirty = false;

		mat->SetProperties(
			_alpha, 
			_tintColor, 
			_texture, 
			_blendFactorSrc, 
			_blendFactorDst, 
			_depthFunc, 
			_writeToDepth, 
			_propsOverriddenFlags);
	}
}

void MaterialProtocol::SetOpacity(const float val)
{
	_isDirty = true;
	_propsOverriddenFlags |= Material::FLAG_OPACITY;

	_alpha = glm::clamp(val, 0.f, 1.f);
}

void MaterialProtocol::SetColor(const uint8 red, const uint8 green, const uint8 blue)
{
	_isDirty = true;
	_propsOverriddenFlags |= Material::FLAG_COLOR;

	_tintColor.r = glm::clamp((int)red, 0, 255);
	_tintColor.g = glm::clamp((int)green, 0, 255);
	_tintColor.b = glm::clamp((int)blue, 0, 255);
}

void MaterialProtocol::SetTexture(Texture2D* texture)
{
	_isDirty = true;
	_propsOverriddenFlags |= Material::FLAG_TEXTURE;

	_texture = texture;
}

void MaterialProtocol::SetBlendingFunction(const BlendFactor src, const BlendFactor dst)
{
	_isDirty = true;
	_propsOverriddenFlags |= Material::FLAG_BLENDING;

	_blendFactorSrc = src;
	_blendFactorDst = dst;
}

void MaterialProtocol::SetDepthTestFunction(const DepthTestFunction func)
{
	_isDirty = true;
	_propsOverriddenFlags |= Material::FLAG_DEPTH_TEST_FUNC;

	_depthFunc = func;
}

void MaterialProtocol::SetWriteToDepth(const bool enabled)
{
	_isDirty = true;
	_propsOverriddenFlags |= Material::FLAG_WRITE_DEPTH;

	_writeToDepth = enabled;
}

NS_VG_END
