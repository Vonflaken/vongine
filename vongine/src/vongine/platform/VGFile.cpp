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

int64 File::Pos() const
{
	return SDL_RWtell(_stream.get());
}

void File::Seek(const uint64 offset)
{
	SDL_RWseek(_stream.get(), offset, RW_SEEK_SET);
}

uint8 File::ReadUInt8()
{
	return SDL_ReadU8(_stream.get());
}

uint16 File::ReadUInt16()
{
	return SDL_ReadLE16(_stream.get());
}

uint32 File::ReadUInt32()
{
	return SDL_ReadLE32(_stream.get());
}

uint64 File::ReadUInt64()
{
	return SDL_ReadLE64(_stream.get());
}

uint32 File::ReadFloat(float* const dst)
{
	return SDL_RWread(_stream.get(), dst, sizeof(float), 1);
}

uint32 File::ReadDouble(double* const dst)
{
	return SDL_RWread(_stream.get(), dst, sizeof(double), 1);
}

std::string File::ReadCString()
{
	std::string str;
	char c = ReadUInt8();
	while (c != 0)
	{
		str += c;
		c = ReadUInt8();
	}
	return str;
}

std::string File::ReadCLine()
{
	std::string str;
	char c = ReadUInt8();
	while (c != '\r' && c != '\n') 
	{
		str += c;
		if (!Eof())
		{
			c = ReadUInt8();
		}
		else 
		{
			break;
		}
	}
	if (c == '\r' && !Eof()) 
	{
		c = ReadUInt8();
		if (c != '\n')
		{
			Seek(Pos() - 1);
		}
	}
	return str;
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
