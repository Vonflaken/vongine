#ifndef __VGRENDERCONTEXT_H__
#define __VGRENDERCONTEXT_H__

#include "VGMacros.h"
#include "base/VGTypes.h"
#include "VGBlendingFunctions.h"
#include "VGDepthTestFunctions.h"

#include "VGSDL.h"

NS_VG_BEGIN

enum class GLCullingFace
{
	FRONT, 
	BACK, 
	FRONT_BACK, 
	NONE
};

enum class GLWinding
{
	CCW, 
	CW
};

class DLLAPI RenderContext
{
public:
	RenderContext();
	virtual ~RenderContext();

	SDL_GLContext CreateGLContext(SDL_Window* window);

	void ActiveTextureUnit(const uint8 unitNumber);

	void SetViewport(const Rect& viewportRect);

	void EnableBlending(const bool enabled);
	void SetBlendingFunction(const BlendFactor src, const BlendFactor dst);

	void EnableDepthTesting(const bool enabled);
	void EnableWriteDepth(const bool enabled);
	void SetDepthFunction(const DepthTestFunction func);

	void SetClearColor(const Color3i color);

	void SetWindingOrder(const GLWinding winding);
	void SetCullingFace(const GLCullingFace cullFace);
	void DisableCullingFace();

	void SetPolygonMode(const int32 mode);

private:
	/**
	* @return GL value matching the internal type or -1 if doesn't find a match
	*/
	int32 GetGLValueFromInternal(const GLCullingFace internalVal) const;
	/**
	* @return GL value matching the internal type or -1 if doesn't find a match
	*/
	int32 GetGLValueFromInternal(const GLWinding internalVal) const;

private:
	std::unique_ptr<void, VG_SDL_Deleter> _glContext;

	Rect _viewportRect; // Gl viewport rect
};

NS_VG_END

#endif
