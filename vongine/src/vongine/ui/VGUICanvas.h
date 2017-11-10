#ifndef __VGUICANVAS_H__
#define __VGUICANVAS_H__

#include "VGMacros.h"
#include "VGWidget.h"

#include <memory>

NS_VG_BEGIN

class Camera;

namespace ui
{
	class DLLAPI Canvas : public Widget
	{
	public:
		static std::shared_ptr<Canvas> Create(const Size& size);

		Canvas();

		/**
		* Creates UI Camera.
		*/
		bool Init(const Size& size) override;

		/**
		* Add UI Camera of this Canvas to the scene.
		*/
		void OnAttach() override;

		/**
		* Remove UI Camera from scene when this Canvas get deactivate.
		*/
		void OnDetach() override;

	private:
		std::shared_ptr<Camera> _canvasCam; // Canvas camera, renders UI elements inside this canvas
	};
}

NS_VG_END

#endif // __VGUICANVAS_H__
