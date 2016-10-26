#ifndef __VGAPPLICATION_H__
#define __VGAPPLICATION_H__

#include "VGMacros.h"
#include <memory>
#include <functional>

NS_VG_BEGIN

class __declspec(dllexport) Application
{
public:
	Application() {}
	virtual ~Application() {}

	static std::shared_ptr<Application> GetInstance();

	bool Run();

	void SetEngineLoadedCallback(const std::function<void()> func) { _engineLoadedCallback = func; }

private:
	std::function<void()> _engineLoadedCallback;
};

NS_VG_END

#endif // __VGAPPLICATION_H__
