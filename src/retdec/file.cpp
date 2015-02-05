///
/// @file      retdec/file.cpp
/// @copyright (c) 2015 by Petr Zemek (s3rvac@gmail.com) and contributors
/// @license   MIT, see the @c LICENSE file for more details
/// @brief     Implementation of the base class and factory of files.
///

#include "retdec/file.h"
#include "retdec/internal/files/filesystem_file.h"
#include "retdec/internal/files/string_file.h"
#include "retdec/internal/utilities/smart_ptr.h"

using namespace retdec::internal;

namespace retdec {

///
/// Constructs a file.
///
File::File() = default;

///
/// Destructs the file.
///
File::~File() = default;

/// @fn File::getName()
///
/// Returns the name of the file.
///
/// When the file has no name, it returns the empty string.
///

/// @fn File::getContent()
///
/// Returns the content of the file.
///

/// @fn File::saveCopyTo(const std::string &directoryPath)
///
/// Stores a copy of the file into the given directory.
///

/// @fn File::saveCopyTo(const std::string &directoryPath,
///     const std::string &name)
///
/// Stores a copy of the file into the given directory under the given name.
///

///
/// Returns a file containing the given content with the given name.
///
/// @param[in] content Content of the file.
/// @param[in] name Name of the file.
///
std::unique_ptr<File> File::fromContentWithName(const std::string &content,
		const std::string &name) {
	return make_unique<StringFile>(content, name);
}

///
/// Returns a file from the given path.
///
/// @param[in] path Path to the file.
///
/// The name of the file is obtained automatically.
///
std::unique_ptr<File> File::fromFilesystem(const std::string &path) {
	return make_unique<FilesystemFile>(path);
}

///
/// Returns a file from the given path, but with a custom name.
///
/// @param[in] path Path to the file.
/// @param[in] name Name to be used as the file's name.
///
/// Use this function only if you want to choose a different name for the file
/// than the one it already has.
///
std::unique_ptr<File> File::fromFilesystemWithOtherName(
		const std::string &path, const std::string &name) {
	return make_unique<FilesystemFile>(path, name);
}

} // namespace retdec
