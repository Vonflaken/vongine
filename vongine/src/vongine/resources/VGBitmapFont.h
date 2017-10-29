#ifndef __VGBITMAPFONT_H__
#define __VGBITMAPFONT_H__

#include "VGMacros.h"
#include "VGFont.h"
#include "base/VGTypes.h"

#include <unordered_map>

NS_VG_BEGIN

class Texture2D;

namespace ui
{
	class DLLAPI BitmapFont : public Font
	{
	public:
		struct Character
		{
			uint32 x; // X location on the texture
			uint32 y; // Y location on the texture

			uint32 width; // Width of the character image
			uint32 height; // Height of the character image

			uint32 xOffset; // The X amount the image should be offset when drawing the character image
			uint32 yOffset; // The Y amount the image should be offset when drawing the character image

			uint32 xAdvance; // The amount to move the current position after drawing the character
		};

		BitmapFont();

		/**
		* Create Texture2D from font image file and store the characters info.
		* @param cfgFilename Font definition text file.
		*/
		virtual bool InitWithFilename(const std::string& cfgFilename);

		virtual uint32 BuildInterleavedVertsAndTexCoordsForText(const std::string& text, std::unique_ptr<float, VG_Free_Deleter>& interleavedVertsAndTexCoords, std::unique_ptr<uint32, VG_Free_Deleter>& indices, Texture2D const * tex, const uint32 fontSize) const;

		virtual float GetTextWidth(const std::string& text, const uint32 fontSize) const;

	private:
		void ParseCharacter(const std::string& line);
		void ParseKerningEntry(const std::string& line);
		void ParseCommonLine(const std::string& line);
		void ParseInfoLine(const std::string& line);

	private:
		std::unordered_map<uint8, Character> _characters;
		std::unordered_map<uint8, std::unordered_map<uint8, int32>> _kernings;
		uint32 _scaleW, _scaleH;
		uint32 _lineHeight;
		std::string _imgRelPath; // Relative dir + filename
	};
}

NS_VG_END

#endif // __VGBITMAPFONT_H__
