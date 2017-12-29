///
/// @file      retdec/exceptions.cpp
/// @copyright (c) 2015 by Petr Zemek (s3rvac@gmail.com) and contributors
/// @license   MIT, see the @c LICENSE file for more details
/// @brief     Implementation of the exceptions.
///

#include "retdec/exceptions.h"

namespace retdec {

///
/// Creates an exception.
///
/// @param[in] code Error code.
/// @param[in] message Short message describing the error.
/// @param[in] description Full description of the error.
///
ApiError::ApiError(int code, const std::string &message,
		const std::string &description):
	Error(std::to_string(code) + " " + message),
	code(code),
	message(message),
	description(description) {}

///
/// Returns the error code.
///
int ApiError::getCode() const noexcept {
	return code;
}

///
/// Returns a short message describing the error.
///
std::string ApiError::getMessage() const {
	return message;
}

///
/// Returns a full description of the error (if any).
///
/// If there is no description, it returns the same value as @c what().
///
std::string ApiError::getDescription() const {
	return !description.empty() ? description : what();
}

} // namespace retdec
