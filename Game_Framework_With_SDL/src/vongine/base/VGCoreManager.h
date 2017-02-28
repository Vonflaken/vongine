#ifndef __VGCOREMANAGER_H__
#define __VGCOREMANAGER_H__

#include "VGMacros.h"
#include "VGServiceLocator.h"

NS_VG_BEGIN

class __declspec(dllexport) CoreManager
{
public:
	static CoreManager& GetInstance();

	// Instance engine services like file I/O system, audio system, etc.
	void InitServices();
	const ServiceLocator& GetServiceLocator() const { return _serviceLocator; }

	// Polling input events, broadcast custom events in queue, update entities and render the scene.
	void ProcessFrame(const float deltaTime);

protected:
	CoreManager();
	virtual ~CoreManager() {}

private:
	ServiceLocator _serviceLocator;
};

NS_VG_END

#endif // __VGCOREMANAGER_H__
