#ifndef __VGSPRITEANIMATION_H__
#define __VGSPRITEANIMATION_H__

#include "VGMacros.h"
#include "base/VGTypes.h"

#include <vector>
#include <memory>

NS_VG_BEGIN

typedef struct
{
	float u0, v0, u1, v1, u2, v2, u3, v3;
} UVRect;

class Sprite;

class DLLAPI SpriteAnimation
{
public:
	SpriteAnimation(const uint32 fps, std::unique_ptr<UVRect>& uvRects, const uint32 framesCount);

	/**
	* Set up properties for the upcoming playback of the animation.
	*/
	void Play(Sprite* sprite, const bool loop);
	void Stop() { _isPlaying = false; }

	bool IsPlaying() const { return _isPlaying; }

	/**
	* Call once per frame for updating animation state.
	* @return UVRect Frame that must be drawn this time.
	*/
	const UVRect& Update(const float deltaTime);

private:
	/**
	* @return bool Whereas or not was able to get the UVRect requested.
	*/
	bool GetUVRect(const uint32 index, UVRect* outUVRect) const;

private:
	uint32 _fps;
	std::unique_ptr<UVRect> _uvRects;
	uint32 _framesCount;
	uint32 _currentFrame;
	float _accumTime; // Helper to accumulate time
	bool _loop;
	bool _isPlaying;
	Sprite* _sprite;
	UVRect _originalUVFrame;
};

NS_VG_END

#endif // __VGSPRITEANIMATION_H__
