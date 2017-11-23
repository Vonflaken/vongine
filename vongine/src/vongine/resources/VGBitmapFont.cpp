#include "VGBitmapFont.h"
#include "resources/VGImage.h"
#include "base/VGCoreManager.h"
#include "resources/VGResourcesCache.h"
#include "base/VGUtils.h"
#include "platform/VGFile.h"
#include "rendering/VGTexture2D.h"

NS_VG_BEGIN

using namespace utils;

BitmapFont::BitmapFont()
: _scaleW(0)
, _scaleH(0)
, _lineHeight(0)
, _averageCharHeight(0.f)
{}

bool BitmapFont::InitWithFilename(const std::string& filename)
{
	bool isValid = false;

	// Read in the font data
	File inFile(filename, FileMode::READ);
	if (inFile.IsOpen())
	{
		std::string line;
		while (inFile.ReadCLine(line))
		{
			// Ignore these lines
			if (str_starts_with("chars c", line.c_str())) continue;
			if (str_starts_with("kernings count", line.c_str())) continue;

			if (str_starts_with("info", line.c_str()))
			{
				ParseInfoLine(line);
			}
			if (str_starts_with("common", line.c_str()))
			{
				ParseCommonLine(line);
			}
			if (str_starts_with("page", line.c_str()))
			{
				// Get related image filename
				std::string imgFilename;
				std::vector<std::string> components;
				str_split(line, '=', components);
				imgFilename = components[2];
				str_trim_char(imgFilename);

				// Get directory of font files
				std::string dir = str_extract_dir(filename);
				_imgRelPath = dir + imgFilename;

				// Create Texture resource from font image file
				CoreManager::GetInstance().ResourcesCache()->AddTexture(_imgRelPath);
			}
			// This is a character definition
			if (str_starts_with("char", line.c_str()))
			{
				ParseCharacter(line);
				continue;
			}
			// Kerning info
			if (str_starts_with("kerning first", line.c_str()))
			{
				ParseKerningEntry(line);
			}
		}

		// Returns true if data was parsed correctly
		isValid = !_characters.empty() && _scaleH != 0 && _scaleH != 0;
		if (isValid)
		{
			_averageCharHeight = _averageCharHeight /* accumulated heights at this point */ / _characters.size(); // Calculate the average height
		}
		// TODO: If not valid, remove texture from ResourceCache.
	}

	return isValid;
}

void BitmapFont::ParseCharacter(const std::string& line)
{
	std::vector<std::string> components;
	str_split(line, '=', components);
	uint8 charId = atoi(components[1].c_str());
	_characters[charId].x = atoi(components[2].c_str());
	_characters[charId].y = atoi(components[3].c_str());
	_characters[charId].width = atoi(components[4].c_str());
	_characters[charId].height = atoi(components[5].c_str());
	_characters[charId].xOffset = atoi(components[6].c_str());
	_characters[charId].yOffset = atoi(components[7].c_str());
	_characters[charId].xAdvance = atoi(components[8].c_str());

	// Accumulate all char heights
	_averageCharHeight += _characters[charId].height;
}

void BitmapFont::ParseKerningEntry(const std::string& line)
{
	std::vector<std::string> components;
	str_split(line, '=', components);

	uint8 firstChar = atoi(components[1].c_str());
	uint8 secondChar = atoi(components[2].c_str());
	_kernings[firstChar][secondChar] = atoi(components[3].c_str());
}

void BitmapFont::ParseCommonLine(const std::string& line)
{
	std::vector<std::string> components;
	str_split(line, '=', components);
	_lineHeight = atoi(components[1].c_str());
	_scaleW = atoi(components[3].c_str());
	_scaleH = atoi(components[4].c_str());
}

void BitmapFont::ParseInfoLine(const std::string& line)
{
	std::vector<std::string> components;
	str_split(line, '=', components);
	_size = atoi(components[2].c_str());
}

