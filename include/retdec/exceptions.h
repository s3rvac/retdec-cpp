///
/// @file      retdec/exceptions.h
/// @copyright (c) 2015-2016 by Petr Zemek (s3rvac@gmail.com) and contributors
/// @license   MIT, see the @c LICENSE file for more details
/// @brief     Exceptions.
///

#ifndef RETDEC_EXCEPTIONS_H
#define RETDEC_EXCEPTIONS_H

#include <stdexcept>
#include <string>

namespace retdec {

///
/// Base class of custom exceptions thrown by the library.
///
class Error: public std::runtime_error {
public:
	using std::runtime_error::runtime_error;
};

///
/// Exception thrown when there is an I/O error.
///
class IoError: public Error {
public:
	using Error::Error;
};

///
/// Exception thrown when there is a filesystem error.
///
class FilesystemError: public IoError {
public:
	using IoError::IoError;
};

///
/// Exception thrown when there is a connection error.
///
class ConnectionError: public IoError {
public:
	using IoError::IoError;
};

///
/// Exception thrown when the API is used incorrectly.
///
class ApiError: public Error {
public:
	ApiError(int code, const std::string &message,
		const std::string &description = "");

	int getCode() const noexcept;
	std::string getMessage() const;
	std::string getDescription() const;

private:
	/// Error code.
	const int code;

	/// Short message describing the error.
	const std::string message;

	/// Full description of the error.
	const std::string description;
};

///
/// Base class of resource exceptions.
///
class ResourceError: public Error {
public:
	using Error::Error;
};

///
/// Exception thrown when a decompilation fails.
///
class DecompilationError: public ResourceError {
public:
	using ResourceError::ResourceError;
};

///
/// Exception thrown when an analysis fails.
///
class AnalysisError: public ResourceError {
public:
	using ResourceError::ResourceError;
};

} // namespace retdec

#endif
