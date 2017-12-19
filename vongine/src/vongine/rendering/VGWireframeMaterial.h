#ifndef __VGWIREFRAMEMATERIAL_H__
#define __VGWIREFRAMEMATERIAL_H__

#include "VGMacros.h"
#include "VGMaterial.h"

NS_VG_BEGIN

class DLLAPI WireframeMaterial : public Material
{
public:
	WireframeMaterial();

	void SetLineColor(const Color3f color);

	/**
	* Change GL polygon mode in order to render the outline of triangles.
	*/
	void Use() override;
};

NS_VG_END

#endif // __VGWIREFRAMEMATERIAL_H__
