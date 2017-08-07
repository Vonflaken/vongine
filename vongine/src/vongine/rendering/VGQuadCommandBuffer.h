#ifndef __VGQUADCOMMANDBUFFER_H__
#define __VGQUADCOMMANDBUFFER_H__

#include "VGCommandBuffer.h"

NS_VG_BEGIN

class DLLAPI QuadCommandBuffer : public CommandBuffer
{
public:
	/**
	* Allocate enough memory for 4 vertex with this stride
	* Initialize indices buffer with fixed values
	*/
	void InitWithStride(const uint32 vertStride);
};

NS_VG_END

#endif // __VGQUADCOMMANDBUFFER_H__
