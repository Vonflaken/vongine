#include "VGSprite.h"
#include "base/VGCoreManager.h"
#include "resources/VGResourcesCache.h"
#include "rendering/VGTexture2D.h"
#include "rendering/VGMaterial.h"
#include "rendering/VGQuadCommandBuffer.h"
#include "rendering/VGGLProgramCache.h"
#include "rendering/VGGLProgram.h"
#include "rendering/VGVertexTypes.h"
#include "rendering/VGRenderer.h"
#include "rendering/VGCamera.h"
#include "physics/VGCircleSimple2DCollision.h"
#include "physics/VGRectSimple2DCollision.h"

NS_VG_BEGIN

using namespace glm;

typedef VERTEX_P3F_C4F_T2F SpriteVertexType;

std::vector<std::weak_ptr<Sprite>> Sprite::s_spritesWithCollision;

std::shared_ptr<Sprite> Sprite::Create(const std::string& filename)
{
	return Sprite::Create(filename, glm::vec3(0.f, 0.f, 0.f));
}

std::shared_ptr<Sprite> Sprite::Create(const std::string& filename, const glm::vec3& position)
{
	std::shared_ptr<Sprite> sprite = std::make_shared<Sprite>();
	if (sprite && sprite->Init(filename, position))
	{
		return sprite;
	}

	return nullptr;
}

std::shared_ptr<Sprite> Sprite::Create(const std::string& filename, const glm::vec3& position, const uint32 width, const uint32 height)
{
	std::shared_ptr<Sprite> sprite = std::make_shared<Sprite>();
	if (sprite && sprite->Init(filename, position, width, height))
	{
		return sprite;
	}

	return nullptr;
}

Sprite::Sprite()
: _width(0)
, _height(0)
, _simpleCollision(nullptr)
, _colRadius(0.f)
, _colBox(0, 0)
{}

