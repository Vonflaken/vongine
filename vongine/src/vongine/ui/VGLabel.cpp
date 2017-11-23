#include "VGLabel.h"
#include "base/VGCoreManager.h"
#include "resources/VGBitmapFont.h"
#include "rendering/VGVertexTypes.h"

NS_VG_BEGIN

namespace ui
{
	std::shared_ptr<Label> Label::Create(const std::string& text, const std::string& fontFilename, const uint32 fontSize)
	{
		return Label::Create(text, fontFilename, fontSize, glm::vec3(0.f, 0.f, 0.f));
	}

	std::shared_ptr<Label> Label::Create(const std::string& text, const std::string& fontFilename, const uint32 fontSize, const glm::vec3& position)
	{
		auto label = std::make_shared<Label>();
		if (label->Init(text, fontFilename, fontSize, position))
		{
			return label;
		}
		return nullptr;
	}

	Label::Label()
	: _font(nullptr)
	, _drawingDirty(false)
	, _fontSize(16)
	{}

	bool Label::Init(const std::string& text, const std::string& fontFilename, const uint32 fontSize, const glm::vec3& position)
	{
		if (Widget::Init(position, { 0, 0 }))
		{
			// Load font
			_font = CoreManager::GetInstance().ResourcesCache()->AddFont(fontFilename);
			if (_font) // Exists?
			{
				// Set font size
				SetFontSize(fontSize);
				// Set text string
				SetText(text);

				// Get shader program
				GLProgram* program = CoreManager::GetInstance().GLProgramCache()->GetProgram(GLProgramName::POSITIONTEXTURECOLOR_noMVP);
				if (program)
				{
					// Set properties
					SetTexture(_font->GetTexture());
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
					_drawCmd.Init();

					return true;
				}
			}
		}
		return false;
	}

	void Label::SetText(const std::string& newText)
	{
		_text = newText;
		UpdateSize();

		_drawingDirty = true;
	}

	void Label::SetFontSize(const uint32 size)
	{
		_fontSize = size;
		UpdateSize();
	}

	void Label::UpdateSize()
	{
		SetSize({ _font->GetTextWidth(_text, _fontSize), _fontSize });
	}

	void Label::Draw(const glm::mat4& modelViewMatrix, const int32 drawOrder, const uint32 flags)
	{
		bool drawingPropsWereUpdated = IsMaterialDirty();

		// Update drawing properties of the material
		ApplyToMaterial(&_material);

		// Draw order of sprites is based on Its z-distance to camera
		float widgetDrawOrder = (float)_order;

		if (drawingPropsWereUpdated || (flags & FLAG_TRANSFORM_DIRTY) || _drawingDirty)
		{
			_drawingDirty = false;

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

			std::unique_ptr<float, utils::VG_Free_Deleter> localPosAndCoords;
			std::unique_ptr<uint32, utils::VG_Free_Deleter> indices;
			Texture2D* tex = nullptr;
			_font->BuildInterleavedVertsAndTexCoordsForText(_text, localPosAndCoords, indices, &tex, _fontSize); // Get info for rendering text

			uint32 tempVertsBuffSize = sizeof(VERTEX_P3F_C4F_T2F) * 4 * _text.length(); // Size to alloc for all verts of each char quad
			std::unique_ptr<VERTEX_P3F_C4F_T2F, utils::VG_Free_Deleter> tempVertsBuff((VERTEX_P3F_C4F_T2F*)malloc(tempVertsBuffSize), utils::VG_Free_Deleter()); // Alloc mem for verts

			for (uint32 i = 0; i < _text.size(); i++) // Build quad per character in '_text' string
			{
				// Calculate verts positions
				float* charVertsPtr = localPosAndCoords.get() + i /* index offset */ * 4 * 4 /* 4 elements per vert by 4 verts */; // Ptr to the beginning of a chunk describing quad vertices
				glm::vec3 pos0 = modelViewMatrix * glm::vec4(*charVertsPtr, *(charVertsPtr + 1), 0.f, 1.f);
				glm::vec3 pos1 = modelViewMatrix * glm::vec4(*(charVertsPtr + 4), *(charVertsPtr + 5), 0.f, 1.f);
				glm::vec3 pos2 = modelViewMatrix * glm::vec4(*(charVertsPtr + 8), *(charVertsPtr + 9), 0.f, 1.f);
				glm::vec3 pos3 = modelViewMatrix * glm::vec4(*(charVertsPtr + 12), *(charVertsPtr + 13), 0.f, 1.f);

				// Set vertices to buffer				// Position				      // Color							  // UV
				*(tempVertsBuff.get() + i * 4) =		{ { pos0.x, pos0.y, pos0.z }, { rgba.r, rgba.g, rgba.b, rgba.a }, { *(charVertsPtr + 2), *(charVertsPtr + 3) } };
				*(tempVertsBuff.get() + i * 4 + 1) =	{ { pos1.x, pos1.y, pos1.z }, { rgba.r, rgba.g, rgba.b, rgba.a }, { *(charVertsPtr + 6), *(charVertsPtr + 7) } };
				*(tempVertsBuff.get() + i * 4 + 2) =	{ { pos2.x, pos2.y, pos2.z }, { rgba.r, rgba.g, rgba.b, rgba.a }, { *(charVertsPtr + 10), *(charVertsPtr + 11) } };
				*(tempVertsBuff.get() + i * 4 + 3) =	{ { pos3.x, pos3.y, pos3.z }, { rgba.r, rgba.g, rgba.b, rgba.a }, { *(charVertsPtr + 14), *(charVertsPtr + 15) } };
			}

			// Update draw command with changes in vertices
			_drawCmd.Update(modelViewMatrix, widgetDrawOrder, flags, &_material, tempVertsBuff.get(), tempVertsBuffSize, indices.get(), sizeof(uint32) * 6 /* indices per quad */ * _text.length() /* # of quads */);
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
