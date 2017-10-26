#ifndef __VGFILE_H__
#define __VGFILE_H__

#include "VGMacros.h"
#include "base/VGTypes.h"

#include "VGSDL.h"

#include <string>
#include <memory>

NS_VG_BEGIN

enum class FileMode
{
	READ,
	WRITE,
	APPEND
};

class DLLAPI File
{
public:
	/**
	* Returns a valid system path pointing to the resource given.
	*/
	static std::string GetFullPathOfResource(const std::string& filename);

	/**
	* Open file stream with given mode. All modes open file as binary.
	*/
	File(const std::string& filename, const FileMode mode);

	bool IsOpen() const;
	void Close();
	uint64 Size() const { return _size; }
	int64 Pos() const;
	void Seek(const uint64 offset);
	bool Eof() const { return Pos() == _size; }

	uint8 ReadUInt8();
	uint16 ReadUInt16();
	uint32 ReadUInt32();
	uint64 ReadUInt64();
	/**
	* @return Number of objects read, or 0 at error or end of file.
	*/
	uint32 ReadFloat(float* const dst);
	/**
	* @return Number of objects read, or 0 at error or end of file.
	*/
	uint32 ReadDouble(double* const dst);
	std::string ReadCString();
	std::string ReadCLine();
	/**
	* @return Number of objects read, or 0 at error or end of file.
	*/
	uint32 ReadBytes(void* const dst, uint32 count);

	/**
	* @return 1 on successful write, 0 on error.
	*/
	uint32 WriteUInt8(const uint8 val);
	/**
	* @return 1 on successful write, 0 on error.
	*/
	uint32 WriteUInt16(const uint16 val);
	/**
	* @return 1 on successful write, 0 on error.
	*/
	uint32 WriteUInt32(const uint32 val);
	/**
	* @return 1 on successful write, 0 on error.
	*/
	uint32 WriteUInt64(const uint64 val);
	/**
	* @return Number of objects written, which will be less than num on error.
	*/
	uint32 WriteFloat(float const * const src);
	/**
	* @return Number of objects written, which will be less than num on error.
	*/
	uint32 WriteDouble(double const * const src);
	/**
	* @return Number of objects written, which will be less than num on error.
	*/
	uint32 WriteCString(const std::string& val);
	/**
	* @return Number of objects written, which will be less than num on error.
	*/
	uint32 WriteCLine(const std::string& val);
	/**
	* @return Number of objects written, which will be less than num on error.
	*/
	uint32 WriteBytes(void const * const src, uint32 count);

private:
	static std::string s_resourcesDirectory;

	std::unique_ptr<SDL_RWops, VG_SDL_Deleter> _stream; // SDL file stream
	int64 _size;
};

NS_VG_END

#endif // __VGFILE_H__

