#ifndef __VGFILEUTILS_H__
#define __VGFILEUTILS_H__

#include "VGMacros.h"
#include "base/VGUtils.h"

#include "VGSDL.h"

#include <string>
#include <memory>

NS_VG_BEGIN

// TODO: Reset stream mode on demand
/// Stream mode can't change once object is constructed for now
class DLLAPI File
{
	friend class FileUtils;

public:
	File();
	File(const std::string& filename, const char* mode);

	void SetFilename(const std::string& filename);

	/// Returns bytes read
	/// Cache file content and size in class props so next calls don't require extra work
	const uint32 Read();
	/// Writes buffer in file
	void Write(const char* buffer, const uint32 size);

	/// File exists if stream is open
	bool Exists();

	const char* GetBuffer() const { return _buffer.get(); }
	const uint32 GetSize() const { return _size; }

private:
	/// Call before do read/write ops on file
	/// Open a stream with the file
	/// Returns true if file is open and false if some error at loading file happened
	bool OpenStream(const char* mode = "rb");

private:
	std::string _filename;
	std::unique_ptr<SDL_RWops, VG_SDL_Deleter> _stream; // SDL file handler
	std::unique_ptr<char, VG_Free_Deleter> _buffer; // File content, null char terminated
	uint32 _size;
};


class DLLAPI FileUtils
{
public:
	FileUtils();

	/// Returns a path to the provided file
	const std::string GetFullPathOfResource(const std::string& filename) const;

	/// Populate File object with content of the actual file
	/// Returns bytes read
	const uint32 Read(File* file) const;
	void Write(File* file, const char* buffer, const uint32 size) const;

private:
	std::string _resourcesPath; /// Path to the folder where is located all game resources
};

NS_VG_END

#endif // __VGFILEUTILS_H__

