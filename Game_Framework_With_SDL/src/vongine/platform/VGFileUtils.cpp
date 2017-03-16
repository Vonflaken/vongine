#include "VGFileUtils.h"
#include "base/VGCoreManager.h"

NS_VG_BEGIN

///////////////////////////////////////////////////////////////////////
/////////////////////////////////////////// File implementation
File::File()
: _filename("")
, _stream(nullptr, VG_SDL_Deleter())
, _buffer(nullptr, VG_Free_Deleter())
, _size(0)
{}

File::File(const std::string& filename, const char* mode)
: _buffer(nullptr, VG_Free_Deleter())
, _size(0)
{
	_filename = filename;

	// Open file stream
	OpenStream(mode);
}

void File::SetFilename(const std::string& filename)
{
	_filename = filename;
}

const char* File::Read()
{
	CoreManager::GetInstance().FileUtils()->Read(this);
}

void File::Write(const char* buffer, const uint32 size)
{
	CoreManager::GetInstance().FileUtils()->Write(this, buffer, size);
}

bool File::Exists()
{
	return OpenStream();
}

bool File::OpenStream(const char* mode)
{
	if (_filename.empty()) // Return false if filename is an empty string
		return false;

	if (_stream) // Return true if stream is already open
		return true;

	// Get full path to file
	std::string path = CoreManager::GetInstance().FileUtils()->GetFullPathOf(_filename);

	// Create file handler of filename with mode
	_stream = VG_SDL_CreateFileRWops(path.c_str(), mode);
	if (!_stream) // Error at trying to load the file
		return false;

	return true;
}

///////////////////////////////////////////////////////////////////////
/////////////////////////////////////////// FileUtils implementation
FileUtils::FileUtils()
: _resourcesPath("Resources/")
{}

/// Build a path from the root resources folder to the file provided
const std::string FileUtils::GetFullPathOf(const std::string& filename) const
{
	return _resourcesPath + filename;
}

void FileUtils::Read(File* file) const
{
	if (file->_buffer) // Exit if buffer is already filled
		return;

	if (file->OpenStream())
	{
		// Get file size
		uint32 size = SDL_RWsize(file->_stream.get());
		// Alloc enough mem to store file content
		char* buffer = (char*)malloc(size + 1);
		// Read in buffer
		SDL_RWread(file->_stream.get(), buffer, 1, size); // TODO: Add error handling
		// Put null char in end of buffer
		buffer[size] = '\0';

		// Set size in file object
		file->_size = size;
		// Set buffer in file object
		file->_buffer.reset(buffer);
	}
}

void FileUtils::Write(File* file, const char* buffer, const uint32 size) const
{
	if (file->OpenStream("w"))
	{
		SDL_RWwrite(file->_stream.get(), buffer, 1, size); // TODO: Add error handling
	}
}

NS_VG_END
