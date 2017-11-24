#ifndef __VGMATERIALPROTOCOL_H__
#define __VGMATERIALPROTOCOL_H__

#include "VGMacros.h"
#include "base/VGTypes.h"
#include "VGBlendingFunctions.h"
#include "VGDepthTestFunctions.h"

NS_VG_BEGIN

class Texture2D;
class Material;

class DLLAPI MaterialProtocol
{
public:
	MaterialProtocol();

	void ApplyToMaterial(Material* mat);

	bool IsMaterialDirty() const { return _isDirty; }

	/**
	* @param val Clamped 0-1
	*/
	void SetOpacity(const float val);
	float GetOpacity() const { return _alpha; }

	/**
	* @param red Clamped 0-255
	* @param green Clamped 0-255
	* @param blue Clamped 0-255
	*/
	void SetColor(const uint8 red, const uint8 green, const uint8 blue);
	const Color3i& GetConstColor() const { return _tintColor; }
	Color3i GetColor() const { return _tintColor; }

	void SetTexture(Texture2D* texture);

	void SetBlendingFunction(const BlendFactor src, const BlendFactor dst);

	void SetDepthTestFunction(const DepthTestFunction func);
	void SetWriteToDepth(const bool enabled);

private:
	bool _isDirty;

	float _alpha;
	Color3i _tintColor; /// Vertex color
	Texture2D* _texture;
	BlendFactor _blendFactorSrc;
	BlendFactor _blendFactorDst;
	DepthTestFunction _depthFunc;
	bool _writeToDepth; /// Whereas or not fragments should write to depth buffer
	uint32 _propsOverriddenFlags; /// Store per bit if user set certain property
};

NS_VG_END

#endif // __VGMATERIALPROTOCOL_H__
