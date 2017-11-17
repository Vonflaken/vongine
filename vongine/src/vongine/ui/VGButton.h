#ifndef __VGBUTTON_H__
#define __VGBUTTON_H__

#include "VGMacros.h"
#include "ui/VGTouchableWidget.h"
#include "rendering/VGMaterialProtocol.h"
#include "rendering/VGMaterial.h"
#include "rendering/VGQuadCommandBuffer.h"

NS_VG_BEGIN

namespace ui
{
	class DLLAPI Button : public TouchableWidget, public MaterialProtocol
	{
		/**
		* @param normalImage Mandatory, button fails to initialize if image doesn't exist.
		* @param pressedImage Optional.
		*/
		static std::shared_ptr<Button> Create(const std::string& normalImage, const std::string& pressedImage);
		/**
		* @param normalImage Mandatory, button fails to initialize if image doesn't exist.
		* @param pressedImage Optional.
		*/
		static std::shared_ptr<Button> Create(const std::string& normalImage, const std::string& pressedImage, const glm::vec3& position);
		/**
		* @param normalImage Mandatory, button fails to initialize if image doesn't exist.
		* @param pressedImage Optional.
		*/
		static std::shared_ptr<Button> Create(const std::string& normalImage, const std::string& pressedImage, const glm::vec3& position, const Size& size);

		Button();

		/**
		* @param normalImage Mandatory, button fails to initialize if image doesn't exist.
		* @param pressedImage Optional.
		*/
		bool Init(const std::string& normalImage, const std::string& pressedImage, const glm::vec3& position, const Size& size = { 0, 0 });

		void HandleMessage(const Message& message) override;

		void Draw(const glm::mat4& modelViewMatrix, const int32 drawOrder, const uint32 flags) override;

	private:
		Material _material;
		QuadCommandBuffer _drawCmd;

		Texture2D* _normalTex;
		Texture2D* _pressedTex;
	};
}

NS_VG_END

#endif // __VGBUTTON_H__
