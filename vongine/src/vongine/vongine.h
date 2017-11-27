#ifndef __VONGINE_H__
#define __VONGINE_H__

#include "2d/VGSprite.h"

#include "base/VGCoreManager.h"
#include "base/VGEntity.h"
#include "base/VGEventManager.h"
#include "base/VGInputManager.h"
#include "base/VGLogger.h"
#include "base/VGMathExtension.h"
#include "base/VGScene.h"
#include "base/VGScreen.h"
#include "base/VGServiceLocator.h"
#include "base/VGTypes.h"
#include "base/VGUtils.h"

#include "platform/VGApplication.h"
#include "platform/VGFile.h"

#include "rendering/VGCamera.h"
#include "rendering/VGCommandBuffer.h"
#include "rendering/VGGL.h"
#include "rendering/VGGLProgram.h"
#include "rendering/VGGLProgramCache.h"
#include "rendering/VGGLProgramState.h"
#include "rendering/VGGLUniform.h"
#include "rendering/VGMaterial.h"
#include "rendering/VGMaterialProtocol.h"
#include "rendering/VGQuadCommandBuffer.h"
#include "rendering/VGRenderContext.h"
#include "rendering/VGRenderer.h"
#include "rendering/VGShader.h"
#include "rendering/VGTexture2D.h"
#include "rendering/VGVertexTypes.h"

#include "resources/VGBitmapFont.h"
#include "resources/VGFont.h"
#include "resources/VGImage.h"
#include "resources/VGResourcesCache.h"

#include "ui/VGButton.h"
#include "ui/VGLabel.h"
#include "ui/VGTouchableWidget.h"
#include "ui/VGUICanvas.h"
#include "ui/VGUIManager.h"
#include "ui/VGUIMessages.h"
#include "ui/VGWidget.h"

#include "utility-structures/VGEvent.h"
#include "utility-structures/VGSignal.h"

#include "VGMacros.h"
#include "VGSDL.h"

#endif // __VONGINE_H__
