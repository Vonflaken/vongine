#include "VGButton.h"
#include "base/VGCoreManager.h"
#include "rendering/VGVertexTypes.h"
#include "ui/VGUIMessages.h"

NS_VG_BEGIN

namespace ui
{
	std::shared_ptr<Button> Button::Create(const std::string& normalImage, const std::string& pressedImage)
	{
		return Button::Create(normalImage, pressedImage, glm::vec3(0.f, 0.f, 0.f));
	}

	std::shared_ptr<Button> Button::Create(const std::string& normalImage, const std::string& pressedImage, const glm::vec3& position)
	{
		return Button::Create(normalImage, pressedImage, position, { 0, 0 });
	}

	std::shared_ptr<Button> Button::Create(const std::string& normalImage, const std::string& pressedImage, const glm::vec3& position, const Size& size)
	{
		auto button = std::make_shared<Button>();
		if (button->Init(normalImage, pressedImage, position, size))
		{
			return button;
		}

		return nullptr;
	}

	Button::Button()
	: _normalTex(nullptr)		
	, _pressedTex(nullptr)
	{}

	bool Button::Init(const std::string& normalImage, const std::string& pressedImage, const glm::vec3& position, const Size& size)
	{
		if (Widget::Init(position, size))
		{
			uint32 setWidth = size.width;
			uint32 setHeight = size.height;

			// Load "normal" texture from file
			_normalTex = CoreManager::GetInstance().ResourcesCache()->AddTexture(normalImage);
			if (_normalTex) // Normal image is mandatory
			{
				// Load "pressed" texture from file
				_pressedTex = CoreManager::GetInstance().ResourcesCache()->AddTexture(pressedImage);
				// Get shader program
				GLProgram* program = CoreManager::GetInstance().GLProgramCache()->GetProgram(GLProgramName::POSITIONTEXTURECOLOR_noMVP);
				if (_normalTex && program)
				{
					if (size.width == 0 && size.height == 0)
					{ // User didn't provide size
						// Get size of button from texture
						setWidth = _normalTex->GetWidth();
						setHeight = _normalTex->GetHeight();
					}

					// Set properties
					SetSize({ setWidth, setHeight });
					SetTexture(_normalTex);
					SetColor(255, 255, 255);
					SetOpacity(1.f);
					SetBlendingFunction(BlendFactor::SRC_ALPHA, BlendFactor::ONE_MINUS_SRC_ALPHA); // Alpha blending

					std::unique_ptr<GLUniform> texSampler = std::make_unique<GLUniform1i>();
					texSampler->name = "u_texture";
					((GLUniform1i*)texSampler.get())->value = 0;
					_material.InitWithUniforms(&texSampler, 1); // Add texture sampler

					// Copy drawing properties to material
					ApplyToMaterial(&_material);

					_material.SetIsTransparent(true);
					_material.SetProgram(program);

					// Initialize draw command
					_drawCmd.InitWithStride(program->State().GetStride());

					return true;
				}
			}
		}
		return false;
	}

	void Button::HandleMessage(const Message& message)
	{
		switch (message.type)
		{
		case MessageType::MouseButtonDown:
		{
			// Set pressed texture if exists
			if (_pressedTex)
				SetTexture(_pressedTex);
			break;
		}
		case MessageType::PointerHoverOut:
		case MessageType::MouseButtonUp:
		{
			SetTexture(_normalTex);
			break;
		}
		}
	}

	void Button::Draw(const glm::mat4& modelViewMatrix, const int32 drawOrder, const uint32 flags)
	{
		bool drawingPropsWereUpdated = IsMaterialDirty();

		// Update drawing properties of the material
		ApplyToMaterial(&_material);

		// Draw order of sprites is based on Its z-distance to camera
		float widgetDrawOrder = (float)_order;

		if (drawingPropsWereUpdated || (flags & FLAG_TRANSFORM_DIRTY))
		{
			// Get color with alpha
			float alpha; Color3i color;
			_material.GetProperties(&alpha, &color, nullptr);
			Color4f rgba = { color.r / 255.f, color.g / 255.f, color.b / 255.f, alpha }; // Normalize rgb values

			/*******************************************************
			*	Widget vertices
			*
			*	3  _____   2
			*	  |\     |			- Draws counterclockwise
			*	  |  \   |          - Draw order: 0, 1, 3, 1, 2, 3
			*	  |    \ |
			*	0  ------  1
			*
			********************************************************/

			// Transform positions in view space
			// Origin is at bottom-left (vert 0)
			// Vertex 0 - bottom-left
			glm::vec4 pos0(0.f, 0.f, 0.f, 1.f);
			pos0 = modelViewMatrix * pos0;
			// Vertex 1 - bottom-right
			glm::vec4 pos1(_size.width, 0.f, 0.f, 1.f);
			pos1 = modelViewMatrix * pos1;
			// Vertex 2 - top-right
			glm::vec4 pos2(_size.width, _size.height, 0.f, 1.f);
			pos2 = modelViewMatrix * pos2;
			// Vertex 3 - top-left
			glm::vec4 pos3(0.f, _size.height, 0.f, 1.f);
			pos3 = modelViewMatrix * pos3;

			// Create temp buffer
			VERTEX_P3F_C4F_T2F tempVertBuff[] = {
				// Position				   // Color						     // UV
				{ { pos0.x, pos0.y, pos0.z },{ rgba.r, rgba.g, rgba.b, rgba.a },{ 0.f, 0.f } },
				{ { pos1.x, pos1.y, pos1.z },{ rgba.r, rgba.g, rgba.b, rgba.a },{ 1.f, 0.f } },
				{ { pos2.x, pos2.y, pos2.z },{ rgba.r, rgba.g, rgba.b, rgba.a },{ 1.f, 1.f } },
				{ { pos3.x, pos3.y, pos3.z },{ rgba.r, rgba.g, rgba.b, rgba.a },{ 0.f, 1.f } }
			};

			// Update draw command with changes in vertices
			_drawCmd.Update(modelViewMatrix, widgetDrawOrder, flags, &_material, tempVertBuff, sizeof(tempVertBuff));
		}
		else
		{
			// Update draw command without changes in vertices
			_drawCmd.Update(modelViewMatrix, widgetDrawOrder, flags, &_material);
		}

		// Add render cmd to Renderer
		CoreManager::GetInstance().GetRenderer()->AddRenderCommand(&_drawCmd, RenderQueue::TRANSPARENT);
	}
}

NS_VG_END
