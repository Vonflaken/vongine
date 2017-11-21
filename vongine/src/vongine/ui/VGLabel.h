#ifndef __VGLABEL_H__
#define __VGLABEL_H__

#include "VGMacros.h"
#include "ui/VGWidget.h"
#include "rendering/VGMaterialProtocol.h"
#include "rendering/VGMaterial.h"
#include "rendering/VGCommandBuffer.h"

NS_VG_BEGIN

class Font;

namespace ui
{
	class DLLAPI Label : public Widget, public MaterialProtocol
	{
	public:
		static std::shared_ptr<Label> Create(const std::string& text, const std::string& fontFilename, const uint32 fontSize, const glm::vec3& position);

		Label();

		bool Init(const std::string& text, const std::string& fontFilename, const uint32 fontSize, const glm::vec3& position);

		/**
		* Set new text string to render and update size of the Widget.
		*/
		void SetText(const std::string& newText);
		/**
		* Sets font size for this Label.
		*/
		void SetFontSize(const uint32 size);

		void Draw(const glm::mat4& modelViewMatrix, const int32 drawOrder, const uint32 flags) override;

	private:
		/**
		* Calculate size of the Widget.
		*/
		void UpdateSize();

	private:
		std::string _text;
		Font* _font;
		uint32 _fontSize;

		Material _material;
		CommandBuffer _drawCmd;
		bool _drawingDirty; // Text changed this frame so have to update drawing buffers.
	};
}

NS_VG_END

#endif // __VGLABEL_H__
