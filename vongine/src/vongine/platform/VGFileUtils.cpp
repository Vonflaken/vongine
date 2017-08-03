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

const uint32 File::Read()
{
	return CoreManager::GetInstance().FileUtils()->Read(this);
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
	std::string path = CoreManager::GetInstance().FileUtils()->GetFullPathOfResource(_filename);

	// Create file handler of filename with mode
	_stream = VG_SDL_CreateFileRWops(path.c_str(), mode);
	if (!_stream) // Error at trying to load the file
	{
		VGLOG_ERROR("Error reading file: '%s'", SDL_GetError());
		return false;
	}

	return true;
}

///////////////////////////////////////////////////////////////////////
/////////////////////////////////////////// FileUtils implementation
FileUtils::FileUtils()
{
	auto appPath = std::unique_ptr<char, VG_SDL_Free>(
		SDL_GetBasePath(), // Path to where app runs 
		SDL_free);
	// Build 'path to resources' string
	const char* resourcesFolder = "Resources/";
	char buff[128];
	snprintf(buff, 128, "%s%s", appPath.get(), resourcesFolder); // Concat
	_resourcesPath = buff; // Assign value
}

/// Build a path from the root resources folder to the file provided
const std::string FileUtils::GetFullPathOfResource(const std::string& filename) const
{
	return _resourcesPath + filename;
}

const uint32 FileUtils::Read(File* file) const
{
	uint32 totalBytesRead = 0;

	if (file->_buffer) // Exit if buffer is already filled
		return file->GetSize();

	if (file->OpenStream())
	{
		// Get file size
		int64 size = SDL_RWsize(file->_stream.get());
		if (size >= 0)
		{
			// Alloc enough mem to store file content
			char* buffer = (char*)malloc(size + 1);
			// Read in buffer
			totalBytesRead = SDL_RWread(file->_stream.get(), buffer, 1, size); // TODO: Add error handling
			// Put null char in end of buffer
			buffer[size] = '\0';

			// Set size in file object
			file->_size = size;
			// Set buffer in file object
			file->_buffer.reset(buffer);
		}
		else // -1 (unknow) or error code
		{
			VGLOG_ERROR("Couldn't obtain file size: '%s'", SDL_GetError());
		}
	}

	return totalBytesRead;
}

void FileUtils::Write(File* file, const char* buffer, const uint32 size) const
{
	if (file->OpenStream("w"))
	{
		SDL_RWwrite(file->_stream.get(), buffer, 1, size); // TODO: Add error handling
	}
}

NS_VG_END
