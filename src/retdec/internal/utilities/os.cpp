///
/// @file      retdec/internal/utilities/os.cpp
/// @copyright (c) 2015 by Petr Zemek (s3rvac@gmail.com) and contributors
/// @license   MIT, see the @c LICENSE file for more details
/// @brief     Implementation of the operating-system-related utilities.
///

#include <fstream>

#include <boost/date_time/posix_time/posix_time_types.hpp>
#include <boost/filesystem.hpp>
#include <boost/thread/thread.hpp>

#include "retdec/exceptions.h"
#include "retdec/internal/utilities/os.h"

using namespace std::string_literals;

namespace retdec {
namespace internal {

///
/// Returns a name of the operating system.
///
/// If the name cannot be determined, it returns @c "Unknown".
///
std::string operatingSystemName() {
#if defined(RETDEC_OS_WINDOWS)
	return "Windows";
#elif defined(RETDEC_OS_ANDROID)
	return "Android";
#elif defined(RETDEC_OS_LINUX)
	return "Linux";
#elif defined(RETDEC_OS_MACOS)
	return "MacOS";
#elif defined(RETDEC_OS_BSD)
	return "BSD";
#elif defined(RETDEC_OS_UNIX)
	return "UNIX";
#else
	return "Unknown";
#endif
}

///
/// Returns the file name from the given path.
///
/// @param[in] path Path to the file.
///
/// If there is no file name, it returns the empty string.
///
std::string fileNameFromPath(const std::string &path) {
	// For a path without a filename, boost::filesystem::path::filename()
	// returns ".", but we want to return the empty string in such a case.
	auto fileName = boost::filesystem::path(path).filename().string();
	return fileName != "." ? fileName : ""s;
}

///
/// Joins the given two paths.
///
std::string joinPaths(const std::string &path1, const std::string &path2) {
	boost::filesystem::path joined(path1);
	joined /= path2;
	return joined.string();
}

///
/// Returns the content of the given file.
///
/// @param[in] path Path to the file.
///
/// @throws FilesystemError When the file cannot be opened or read.
///
/// The file is opened in the binary mode, so no conversions are performed
/// during the reading.
///
std::string readFile(const std::string &path) {
	std::ifstream file(path, std::ios::in | std::ios::binary);
	if (!file) {
		throw FilesystemError("cannot open file \"" + path + "\"");
	}

	file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	std::string content;
	try {
		// The following method gets the file size, resizes the string holding
		// the content, and reads the file afterwards. The obtained file size
		// is reliable because we have opened the file in the binary mode, so
		// there are no conversions performed.
		file.seekg(0, std::ios::end);
		content.resize(file.tellg());
		file.seekg(0, std::ios::beg);
		file.read(&content[0], content.size());
	} catch (const std::ifstream::failure &) {
		throw FilesystemError("cannot read file \"" + path + "\"");
	}
	return content;
}

///
/// Stores a file with the given @a content into the given @a path.
///
/// @throws FilesystemError When the file cannot be opened or written.
///
/// The file is opened in the binary mode, so no conversions are performed
/// during writing.
///
void writeFile(const std::string &path, const std::string &content) {
	std::ofstream file(path, std::ios::out | std::ios::binary);
	if (!file) {
		throw FilesystemError("cannot open file \"" + path + "\"");
	}

	file << content;
	if (!file) {
		throw FilesystemError("cannot write file \"" + path + "\"");
	}
}

///
/// Copies file in @a srcPath to a file in @a dstPath.
///
/// @throws FilesystemError When a file cannot be opened, read, or written.
///
void copyFile(const std::string &srcPath, const std::string &dstPath) {
	try {
		boost::filesystem::copy_file(srcPath, dstPath,
			boost::filesystem::copy_option::overwrite_if_exists);
	} catch (const boost::filesystem::filesystem_error &) {
		throw FilesystemError("cannot copy file \"" + srcPath +
			"\" to \"" + dstPath + "\"");
	}
}

///
/// Sleeps for the given number of milliseconds.
///
void sleep(int milliseconds) {
	// Do not use std::this_thread::sleep_for() because <thread> is not
	// available in MinGW on Windows.
	boost::this_thread::sleep(boost::posix_time::milliseconds(milliseconds));
}

} // namespace internal
} // namespace retdec
