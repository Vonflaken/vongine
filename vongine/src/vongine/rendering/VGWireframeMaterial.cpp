#include "VGWireframeMaterial.h"
#include "base/VGCoreManager.h"
#include "base/VGTypes.h"

NS_VG_BEGIN

WireframeMaterial::WireframeMaterial()
{
	// Create uniform with color for tinting lines rendered
	std::unique_ptr<GLUniform> color = std::make_unique<GLUniform3f>();
	color->name = "u_color";
	float* valuePtr = ((GLUniform3f*)color.get())->value;
	valuePtr[0] = 0.f/*r*/; valuePtr[1] = 1.f/*g*/; valuePtr[2] = 0.f/*b*/; // GREEN is default lines color
	InitWithUniforms(&color, 1); // Add uniform

	SetIsTransparent(true);
	SetCullingFace(GLCullingFace::NONE);
	SetProgram(CoreManager::GetInstance().GLProgramCache()->GetProgram(GLProgramName::POSITIONUCOLOR_VP));
}

void WireframeMaterial::SetLineColor(const Color3f color)
{
	float rgb[3] = { color.r, color.g, color.b };
	UpdateUniform("u_color", rgb);
}

void WireframeMaterial::Use()
{
	Material::Use();

	// Set width of lines rendered
	glLineWidth(1.f);

	// Change polygon mode in order to draw only the outline of triangles -> wireframe look
	CoreManager::GetInstance().RenderContext()->SetPolygonMode(GL_LINE);
}

NS_VG_END
