#include "VGSpriteAnimation.h"
#include "2d/VGSprite.h"

NS_VG_BEGIN

SpriteAnimation::SpriteAnimation(std::unique_ptr<UVRect, utils::VG_Free_Deleter>& uvRects, const uint32 framesCount)
: _framesCount(framesCount)
, _fps(24)
, _uvRects(std::move(uvRects))
, _isPlaying(false)
, _loop(false)
, _currentFrame(0)
, _originalUVFrame({ 0.f })
, _accumTime(0.f)
, _sprite(nullptr)
, _isBackwards(false)
, _finishedCallback(nullptr)
{}

SpriteAnimation::SpriteAnimation(const SpriteAnimation& other)
{
	UVRect* uvRectsPtr = nullptr;
	if (other._uvRects)
	{
		// Recreate '_uvRects' from 'other'
		uint32 allocSize = sizeof(UVRect) * other._framesCount;
		uvRectsPtr = (UVRect*)malloc(allocSize); // Alloc mem
		UVRect* otherUVRectsPtr = other._uvRects.get();
		memcpy(uvRectsPtr, otherUVRectsPtr, allocSize); // Copy mem
	}
	// Set vars
	_uvRects = std::unique_ptr<UVRect, utils::VG_Free_Deleter>(uvRectsPtr);
	_framesCount = other._framesCount;
	_fps = other._fps;
	_isPlaying = other._isPlaying;
	_loop = other._loop;
	_currentFrame = other._currentFrame;
	_originalUVFrame = other._originalUVFrame;
	_accumTime = other._accumTime;
	_sprite = other._sprite;
	_isBackwards = other._isBackwards;
	_finishedCallback = other._finishedCallback;
}

SpriteAnimation& SpriteAnimation::operator=(SpriteAnimation other)
{
	SpriteAnimation temp(other);
	swap(*this, temp);

	return *this;
}

void SpriteAnimation::Play(Sprite* sprite, const bool loop, const bool playBackwards, const std::function<void(SpriteAnimation*)>& finishedCallback, const uint32 fps)
{
	if (sprite)
	{
		// Set up
		_loop = loop;
		_sprite = sprite;
		_fps = fps;
		_isBackwards = playBackwards;
		_finishedCallback = finishedCallback;
		_isPlaying = true;
		_currentFrame = 0;
		_originalUVFrame = sprite->GetUVFrame(); // Store current frame of Sprite so we can restore it when done
		_accumTime = 0.f;

		uint32 startFrameId = (playBackwards) ? _framesCount - 1/*last*/ : 0;
		// Set first frame of animation 
		UVRect uvRect;
		if (GetUVRect(startFrameId, &uvRect))
			sprite->SetUVFrame(uvRect);
	}
}

void SpriteAnimation::Update(const float deltaTime)
{
	// Keep updating while we are playing and has uv frames set
	if (_isPlaying && _uvRects)
	{
		// Set original frame by default
		UVRect retFrame = _originalUVFrame;

		_accumTime += deltaTime;		

		if (_accumTime >= (1.f / _fps)/*time during which a frame stays*/) // Is time to set next frame?
		{
			_accumTime = 0.f; // Reset
			
			// Move next frame
			if (!_isBackwards)
				_currentFrame++;
			else
				_currentFrame--;

			if ((!_isBackwards && _currentFrame >= _framesCount) 
				|| (_isBackwards && _currentFrame < 0))
			{
				// Animation reaches end
				if (_loop) // Keep looping
					_currentFrame = (_isBackwards) ? _framesCount - 1/*last*/ : 0; // Start again if a loop anim
				else // Stop playback otherwise
					Stop();
			}						
		}
		// If animations ends and doesn't loop, 
		// 'retFrame' will remain unchanged due to '_currentFrame' value is out of bounds
		// so Sprite will recover its pre-anim state.
		GetUVRect(_currentFrame, &retFrame);

		if (_sprite)
			_sprite->SetUVFrame(retFrame); // Set new frame

		if (!_isPlaying) // Trigger callback if animation just finished
		{
			if (_finishedCallback)
				_finishedCallback(this);
		}
	}
}

void SpriteAnimation::DrawFrame(const uint32 frameId)
{
	if (_sprite && frameId < _framesCount) // Check out of bounds
	{
		UVRect uvRect;
		if (GetUVRect(frameId, &uvRect))
		{
			_sprite->SetUVFrame(uvRect);
		}
	}
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
