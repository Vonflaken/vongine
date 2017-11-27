#ifndef __VGBITMAPFONT_H__
#define __VGBITMAPFONT_H__

#include "VGMacros.h"
#include "VGFont.h"
#include "base/VGTypes.h"

#include <unordered_map>

NS_VG_BEGIN

/**
* This BMP font rendering class works for fonts created with BMFont app by AngelCode.
* DISCLAIMER: only supported the PNG version of the font image file.
* @url http://www.angelcode.com/products/bmfont/
*/
class DLLAPI BitmapFont : public Font
{
public:
	struct Character
	{
		uint32 x; // X location on the texture
		uint32 y; // Y location on the texture

		uint32 width; // Width of the character image
		uint32 height; // Height of the character image

		int32 xOffset; // The X amount the image should be offset when drawing the character image
		int32 yOffset; // The Y amount the image should be offset when drawing the character image

		uint32 xAdvance; // The amount to move the current position after drawing the character
	};

	BitmapFont();

	/**
	* Create Texture2D from font image file and store the characters info.
	* @param cfgFilename Font definition text file.
	*/
	bool InitWithFilename(const std::string& cfgFilename) override;

	uint32 BuildInterleavedVertsAndTexCoordsForText(const std::string& text, std::unique_ptr<float, utils::VG_Free_Deleter>& interleavedVertsAndTexCoords, std::unique_ptr<uint32, utils::VG_Free_Deleter>& indices, Texture2D const ** tex, const uint32 fontSize) const override;

	uint32 GetTextWidth(const std::string& text, const uint32 fontSize) const override;
	Texture2D* GetTexture() const override;

private:
	void ParseCharacter(const std::string& line);
	void ParseKerningEntry(const std::string& line);
	void ParseCommonLine(const std::string& line);
	void ParseInfoLine(const std::string& line);

	int32 FindKerningVal(const uint8 cfirst, const uint8 csecond) const;

private:
	std::unordered_map<uint8, Character> _characters;
	std::unordered_map<uint8, std::unordered_map<uint8, int32>> _kernings;
	uint32 _scaleW, _scaleH;
	uint32 _lineHeight;
	std::string _imgRelPath; // Relative dir + filename. Used as string key in Texture2D cache
	float _averageCharHeight; // Average of height among all chars in font
};

NS_VG_END

#endif // __VGBITMAPFONT_H__
