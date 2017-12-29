///
/// @file      retdec/internal/utilities/json.cpp
/// @copyright (c) 2015 by Petr Zemek (s3rvac@gmail.com) and contributors
/// @license   MIT, see the @c LICENSE file for more details
/// @brief     Implementation of the JSON utility functions.
///

#include "retdec/exceptions.h"
#include "retdec/internal/utilities/json.h"

namespace retdec {
namespace internal {

///
/// Creates an exception.
///
/// @param[in] formattedErrors Formatted error messages.
///
JsonDecodingError::JsonDecodingError(const std::string &formattedErrors):
	Error("JSON decoding failed: " + formattedErrors) {}

///
/// Decodes the given string into a JSON value.
///
/// @throws JsonDecodingError When the decoding fails, i.e. @a str is not valid
///                           JSON.
///
Json::Value toJson(const std::string &str) {
	Json::Value strAsJson;
	Json::Reader reader;
	bool parsingSuccessful = reader.parse(str, strAsJson);
	if (!parsingSuccessful) {
		throw JsonDecodingError(reader.getFormattedErrorMessages());
	}
	return strAsJson;
}

} // namespace internal
} // namespace retdec
