#ifndef __VGAPPLICATION_H__
#define __VGAPPLICATION_H__

#include "VGMacros.h"
#include <functional>

NS_VG_BEGIN

class __declspec(dllexport) Application
{
public:
	static Application& GetInstance();

	bool Run();

	void SetEngineLoadedCallback(const std::function<void()> func) { _engineLoadedCallback = func; }

protected:
	Application() {}
	virtual ~Application() {}

private:
	std::function<void()> _engineLoadedCallback;
};

NS_VG_END

#endif // __VGAPPLICATION_H__
