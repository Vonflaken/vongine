#include "VGMathExtension.h"

NS_VG_BEGIN

namespace mathex
{
	void ClosestPointToRect(const float x, const float y, const float rectx, const float recty, const float width, const float height, float* const outx, float* const outy) 
	{
		if (outx) *outx = (x < rectx) ? rectx : (x > rectx + width) ? rectx + width : x;
		if (outy) *outy = (y < recty) ? recty : (y > recty + height) ? recty + height : y;
	}

	bool RectsOverlap(const float x1, const float y1, const float width1, const float height1, const float x2, const float y2, const float width2, const float height2) 
	{
		if ((ValueInRange(x1, x2, x2 + width2) || ValueInRange(x2, x1, x1 + width1)) &&
			(ValueInRange(y1, y2, y2 + height2) || ValueInRange(y2, y1, y1 + height1)))
		{
			return true;
		}
		return false;
	}
}

NS_VG_END
