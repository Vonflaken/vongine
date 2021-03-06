#ifndef __VGTYPES_H__
#define __VGTYPES_H__

typedef signed char int8;
typedef signed short int16;
typedef signed int int32;
typedef signed long int64;
typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;
typedef unsigned long uint64;

/******************************** Color types */

struct Color3i 
{
	Color3i() : Color3i(255, 255, 255)
	{}
	Color3i(const uint8 red, const uint8 green, const uint8 blue)
	: r(red)
	, g(green)
	, b(blue)
	{}

	uint8 r;
	uint8 g;
	uint8 b;
};

struct Color3f
{
	Color3f() : Color3f(1.f, 1.f, 1.f)
	{}
	Color3f(const float red, const float green, const float blue)
	: r(red)
	, g(green)
	, b(blue)
	{}

	float r;
	float g;
	float b;
};

struct Color4i 
{
	Color4i() : Color4i(255, 255, 255, 255)
	{}
	Color4i(const uint8 red, const uint8 green, const uint8 blue, const uint8 alpha)
	: r(red)
	, g(green)
	, b(blue)
	, a(alpha)
	{}

	uint8 r;
	uint8 g;
	uint8 b;
	uint8 a;
};

struct Color4f
{
	Color4f() : Color4f(1.f, 1.f, 1.f, 1.f)
	{}
	Color4f(const float red, const float green, const float blue, const float alpha)
	: r(red)
	, g(green)
	, b(blue)
	, a(alpha)
	{}

	float r;
	float g;
	float b;
	float a;
};
/******************************** End color types */

struct Point
{
	Point() : Point(0.f, 0.f)
	{}

	Point(const float _x, const float _y)
	: x(_x)
	, y(_y)
	{}

	inline Point operator+(const Point& p) const
	{
		return { x + p.x, y + p.y };
	}

	inline Point operator-(const Point& p) const
	{
		return { x - p.x, y - p.y };
	}

	inline Point operator*(const float s) const
	{
		return { x * s, y * s };
	}

	inline Point operator/(const float s) const
	{
		return { x / s, y / s};
	}

	float x;
	float y;
};

struct Rect
{
	Rect() : Rect(0.f, 0.f, 0, 0)
	{}

	Rect(const float posx, const float posy, const uint32 w, const uint32 h)
	: x(posx), y(posy), width(w), height(h)
	{}

	bool IsPointInside(const Point& point) const
	{
		if (point.x >= x && point.x <= x + width && point.y >= y && point.y <= y + height)
			return true;

		return false;
	}

	inline bool operator==(const Rect& r) const { return x == r.x 
													&& y == r.y 
													&& width == r.width 
													&& height == r.height; }
	inline bool operator!=(const Rect& r) const { return !(*this == r); }

	float x;
	float y;
	uint32 width;
	uint32 height;
};

struct Size
{
	Size() : Size(0, 0)
	{}

	Size(const uint32 width, const uint32 height)
	: width(width)
	, height(height)
	{}

	/**
	* Whereas or not both width and height are zero.
	*/
	inline bool IsZero() const { return (width == 0 && height == 0); }

	uint32 width, height;
};

#endif // __VGTYPES_H__
