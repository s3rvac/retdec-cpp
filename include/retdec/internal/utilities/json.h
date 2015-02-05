///
/// @file      retdec/internal/utilities/json.h
/// @copyright (c) 2015 by Petr Zemek (s3rvac@gmail.com) and contributors
/// @license   MIT, see the @c LICENSE file for more details
/// @brief     Utilities for working with the JSON format.
///

#ifndef RETDEC_INTERNAL_UTILITIES_JSON_H
#define RETDEC_INTERNAL_UTILITIES_JSON_H

#include <json/json.h>
#include <string>

#include "retdec/exceptions.h"

namespace retdec {
namespace internal {

/// @name JSON
/// @{

///
/// Exception thrown when JSON decoding fails.
///
class JsonDecodingError: public Error {
public:
	JsonDecodingError(const std::string &formattedErrors);
};

Json::Value toJson(const std::string &str);

/// @}

} // namespace internal
} // namespace retdec

#endif
