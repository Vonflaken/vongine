#ifndef __VGAPPLICATION_H__
#define __VGAPPLICATION_H__

#include "VGMacros.h"
#include "base/VGTypes.h"

#include <functional>

NS_VG_BEGIN

typedef struct
{
	uint32 windowWidth;
	uint32 windowHeight;
	// Store on/off config values per bit.
	// Use bitwise op OR to set on multiple states.
	uint32 flags; 
	std::function<void()> engineLoadedCallback; // This function is called when engine finished its load and it's ready to add game stuff.
} AppConfigurationObject;
// Valid values for the 'flags' member of AppConfigurationObject.
#define VG_CFG_LOCKWINDOWRESIZE (1 << 0)

class DLLAPI Application
{
public:
	static Application& GetInstance();

	bool Run(const AppConfigurationObject& appCfg);

protected:
	Application() {}
	virtual ~Application() {}

private:
	bool Init(const AppConfigurationObject& appCfg);

	void SetGLAttributes();

	void Cleanup();
};

NS_VG_END

#endif // __VGAPPLICATION_H__
