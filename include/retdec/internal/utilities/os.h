///
/// @file      retdec/internal/utilities/os.h
/// @copyright (c) 2015-2016 by Petr Zemek (s3rvac@gmail.com) and contributors
/// @license   MIT, see the @c LICENSE file for more details
/// @brief     Operating-system-related utilities.
///

#ifndef RETDEC_INTERNAL_UTILITIES_OS_H
#define RETDEC_INTERNAL_UTILITIES_OS_H

#include <string>

// Obtain the used operating system.
// http://sourceforge.net/p/predef/wiki/OperatingSystems/
#if defined(_WIN32) || defined(_WIN64) || defined(__WIN32__) || defined(__WINDOWS__) || defined(__CYGWIN__)
	#define RETDEC_OS_WINDOWS
#elif defined(__ANDROID__)
	#define RETDEC_OS_ANDROID
#elif defined(__linux__)
	#define RETDEC_OS_LINUX
#elif defined(__APPLE__) || defined(__MACH__)
	#define RETDEC_OS_MACOS
#elif defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__)
	#define RETDEC_OS_BSD
#elif defined(__unix__) || defined(__unix)
	#define RETDEC_OS_UNIX
#endif

namespace retdec {
namespace internal {

/// @name Operating System
/// @{

std::string operatingSystemName();
std::string fileNameFromPath(const std::string &path);
std::string readFile(const std::string &path);
void writeFile(const std::string &path, const std::string &content);
void copyFile(const std::string &srcPath, const std::string &dstPath);
std::string joinPaths(const std::string &path1, const std::string &path2);

///
/// Joins the given paths.
///
template <typename... Paths>
inline std::string joinPaths(const std::string &path1, const std::string &path2,
		const Paths &... paths) {
	return joinPaths(path1, path2) + joinPaths(paths...);
}

void sleep(int milliseconds);

/// @}

} // namespace internal
} // namespace retdec

#endif