bool Sprite::Init(const std::string& filename, const glm::vec3& position, const uint32 width, const uint32 height)
{
	if (Entity::Init(position))
	{
		uint32 setWidth = width;
		uint32 setHeight = height;

		// Get texture from file
		Texture2D* tex = CoreManager::GetInstance().ResourcesCache()->AddTexture(filename);
		// Get shader program
		GLProgram* program = CoreManager::GetInstance().GLProgramCache()->GetProgram(GLProgramName::POSITIONTEXTURECOLOR_noMVP);
		if (tex && program)
		{
			if (width == 0 && height == 0)
			{
				// Get size of sprite from texture
				setWidth = tex->GetWidth();
				setHeight = tex->GetHeight();
			}

			// Set properties
			SetWidth(setWidth);
			SetHeight(setHeight);
			SetTexture(tex);
			SetColor(255, 255, 255);
			SetOpacity(1.f);
			SetBlendingFunction(BlendFactor::SRC_ALPHA, BlendFactor::ONE_MINUS_SRC_ALPHA); // Alpha blending

			std::unique_ptr<GLUniform> texSampler(new GLUniform1i());
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

	return false;
}

void Sprite::Draw(const glm::mat4& modelViewMatrix, const int32 drawOrder, const uint32 flags)
{
	bool drawingPropsWereUpdated = IsMaterialDirty();

	// Update drawing properties of the material
	ApplyToMaterial(&_material);

	// Draw order of sprites is based on Its z-distance to camera
	float spriteDrawOrder = glm::distance(_position.z, Camera::s_renderingCamera->GetPosition().z);

	if (drawingPropsWereUpdated || (flags & FLAG_TRANSFORM_DIRTY))
	{		
		// Get color with alpha
		float alpha; Color3i color;
		_material.GetProperties(&alpha, &color, nullptr);
		Color4f rgba = { color.r / 255.f, color.g / 255.f, color.b / 255.f, alpha }; // Normalize rgb values
		
		/*******************************************************
		*	Sprite vertices
		*
		*	3  _____   2
		*	  |\     |			- Draws counterclockwise
		*	  |  \   |          - Draw order: 0, 1, 3, 1, 2, 3
		*	  |    \ |
		*	0  ------  1
		*
		********************************************************/
		float halfWidth = _width / 2.f;
		float halfHeight = _height / 2.f;

		// Transform positions in view space
		// Vertex 0 - bottom-left
		glm::vec4 pos0(-halfWidth, -halfHeight, 0.f, 1.f);
		pos0 = modelViewMatrix * pos0;
		// Vertex 1 - bottom-right
		glm::vec4 pos1(halfWidth, -halfHeight, 0.f, 1.f);
		pos1 = modelViewMatrix * pos1;
		// Vertex 2 - top-right
		glm::vec4 pos2(halfWidth, halfHeight, 0.f, 1.f);
		pos2 = modelViewMatrix * pos2;
		// Vertex 3 - top-left
		glm::vec4 pos3(-halfWidth, halfHeight, 0.f, 1.f);
		pos3 = modelViewMatrix * pos3;

		// Create temp buffer
		SpriteVertexType tempVertBuff[] = {
			// Position				   // Color						     // UV
			{{pos0.x, pos0.y, pos0.z}, {rgba.r, rgba.g, rgba.b, rgba.a}, {0.f, 0.f}}, 
			{{pos1.x, pos1.y, pos1.z}, {rgba.r, rgba.g, rgba.b, rgba.a}, {1.f, 0.f}}, 
			{{pos2.x, pos2.y, pos2.z}, {rgba.r, rgba.g, rgba.b, rgba.a}, {1.f, 1.f}}, 
			{{pos3.x, pos3.y, pos3.z}, {rgba.r, rgba.g, rgba.b, rgba.a}, {0.f, 1.f}}
		};

		// Update draw command with changes in vertices
		_drawCmd.Update(modelViewMatrix, spriteDrawOrder, flags, &_material, tempVertBuff, sizeof(tempVertBuff));
	}
	else
	{
		// Update draw command without changes in vertices
		_drawCmd.Update(modelViewMatrix, spriteDrawOrder, flags, &_material);
	}

	// Add render cmd to Renderer
	CoreManager::GetInstance().GetRenderer()->AddRenderCommand(&_drawCmd, RenderQueue::TRANSPARENT);
}

void Sprite::SetCollision(const Simple2DCollisionType colType)
{
	Point absPos = GetAbsolute2DPosition();

	switch (colType)
	{
	case Simple2DCollisionType::Circle:
	{
		float radius = GetColRadius();

		_simpleCollision.reset(new CircleSimple2DCollision(absPos.x, absPos.y, radius));
		// Add this Sprite to collision collection
		s_spritesWithCollision.push_back(std::static_pointer_cast<Sprite>(shared_from_this()));
		break;
	}
	case Simple2DCollisionType::Rect:
	{
		Size box = GetColBox();

		_simpleCollision.reset(new RectSimple2DCollision(absPos.x, absPos.y, box.width, box.height));
		break;
	}
	case Simple2DCollisionType::None:
	{
		_simpleCollision.reset(nullptr);
		// Remove this Sprite from collision collection
		for (auto it = s_spritesWithCollision.begin(); it != s_spritesWithCollision.end(); it++)
		{
			auto wptr = *it;
			if (!wptr.expired())
			{
				if (wptr.lock().get() == this)
				{
					s_spritesWithCollision.erase(it);
					break;
				}
			}
		}
		break;
	}
	}
}

bool Sprite::CheckCollision(Sprite* other)
{
	auto otherCol = other->GetCollision();
	if (otherCol && _simpleCollision) // Both have collision shape defined
	{
		// Update collision shape values before check
		UpdateCollisionShape();
		other->UpdateCollisionShape();

		if (_simpleCollision->DoesCollide(otherCol))
		{ // Did collide
			// Notify myself
			OnCollision(other);
			// Notify other
			other->OnCollision(this);

			return true;
		}
	}
	return false;
}

void Sprite::UpdateCollisionShape()
{
	Point absPos = GetAbsolute2DPosition();
	Size box = GetColBox();
	_simpleCollision->UpdateShape(absPos.x, absPos.y, box.width, box.height);
	float radius = GetColRadius();
	_simpleCollision->UpdateShape(absPos.x, absPos.y, radius);
}

Size Sprite::GetColBox() const
{
	Size box;
	if (_colBox.IsZero())
	{ // If a box shape is not defined, pick from Sprite size
		box.width = _width * _scale.x;
		box.height = _height * _scale.y;
	}
	else
		box = _colBox;
	return box;
}

float Sprite::GetColRadius() const
{
	float radius;
	if (_colRadius == 0.f) // If a radius is not defined, pick the largest axis of Sprite
		radius = max(_width * _scale.x, _height * _scale.y) / 2.f; 
	else
		radius = _colRadius;
	return radius;
}

NS_VG_END
