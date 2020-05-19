#ifndef __VGFONT_H__
#define __VGFONT_H__

#include "VGMacros.h"
#include "base/VGTypes.h"
#include "base/VGUtils.h"

#include <string>
#include <memory>

NS_VG_BEGIN

class Texture2D;

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
	* Return measures of text's bounding box.
	*/
	virtual uint32 GetTextWidth(const std::string& text, const uint32 fontSize) const = 0;

	/**
	* Set vertices xy position and texture coords data for rendering the text provided.
	* Allocate buffers for verts and indices, then buffers are binded to pointers provided.
	* Position and tex coords data are interleaved, that means consecutive blocks (stride) of 16 bytes contains 4+4 bytes xy and 4+4 bytes uv.
	* @param interleavedPosAndUVBufferDest Will be assigned a ptr to buffer of vertices.
	* @param indicesBufferDest Will be assigned a ptr to buffer of indices.
	* @param tex Will be assigned texture used to render the font.
	* @returns uint32 Indices count.
	*/
	virtual uint32 BuildInterleavedPosAndUVBufferForText(const std::string& text, std::unique_ptr<float,utils::VG_Free_Deleter>& interleavedPosAndUVBufferDest, std::unique_ptr<uint32,utils::VG_Free_Deleter>& indicesBufferDest, Texture2D const ** tex, const uint32 fontSize) const = 0;

	virtual Texture2D* GetTexture() const = 0;

	uint32 GetSize() const { return _size; }

protected:
	uint32 _size; // Font size.
};

NS_VG_END

#endif // __VGFONT_H__
