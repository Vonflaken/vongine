#include "VGFile.h"

NS_VG_BEGIN

std::string File::GetFullPathOfResource(const std::string& filename)
{
	return s_resourcesDirectory + filename;
}

File::File(const std::string& filename, const FileMode mode)
{
	std::string attr;
	switch (mode)
	{
	case FileMode::READ:
		attr = "rb";
		break;
	case FileMode::WRITE:
		attr = "wb";
		break;
	case FileMode::APPEND:
		attr = "ab";
		break;
	case FileMode::READ_WRITE:
		attr = "r+b";
		break;
	case FileMode::NEW_FILE_RW:
		attr = "w+b";
		break;
	}

	auto appPath = std::unique_ptr<char, VG_SDL_Free>(
		SDL_GetBasePath(), // Path to where app runs 
		SDL_free);
	// Build 'path to resources' string
	const char* resourcesFolder = "Resources/";
	char buff[128];
	snprintf(buff, 128, "%s%s", appPath.get(), resourcesFolder); // Concat
	s_resourcesDirectory = buff; // Assign value

	std::string filepath = File::GetFullPathOfResource(filename);

	_stream = VG_SDL_CreateFileRWops(filepath.c_str(), attr.c_str());

	_size = -1;
	if (_stream && mode == FileMode::READ)
	{
		_size = SDL_RWsize(_stream.get());
	}
}

bool File::IsOpen() const
{
	return _stream != nullptr;
}

void File::Close()
{
	_stream.reset(nullptr);
}

inline int64 File::Pos() const
{
	return SDL_RWtell(_stream.get());
}

void File::Seek(const uint64 offset)
{
	SDL_RWseek(_stream.get(), offset, RW_SEEK_SET);
}

bool File::ReadUInt8(uint8* const dst)
{
	*dst = SDL_ReadU8(_stream.get());
	return !Eof();
}

bool File::ReadUInt16(uint16* const dst)
{
	*dst = SDL_ReadLE16(_stream.get());
	return !Eof();
}

bool File::ReadUInt32(uint32* const dst)
{
	*dst = SDL_ReadLE32(_stream.get());
	return !Eof();
}

bool File::ReadUInt64(uint64* const dst)
{
	*dst = SDL_ReadLE64(_stream.get());
	return !Eof();
}

bool File::ReadFloat(float* const dst)
{
	return SDL_RWread(_stream.get(), dst, sizeof(float), 1);
}

bool File::ReadDouble(double* const dst)
{
	return SDL_RWread(_stream.get(), dst, sizeof(double), 1);
}

bool File::ReadCString(std::string& dst)
{
	unsigned char c;
	while (ReadUInt8(&c) && c != '\0')
	{
		dst += c;
	}
	
	return !Eof();
}

bool File::ReadCLine(std::string& str)
{
	std::string str;
	unsigned char c;
	while (ReadUInt8(&c) && c != '\r' && c != '\n') 
	{
		str += c;
	}

	if (c == '\r' && !Eof()) 
	{
		ReadUInt8(&c);
		if (c != '\n')
		{
			Seek(Pos() - 1);
		}
	}

	return !Eof();
}

uint32 File::ReadBytes(void* const dst, uint32 count)
{
	return SDL_RWread(_stream.get(), dst, 1, count);
}

uint32 File::WriteUInt8(const uint8 val)
{
	return SDL_WriteU8(_stream.get(), val);
}

uint32 File::WriteUInt16(const uint16 val)
{
	return SDL_WriteLE16(_stream.get(), val);
}

uint32 File::WriteUInt32(const uint32 val)
{
	return SDL_WriteLE32(_stream.get(), val);
}

uint32 File::WriteUInt64(const uint64 val)
{
	return SDL_WriteLE64(_stream.get(), val);
}

uint32 File::WriteFloat(float const * const src)
{
	return SDL_RWwrite(_stream.get(), src, sizeof(float), 1);
}

uint32 File::WriteDouble(double const * const src)
{
	return SDL_RWwrite(_stream.get(), src, sizeof(double), 1);
}

uint32 File::WriteCString(const std::string& val)
{
	return SDL_RWwrite(_stream.get(), val.c_str(), 1, val.length() + 1);
}

uint32 File::WriteCLine(const std::string& val)
{
	std::string line = val + "\r\n";
	return SDL_RWwrite(_stream.get(), line.c_str(), 1, line.length());
}

uint32 File::WriteBytes(void const * const src, uint32 count)
{
	return SDL_RWwrite(_stream.get(), src, 1, count);
}

NS_VG_END
