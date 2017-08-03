#ifndef __VGCOREMANAGER_H__
#define __VGCOREMANAGER_H__

#include "VGMacros.h"
#include "VGServiceLocator.h"
#include "rendering/VGRenderer.h"

#include "VGSDL.h"

#include <vector>

NS_VG_BEGIN

class Scene;
class Screen;

class DLLAPI CoreManager
{
public:
	static CoreManager& GetInstance();

	/**
	* Create app window with given size and gl context
	*/
	bool InitWithScreenSize(const uint32 width, const uint32 height);

	/**
	* Instance engine services like file I/O system, audio system, etc.
	*/
	void InitServices();

	const ServiceLocator* GetServiceLocator() const { return _serviceLocator.get(); }
	/// Helpers to make shorter the calls to services
	const FileUtils* FileUtils() const { return _serviceLocator->FileUtilsService(); }
	ResourcesCache* const ResourcesCache() const { return _serviceLocator->ResourcesCacheService(); }
	RenderContext* const RenderContext() const { return _serviceLocator->RenderContextService(); }
	GLProgramCache* const GLProgramCache() const { return _serviceLocator->GLProgramCacheService(); }

	bool CreateScreenAndGLContext(const uint32 width, const uint32 height);

	Renderer* GetRenderer() const { return _renderer.get(); }

	/// Polling input events, broadcast custom events in queue, update entities and render the scene.
	void ProcessFrame(bool* shouldExitApp);

	/// Will replace the scene at the end of the frame
	void ReplaceScene(const std::shared_ptr<Scene> newScene);

	SDL_Window* GetWindow();
	const Size& GetScreenSize() const;

protected:
	CoreManager();
	virtual ~CoreManager();

private:
	std::unique_ptr<ServiceLocator> _serviceLocator;

	std::unique_ptr<Screen> _screen;
	std::unique_ptr<Renderer> _renderer;

	std::shared_ptr<Scene> _activeScene;
	std::shared_ptr<Scene> _nextScene;
};

NS_VG_END

#endif // __VGCOREMANAGER_H__
