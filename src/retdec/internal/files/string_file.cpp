///
/// @file      retdec/internal/files/string_file.cpp
/// @copyright (c) 2015 by Petr Zemek (s3rvac@gmail.com) and contributors
/// @license   MIT, see the @c LICENSE file for more details
/// @brief     Implementation of the file storing its content in a string.
///

#include <utility>

#include "retdec/internal/files/string_file.h"
#include "retdec/internal/utilities/os.h"

namespace retdec {
namespace internal {

///
/// Constructs a file with the given content.
///
StringFile::StringFile(std::string content):
	content(std::move(content)) {}

///
/// Constructs a file with the given content and name.
///
StringFile::StringFile(std::string content, std::string name):
	content(std::move(content)), name(std::move(name)) {}

///
/// Destructs the file.
///
StringFile::~StringFile() = default;

// Override.
std::string StringFile::getName() const {
	return name;
}

// Override.
std::string StringFile::getContent() {
	return content;
}

// Override.
void StringFile::saveCopyTo(const std::string &directoryPath) {
	saveCopyTo(directoryPath, name);
}

// Override.
void StringFile::saveCopyTo(const std::string &directoryPath,
		const std::string &name) {
	writeFile(joinPaths(directoryPath, name), content);
}

} // namespace internal
} // namespace retdec
