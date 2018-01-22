#ifndef __VGSPRITEANIMATION_H__
#define __VGSPRITEANIMATION_H__

#include "VGMacros.h"
#include "base/VGTypes.h"
#include "base/VGUtils.h"

#include <vector>
#include <memory>
#include <functional>

NS_VG_BEGIN

typedef struct
{
	float u0, v0, u1, v1, u2, v2, u3, v3;
} UVRect;

class Sprite;

class DLLAPI SpriteAnimation
{
public:
	/**
	* Added to support std::pair which requires default ctor.
	*/
	SpriteAnimation() : SpriteAnimation(std::unique_ptr<UVRect, utils::VG_Free_Deleter>(nullptr), 0) {}
	/**
	* SpriteAnimation object will take ownership of "uvRects" ptr.
	*/
	SpriteAnimation(std::unique_ptr<UVRect, utils::VG_Free_Deleter>& uvRects, const uint32 framesCount);
	/**
	* Copy ctor.
	*/
	SpriteAnimation(const SpriteAnimation& other);

	/**
	* Assignment operator.
	*/
	SpriteAnimation& operator=(SpriteAnimation other);

	/**
	* Implement swap.
	*/
	friend void swap(SpriteAnimation& first, SpriteAnimation& second)
	{
		using std::swap;

		// Swap vars
		swap(first._uvRects, second._uvRects);
		swap(first._framesCount, second._framesCount);
		swap(first._fps, second._fps);
		swap(first._isPlaying, second._isPlaying);
		swap(first._loop, second._loop);
		swap(first._currentFrame, second._currentFrame);
		swap(first._originalUVFrame, second._originalUVFrame);
		swap(first._accumTime, second._accumTime);
		swap(first._sprite, second._sprite);
		swap(first._isBackwards, second._isBackwards);
		swap(first._finishedCallback, second._finishedCallback);
	}

	/**
	* Set up properties for the upcoming playback of the animation.
	* @param finishedCallback Function is called when animation finishes.
	*/
	void Play(Sprite* sprite, const bool loop, const bool playBackwards = false, const std::function<void(SpriteAnimation*)>& finishedCallback = nullptr, const uint32 fps = 24);
	void Stop() { _isPlaying = false; }

	bool IsPlaying() const { return _isPlaying; }

	/**
	* Call once per frame for updating animation state. Change uvFrame of Sprite asociated.
	* @return UVRect Frame that must be drawn this time.
	*/
	void Update(const float deltaTime);

	/**
	* Change UVRect of '_sprite' with related to 'frameId'.
	*/
	void DrawFrame(const uint32 frameId);

private:
	/**
	* @return bool Whereas or not was able to get the UVRect requested.
	*/
	bool GetUVRect(const uint32 index, UVRect* outUVRect) const;

private:
	uint32 _fps;
	std::unique_ptr<UVRect, utils::VG_Free_Deleter> _uvRects;
	uint32 _framesCount;
	int32 _currentFrame;
	float _accumTime; // Helper to accumulate time
	bool _loop;
	bool _isPlaying;
	Sprite* _sprite;
	UVRect _originalUVFrame;
	bool _isBackwards; // If true, animation will play backwards
	std::function<void(SpriteAnimation*)> _finishedCallback;
};

NS_VG_END

#endif // __VGSPRITEANIMATION_H__
