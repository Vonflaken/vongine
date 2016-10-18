#ifndef __VFApplication_H__
#define __VFApplication_H__

#include "VFMacros.h"
#include <memory>

NS_VF_BEGIN

class __declspec(dllexport) Application
{
public:
	virtual ~Application() {}

	static Application& GetInstance();

	bool Run();

private:
	Application() {}

private:
	static std::shared_ptr<Application> s_instance;
};

NS_VF_END

#endif // __VFApplication_H__
