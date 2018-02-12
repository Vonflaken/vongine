#ifndef __VGFILE_H__
#define __VGFILE_H__

#include "VGMacros.h"
#include "base/VGTypes.h"

#include "VGSDL.h"

#include <string>
#include <memory>

NS_VG_BEGIN

/**
* Reference to SDL file modes.
* @link https://wiki.libsdl.org/SDL_RWFromFile?highlight=%28%5CbCategoryIO%5Cb%29%7C%28CategoryEnum%29%7C%28CategoryStruct%29
*/
enum class FileMode
{
	READ,
	WRITE,
	APPEND, 
	READ_WRITE, 
	NEW_FILE_RW
};

class DLLAPI File
{
public:
	/**
	* Returns a valid system path pointing to the resource given.
	*/
	static std::string GetFullPathOfResource(const std::string& filename);

	static bool Exists(const std::string& filename);

	/**
	* Open file stream with given mode. All modes open file as binary.
	*/
	File(const std::string& filename, const FileMode mode);

	bool IsOpen() const;
	void Close();
	/**
	* @return int64 Size of the file on success, -1 if unknown or a negative SDL error code.
	*/
	int64 Size() const { return _size; }
	inline int64 Pos() const;
	void Seek(const uint64 offset);
	inline bool Eof() const { return Pos() == _size; }

	/**
	* Put read uint8 in 'dst'.
	* @return bool Whereas or not file didn't reach eof.
	*/
	bool ReadUInt8(uint8* const dst);
	/**
	* Put read uint16 in 'dst'.
	* @return bool Whereas or not file didn't reach eof.
	*/
	bool ReadUInt16(uint16* const dst);
	/**
	* Put read uint32 in 'dst'.
	* @return bool Whereas or not file didn't reach eof.
	*/
	bool ReadUInt32(uint32* const dst);
	/**
	* Put read uint64 in 'dst'.
	* @return bool Whereas or not file didn't reach eof.
	*/
	bool ReadUInt64(uint64* const dst);
	/**
	* Put read float in 'dst'.
	* @return bool Number of objects read, or 0 at error or end of file.
	*/
	bool ReadFloat(float* const dst);
	/**
	* Put read double in 'dst'.
	* @return bool Whereas or not file didn't reach eof.
	*/
	bool ReadDouble(double* const dst);
	/**
	* Put read string in 'dst'. 
	* @return bool Whereas or not file didn't reach eof.
	*/
	bool ReadCString(std::string& dst);
	/**
	* Put read line in 'dst' string.
	* @return bool Whereas or not file didn't reach eof.
	*/
	bool ReadCLine(std::string& dst);
	/**
	* Read 'count' number of bytes is guaranteed at least error pops or eof reaches.
	* @param dst Content read.
	* @return int64 Number of objects read, or 0 at error or end of file.
	*/
	int64 ReadBytes(void* const dst, int64 count);

	/**
	* @return bool Whereas or no write was successful.
	*/
	bool WriteUInt8(const uint8 val);
	/**
	* @return bool Whereas or no write was successful.
	*/
	bool WriteUInt16(const uint16 val);
	/**
	* @return bool Whereas or no write was successful.
	*/
	bool WriteUInt32(const uint32 val);
	/**
	* @return bool Whereas or no write was successful.
	*/
	bool WriteUInt64(const uint64 val);
	/**
	* @return bool Whereas or no write was successful.
	*/
	bool WriteFloat(float const * const src);
	/**
	* @return bool Whereas or no write was successful.
	*/
	bool WriteDouble(double const * const src);
	/**
	* @return bool Whereas or no write was successful.
	*/
	bool WriteCString(const std::string& val);
	/**
	* @return bool Whereas or no write was successful.
	*/
	bool WriteCLine(const std::string& val);
	/**
	* Call SDL_GetError() for more information on error.
	* @return int64 Number of bytes written, which will be less than count on error.
	*/
	uint32 WriteBytes(void const * const src, uint32 count);

private:
	static std::string s_resourcesDirectory;

	std::unique_ptr<SDL_RWops, VG_SDL_Deleter> _stream; // SDL file stream
	int64 _size;
};

NS_VG_END

#endif // __VGFILE_H__

