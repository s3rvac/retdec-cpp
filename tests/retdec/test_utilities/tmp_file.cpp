///
/// @file      retdec/test_utilities/tmp_file.cpp
/// @copyright (c) 2015-2017 by Petr Zemek (s3rvac@gmail.com) and contributors
/// @license   MIT, see the @c LICENSE file for more details
/// @brief     Implementation of the temporary file utilities.
///

#include <fstream>
#include <memory>

#include <boost/filesystem.hpp>

#include "retdec/test_utilities/tmp_file.h"

namespace retdec {
namespace tests {

///
/// Private implementation of TmpFile.
///
struct TmpFile::Impl {
	/// Creates a temporary file with the given content.
	Impl(): path(boost::filesystem::unique_path()) {}

	/// Path to the temporary file.
	boost::filesystem::path path;
};

///
/// Creates a temporary file with the given content.
///
TmpFile::TmpFile(const std::string &content): impl(std::make_unique<Impl>()) {
	std::ofstream file(impl->path.native(), std::ios::out | std::ios::binary);
	file << content;
}

///
/// Destroys the temporary file by removing it.
///
TmpFile::~TmpFile() {
	boost::filesystem::remove(impl->path);
}

///
/// Returns a path to the file.
///
std::string TmpFile::getPath() const {
	return impl->path.native();
}

///
/// Creates a temporary file with the given content.
///
std::unique_ptr<TmpFile> TmpFile::createWithContent(const std::string &content) {
	return std::unique_ptr<TmpFile>(new TmpFile(content));
}

RemoveFileOnDestruction::RemoveFileOnDestruction(const std::string &path):
	path(path) {}

RemoveFileOnDestruction::~RemoveFileOnDestruction() {
	boost::filesystem::remove(path);
}

} // namespace tests
} // namespace retdec
