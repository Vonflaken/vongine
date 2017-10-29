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

	/**
	* Open file stream with given mode. All modes open file as binary.
	*/
	File(const std::string& filename, const FileMode mode);

	bool IsOpen() const;
	void Close();
	uint64 Size() const { return _size; }
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
	* Put read bytes in 'dst' buffer.
	* @return uint32 Number of objects read, or 0 at error or end of file.
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

