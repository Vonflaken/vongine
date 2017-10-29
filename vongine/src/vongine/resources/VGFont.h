#ifndef __VGFONT_H__
#define __VGFONT_H__

#include "VGMacros.h"
#include "base/VGTypes.h"
#include "base/VGUtils.h"

#include <string>
#include <memory>

NS_VG_BEGIN

using namespace utils;

namespace ui
{
	class DLLAPI Font
	{
	public:
		Font() : _size(0) {}
		virtual ~Font() {}

		/**
		* Load font file and creates a texture with the info.
		*/
		virtual bool InitWithFilename(const std::string& filename) = 0;

		/**
		* Returns measures of text from size of chars in texture of the font.
		*/
		virtual float GetTextWidth(const std::string& text, const uint32 fontSize) const = 0;

		/**
		* Set vertices xy position and texture coords data for rendering the text provided.
		* Allocate buffers for verts and indices, then buffers are binded to pointers provided.
		* Position and tex coords data are interleaved, that means consecutive blocks of 16 bytes contains 4+4 bytes xy and 4+4 bytes uv.
		* @returns Indices count.
		*/
		virtual uint32 BuildInterleavedVertsAndTexCoordsForText(const std::string& text, std::unique_ptr<float, VG_Free_Deleter>& interleavedVertsAndTexCoords, std::unique_ptr<uint32, VG_Free_Deleter>& indices, const uint32 fontSize) const = 0;

		uint32 GetSize() const { return _size; }

	protected:
		uint32 _size; // Font size
	};
}

NS_VG_END

#endif // __VGFONT_H__
