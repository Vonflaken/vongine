#ifndef __VFApplication_H__
#define __VFApplication_H__

#include "VFMacros.h"
#include <memory>

NS_VF_BEGIN

class __declspec(dllexport) Application
{
public:
	virtual ~Application() {}

	static std::shared_ptr<Application> GetInstance();

	bool Run();

private:
	Application() {}
};

NS_VF_END

#endif // __VFApplication_H__