int32 BitmapFont::FindKerningVal(const uint8 cfirst, const uint8 csecond) const
{
	int32 kerningVal = 0;
	// Find kerning
	auto mapIt = _kernings.find(cfirst);
	if (mapIt != _kernings.end())
	{
		auto charIt = mapIt->second.find(csecond);
		if (charIt != mapIt->second.end())
		{
			kerningVal = charIt->second; // Return kerning
		}
	}
	return kerningVal;
}

typedef struct
{
	float vblx, vbly, tblx, tbly, vbrx, vbry, tbrx, tbry, vtrx, vtry, ttrx, ttry, vtlx, vtly, ttlx, ttly;
} FontQuad; // Holds xy position and tex coords of 4 vertices

#define MAKE_FONT_SQUARE(x1,y1,x2,y2, tx1,ty1,tx2,ty2) { \
(x1),(y1), (tx1),(ty1), \
(x2),(y1), (tx2),(ty1), \
(x2),(y2), (tx2),(ty2), \
(x1),(y2), (tx1),(ty2) \
}

uint32 BitmapFont::BuildInterleavedVertsAndTexCoordsForText(const std::string& text, std::unique_ptr<float, VG_Free_Deleter>& interleavedVertsAndTexCoords, std::unique_ptr<uint32, VG_Free_Deleter>& indices, Texture2D const ** tex, const uint32 fontSize) const
{
	float scale = fontSize / (float)_size;
		
	interleavedVertsAndTexCoords.reset((float*)malloc(sizeof(FontQuad) * text.size())); // Take ownership of allocated memory for storing font quads
	FontQuad* verticesPtr = (FontQuad*)interleavedVertsAndTexCoords.get();

	indices.reset((uint32*)malloc(sizeof(uint32) * text.size() * 6));
	uint32* indicesPtr = indices.get();

	uint32 index = 0;
	float x = 0.f;
	float y = _averageCharHeight; // Add some positive yOffset to centerize text in y-axis
	for (uint32 i = 0; i < text.size(); i++)
	{
		uint8 c = text[i];
		if (i > 0)
		{
			x += scale * (float)FindKerningVal(c, text[i - 1]);
		}
		const Character& cdef = _characters.at(c);
		FontQuad tmp = MAKE_FONT_SQUARE(x + cdef.xOffset * scale, y + scale * -((float)cdef.height + cdef.yOffset),
										x + scale * (cdef.xOffset + cdef.width), y + scale * -cdef.yOffset,
										(float)cdef.x / (float)_scaleW, 1.f - ((float)(cdef.y + cdef.height) / (float)_scaleH),
										(float)(cdef.x + cdef.width) / (float)_scaleW, 1.f - ((float)cdef.y / (float)_scaleH));
		verticesPtr[i] = tmp;
		x += scale * (float)cdef.xAdvance;

		indicesPtr[index] = i * 4;
		indicesPtr[index + 1] = i * 4 + 1;
		indicesPtr[index + 2] = i * 4 + 3;
		indicesPtr[index + 3] = i * 4 + 1;
		indicesPtr[index + 4] = i * 4 + 2;
		indicesPtr[index + 5] = i * 4 + 3;
		index += 6;
	}

	*tex = CoreManager::GetInstance().ResourcesCache()->AddTexture(_imgRelPath); // Get font texture

	return index;
}

uint32 BitmapFont::GetTextWidth(const std::string& text, const uint32 fontSize) const
{
	int32 x = 0;
	for (uint32 i = 0; i < text.size(); i++)
	{
		uint8 c = text[i];
		if (i > 0)
		{
			x += FindKerningVal(c, text[i - 1]);
		}
		const Character& cdef = _characters.at(c);
		// Special handling for last character
		if (i < text.size() - 1)
		{
			x += cdef.xAdvance;
		}
		else
		{
			x += cdef.xOffset + cdef.width;
		}
	}
	float scale = fontSize / (float)_size;
	return (uint32)(scale * x);
}

Texture2D* BitmapFont::GetTexture() const
{
	return CoreManager::GetInstance().ResourcesCache()->AddTexture(_imgRelPath);
}

NS_VG_END
