///
/// @file      retdec/internal/files/filesystem_file.cpp
/// @copyright (c) 2015-2016 by Petr Zemek (s3rvac@gmail.com) and contributors
/// @license   MIT, see the @c LICENSE file for more details
/// @brief     Implementation of the file stored in a filesystem.
///

#include "retdec/internal/files/filesystem_file.h"
#include "retdec/internal/utilities/os.h"

namespace retdec {
namespace internal {

///
/// Constructs a file.
///
/// @param[in] path Path to the file in a filesystem.
///
FilesystemFile::FilesystemFile(const std::string &path):
	path(path), name(fileNameFromPath(path)) {}

///
/// Constructs a file with a custom name.
///
/// @param[in] path Path to the file in a filesystem.
/// @param[in] name Name to be used as the file's name.
///
/// @par Preconditions
/// - @a name is non-empty
///
FilesystemFile::FilesystemFile(std::string path, std::string name):
	path(std::move(path)), name(std::move(name)) {}

///
/// Destructs the file.
///
FilesystemFile::~FilesystemFile() = default;

// Override.
std::string FilesystemFile::getName() const {
	return name;
}

// Override.
std::string FilesystemFile::getContent() {
	return readFile(path);
}

// Override.
void FilesystemFile::saveCopyTo(const std::string &directoryPath) {
	saveCopyTo(directoryPath, name);
}

// Override.
void FilesystemFile::saveCopyTo(const std::string &directoryPath,
		const std::string &name) {
	copyFile(path, joinPaths(directoryPath, name));
}

} // namespace internal
} // namespace retdec
