#include "VGCoreManager.h"

NS_VG_BEGIN

CoreManager& CoreManager::GetInstance()
{
	static CoreManager* instance = new CoreManager();
	return *instance;
}

void CoreManager::ProcessFrame()
{

}

NS_VG_END
