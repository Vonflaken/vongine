#include "VGRenderContext.h"

#include "ogl/glew.h"

NS_VG_BEGIN

RenderContext::RenderContext()
: _glContext(nullptr, VG_SDL_Deleter())
{}

RenderContext::~RenderContext()
{}

SDL_GLContext RenderContext::CreateGLContext(SDL_Window* window)
{
	if (!_glContext && window)
	{
		auto ctx = VG_SDL_CreateGLContext(window);
		if (ctx)
		{
			_glContext = std::move(ctx);

			return _glContext.get();
		}
	}

	VGLOG_ERROR("Creating an OpenGL context failed: '%s'", SDL_GetError());

	return nullptr;
}

void RenderContext::ActiveTextureUnit(const uint8 unitNumber)
{
	if (unitNumber < 16)
	{
		glActiveTexture(GL_TEXTURE0 + unitNumber);
	}
}

void RenderContext::SetViewport(const Rect& viewportRect)
{
	if (viewportRect != _viewportRect)
	{
		glViewport((GLint)viewportRect.x, (GLint)viewportRect.y, viewportRect.width, viewportRect.height);
		_viewportRect = viewportRect;
	}
}

void RenderContext::EnableBlending(const bool enabled)
{
	if (enabled)
		glEnable(GL_BLEND);
	else
		glDisable(GL_BLEND);
}

void RenderContext::SetBlendingFunction(const BlendFactor src, const BlendFactor dst)
{
	glBlendFunc(
		BlendingFunctionsHelpers::GetGLValueFromInternal(src),
		BlendingFunctionsHelpers::GetGLValueFromInternal(dst));
}

void RenderContext::EnableDepthTesting(const bool enabled)
{
	if (enabled)
		glEnable(GL_DEPTH_TEST);
	else
		glDisable(GL_DEPTH_TEST);
}

void RenderContext::EnableWriteDepth(const bool enabled)
{
	glDepthMask(enabled);
}

void RenderContext::SetDepthFunction(const DepthTestFunction func)
{
	glDepthFunc(DepthTestFunctionsHelpers::GetGLValueFromInternal(func));
}

void RenderContext::SetClearColor(const Color3i color)
{
	glClearColor(color.r / 255.f, color.g / 255.f, color.b / 255.f, 1.f);
}

void RenderContext::SetWindingOrder(const GLWinding winding)
{
	glFrontFace(GetGLValueFromInternal(winding));
}

void RenderContext::SetCullingFace(const GLCullingFace cullFace)
{
	glEnable(GL_CULL_FACE);
	glCullFace(GetGLValueFromInternal(cullFace));
}

void RenderContext::DisableCullingFace()
{
	glDisable(GL_CULL_FACE);
}

int32 RenderContext::GetGLValueFromInternal(const GLCullingFace internalVal) const
{
	int32 glVal = -1;
	switch (internalVal)
	{
	case GLCullingFace::BACK:
		glVal = GL_BACK;
		break;
	case GLCullingFace::FRONT:
		glVal = GL_FRONT;
		break;
	case GLCullingFace::FRONT_BACK:
		glVal = GL_FRONT_AND_BACK;
		break;
	}
	return glVal;
}

int32 RenderContext::GetGLValueFromInternal(const GLWinding internalVal) const
{
	int32 glVal = -1;
	switch (internalVal)
	{
	case GLWinding::CCW:
		glVal = GL_CCW;
		break;
	case GLWinding::CW:
		glVal = GL_CW;
		break;
	}
	return glVal;
}

NS_VG_END
