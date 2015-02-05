///
/// @file      retdec/internal/utilities/os.h
/// @copyright (c) 2015 by Petr Zemek (s3rvac@gmail.com) and contributors
/// @license   MIT, see the @c LICENSE file for more details
/// @brief     Operating-system-related utilities.
///

#ifndef RETDEC_INTERNAL_UTILITIES_OS_H
#define RETDEC_INTERNAL_UTILITIES_OS_H

#include <string>

// Obtain the used operating system. Currently, we only distinguish between "MS
// Windows" and "other operating systems".
#if defined(__WIN) || defined(_WIN32) || defined(__WIN32__) || defined(__CYGWIN__)
	#define RETDEC_OS_WINDOWS
#endif

namespace retdec {
namespace internal {

/// @name Operating System
/// @{

std::string fileNameFromPath(const std::string &path);
std::string readFile(const std::string &path);
void writeFile(const std::string &path, const std::string &content);
void copyFile(const std::string &srcPath, const std::string &dstPath);
std::string joinPaths(const std::string &path);
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
