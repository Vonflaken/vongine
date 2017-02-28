#include "VGCoreManager.h"

NS_VG_BEGIN

CoreManager& CoreManager::GetInstance()
{
	static CoreManager* instance = new CoreManager();
	return *instance;
}

CoreManager::CoreManager()
: _serviceLocator()
{}

void CoreManager::ProcessFrame(const float deltaTime)
{

}

NS_VG_END
