#include "VGSimple2DCollision.h"

NS_VG_BEGIN

Simple2DCollision::Simple2DCollision()
{
	// Create WireframeMaterial
	_debugMat = std::make_unique<WireframeMaterial>();
	// Create CommandBuffer
	_debugDrawCmd = std::make_unique<CommandBuffer>();
	_debugDrawCmd->Init();
}

NS_VG_END
