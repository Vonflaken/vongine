#include "VGSpriteAnimation.h"
#include "2d/VGSprite.h"

NS_VG_BEGIN

SpriteAnimation::SpriteAnimation(const uint32 fps, std::unique_ptr<UVRect>& uvRects, const uint32 framesCount)
: _framesCount(framesCount)
, _fps(fps)
, _uvRects(std::move(uvRects))
, _isPlaying(false)
, _loop(false)
, _currentFrame(0)
, _originalUVFrame({ 0.f })
, _accumTime(0.f)
{}

void SpriteAnimation::Play(Sprite* sprite, const bool loop)
{
	if (sprite)
	{
		// Set up
		_loop = loop;
		_sprite = sprite;
		_isPlaying = true;
		_currentFrame = 0;
		_originalUVFrame = sprite->GetUVFrame(); // Store current frame of Sprite so we can restore it when done
		_accumTime = 0.f;

		// Set first frame of animation 
		UVRect uvRect;
		if (GetUVRect(0, &uvRect))
			sprite->SetUVFrame(uvRect);
	}
}

const UVRect& SpriteAnimation::Update(const float deltaTime)
{
	// Return original frame by default
	UVRect retFrame = _originalUVFrame;
	// Keep updating while we are playing and has uv frames set
	if (_isPlaying && _uvRects)
	{
		_accumTime += deltaTime;

		if (_accumTime >= (1.f / _fps)/*window that a frame stays*/) // Is time to set next frame?
		{
			_accumTime = 0.f; // Reset

			_currentFrame++; // Advance one frame
			if (_currentFrame >= _framesCount)
			{
				// Animation reaches end
				if (_loop)
					_currentFrame = 0; // Start again if a loop anim
				else
				{
					Stop(); // Stop playing otherwise
					return retFrame;
				}
			}
			GetUVRect(_currentFrame, &retFrame); // Set new frame
		}
	}
	return retFrame;
}

bool SpriteAnimation::GetUVRect(const uint32 index, UVRect* outUVRect) const
{
	if (_uvRects && outUVRect && index < _framesCount)
	{
		UVRect* uvRectsPtr = _uvRects.get();
		*outUVRect = uvRectsPtr[index];
		return true;
	}
	return false;
}

NS_VG_END
