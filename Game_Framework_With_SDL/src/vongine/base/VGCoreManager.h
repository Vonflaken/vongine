#ifndef __VGCOREMANAGER_H__
#define __VGCOREMANAGER_H__

#include "VGMacros.h"

NS_VG_BEGIN

class __declspec(dllexport) CoreManager
{
public:
	static CoreManager& GetInstance();

	// Polling events, update entities and render
	void ProcessFrame();

protected:
	CoreManager() {}
	virtual ~CoreManager() {}
};

NS_VG_END

#endif // __VGCOREMANAGER_H__
