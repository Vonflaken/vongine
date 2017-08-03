#include "VGRenderer.h"
#include "VGCommandBuffer.h"
#include "VGGLProgram.h"
#include "VGGLProgramState.h"
#include "VGCamera.h"
#include "base/VGCoreManager.h"
#include "VGRenderContext.h"

#include "glm/gtc/type_ptr.hpp"

#include <algorithm>

NS_VG_BEGIN

/**
* Comparison function for back-to-front sorting
* Draw order in transparent geometry is treated as distance to camera
* Desc order
*/
inline bool BackToFrontComp(const CommandBuffer* first, const CommandBuffer* last)
{
	return first->GetDrawOrder() >= last->GetDrawOrder();
}

void Renderer::AddRenderCommand(CommandBuffer* cmd, const RenderQueue queue)
{
	switch (queue)
	{
	case RenderQueue::OPAQUE:
		_opaqueQueue.push_back(cmd);
		break;
	case RenderQueue::TRANSPARENT:
		_transparentQueue.push_back(cmd);
		break;
	}
}

void Renderer::Draw()
{
	// Enable depth testing before actual draws
	CoreManager::GetInstance().RenderContext()->EnableDepthTesting(true);

	// Render opaque geometry first
	for (auto it = _opaqueQueue.begin(); it != _opaqueQueue.end(); it++)
	{
		DrawRenderCommand(*it);
	}

	// Sort back-to-front transparent geometry
	std::sort(_transparentQueue.begin(), _transparentQueue.end(), BackToFrontComp);
	// Render transparent geometry
	for (auto it = _transparentQueue.begin(); it != _transparentQueue.end(); it++)
	{
		DrawRenderCommand(*it);
	}

	// Clean up commands array
	ClearAllRenderQueues();
}

void Renderer::DrawRenderCommand(CommandBuffer* cmd)
{
	// Set gfx config
	cmd->PrepareToDraw();

	SetGlobalUniforms(cmd);
	
	// Draw
	glDrawElements(GL_TRIANGLES, cmd->GetIndicesLength(), GL_UNSIGNED_INT, 0);
	// TODO: Add one drawcall to counter
	glBindVertexArray(0); // Unbind last VAO
}

void Renderer::SetGlobalUniforms(CommandBuffer* cmd)
{
	GLProgramState& programState = cmd->GetMaterial()->GetProgram()->State();
	auto camera = Camera::s_renderingCamera;

	// Create modelView matrix uniform
	const glm::mat4& modelViewMatrix = cmd->GetMVMatrix();
	GLUniformMatrix4f uMVMat;
	uMVMat.name = "u_modelViewMatrix";
	GLUniformHelpers::SetValue(&uMVMat, glm::value_ptr(modelViewMatrix));

	// Create projeciton matrix uniform
	const glm::mat4& projMatrix = camera->GetProjectionMatrix();
	GLUniformMatrix4f uProjMat;
	uProjMat.name = "u_projMatrix";
	GLUniformHelpers::SetValue(&uProjMat, glm::value_ptr(projMatrix));

	// Create view matrix uniform
	const glm::mat4& viewMatrix = camera->GetViewMatrix();
	GLUniformMatrix4f uViewMat;
	uViewMat.name = "u_viewMatrix";
	GLUniformHelpers::SetValue(&uViewMat, glm::value_ptr(viewMatrix));

	// Set uniforms
	programState.ApplyUni(&uMVMat);
	programState.ApplyUni(&uProjMat);
	programState.ApplyUni(&uViewMat);
}

void Renderer::ClearAllRenderQueues()
{
	_opaqueQueue.clear();
	_transparentQueue.clear();
}

NS_VG_END
