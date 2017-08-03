#ifndef __VGRENDERER_H__
#define __VGRENDERER_H__

#include "VGMacros.h"

#include <vector>

NS_VG_BEGIN

enum class RenderQueue
{
	OPAQUE, 
	TRANSPARENT
};

class CommandBuffer;

class DLLAPI Renderer
{
public:
	void AddRenderCommand(CommandBuffer* cmd, const RenderQueue queue);
	void Draw();

private:
	/// Drawcall
	void DrawRenderCommand(CommandBuffer* cmd);

	/// Set global uniforms, those generic values used in most shaders
	void SetGlobalUniforms(CommandBuffer* cmd);

	void ClearAllRenderQueues();

private:
	std::vector<CommandBuffer*> _opaqueQueue;
	std::vector<CommandBuffer*> _transparentQueue;
};

NS_VG_END

#endif // __VGRENDERER_H__
