///
/// @file      retdec/internal/utilities/string.cpp
/// @copyright (c) 2015-2016 by Petr Zemek (s3rvac@gmail.com) and contributors
/// @license   MIT, see the @c LICENSE file for more details
/// @brief     Implementation of the string utility functions.
///

#include <cctype>

#include "retdec/internal/utilities/string.h"

namespace retdec {
namespace internal {

///
/// Capitalizes all words in the given string.
///
/// Example:
/// @code
/// capitalizeWords("my name is jerry") // -> "My Name Is Jerry"
/// capitalizeWords("MY NAME IS JERRY") // -> "My Name Is Jerry"
/// @endcode
//
std::string capitalizeWords(std::string s) {
	bool capitalizeNext = true;
	for (auto &c : s) {
		if (std::isspace(c)) {
			capitalizeNext = true;
		} else if (std::isalpha(c)) {
			c = capitalizeNext ? std::toupper(c) : std::tolower(c);
			capitalizeNext = false;
		} else {
			capitalizeNext = false;
		}
	}
	return s;
}

} // namespace internal
} // namespace retdec
