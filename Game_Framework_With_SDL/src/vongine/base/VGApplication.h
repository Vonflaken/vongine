#ifndef __VGAPPLICATION_H__
#define __VGAPPLICATION_H__

#include "VGMacros.h"
#include <memory>

NS_VG_BEGIN

class __declspec(dllexport) Application
{
public:
	Application() {}
	virtual ~Application() {}

	static std::shared_ptr<Application> GetInstance();

	bool Run();
};

NS_VG_END

#endif // __VGAPPLICATION_H__
