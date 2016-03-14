///
/// @file      retdec/exceptions_tests.cpp
/// @copyright (c) 2015-2016 by Petr Zemek (s3rvac@gmail.com) and contributors
/// @license   MIT, see the @c LICENSE file for more details
/// @brief     Tests for the exceptions.
///

#include <gtest/gtest.h>

#include "retdec/exceptions.h"

using namespace testing;

namespace retdec {
namespace tests {

///
/// Tests for Error.
///
class ErrorTests: public Test {};

TEST_F(ErrorTests,
WhatReturnsCorrectMessage) {
	const std::string RefErrorMessage("error message");

	Error ex(RefErrorMessage);

	ASSERT_EQ(RefErrorMessage, ex.what());
}

///
/// Tests for IoError.
///
class IoErrorTests: public Test {};

TEST_F(IoErrorTests,
WhatReturnsCorrectMessage) {
	const std::string RefIoErrorMessage("error message");

	IoError ex(RefIoErrorMessage);

	ASSERT_EQ(RefIoErrorMessage, ex.what());
}

///
/// Tests for FilesystemError.
///
class FilesystemErrorTests: public Test {};

TEST_F(FilesystemErrorTests,
WhatReturnsCorrectMessage) {
	const std::string RefFilesystemErrorMessage("error message");

	FilesystemError ex(RefFilesystemErrorMessage);

	ASSERT_EQ(RefFilesystemErrorMessage, ex.what());
}

///
/// Tests for ConnectionError.
///
class ConnectionErrorTests: public Test {};

TEST_F(ConnectionErrorTests,
WhatReturnsCorrectMessage) {
	const std::string RefConnectionErrorMessage("error message");

	ConnectionError ex(RefConnectionErrorMessage);

	ASSERT_EQ(RefConnectionErrorMessage, ex.what());
}

///
/// Tests for ApiError.
///
class ApiErrorTests: public Test {};

TEST_F(ApiErrorTests,
GettersAndWhatReturnCorrectValuesWhenDescriptionIsGiven) {
	ApiError ex(404, "Not Found", "The page was not found.");

	ASSERT_STREQ("404 Not Found", ex.what());
	ASSERT_EQ(404, ex.getCode());
	ASSERT_EQ("Not Found", ex.getMessage());
	ASSERT_EQ("The page was not found.", ex.getDescription());
}

TEST_F(ApiErrorTests,
GetDescriptionReturnsSameValueAsWhatWhenDescriptionIsNotGiven) {
	ApiError e(404, "Not Found");

	ASSERT_EQ(e.what(), e.getDescription());
}

///
/// Tests for AuthError.
///
class AuthErrorTests: public Test {};

TEST_F(AuthErrorTests,
GettersAndWhatReturnCorrectValuesWhenDescriptionIsGiven) {
	AuthError ex(401, "Unauthorized by API Key", "API key authorization failed.");

	ASSERT_STREQ("401 Unauthorized by API Key", ex.what());
	ASSERT_EQ(401, ex.getCode());
	ASSERT_EQ("Unauthorized by API Key", ex.getMessage());
	ASSERT_EQ("API key authorization failed.", ex.getDescription());
}

TEST_F(AuthErrorTests,
GetDescriptionReturnsSameValueAsWhatWhenDescriptionIsNotGiven) {
	AuthError e(401, "Unauthorized by API Key");

	ASSERT_EQ(e.what(), e.getDescription());
}

///
/// Tests for DecompilationError.
///
class DecompilationErrorTests: public Test {};

TEST_F(DecompilationErrorTests,
WhatReturnsCorrectMessage) {
	const std::string RefDecompilationErrorMessage("error message");

	DecompilationError ex(RefDecompilationErrorMessage);

	ASSERT_EQ(RefDecompilationErrorMessage, ex.what());
}

///
/// Tests for AnalysisError.
///
class AnalysisErrorTests: public Test {};

TEST_F(AnalysisErrorTests,
WhatReturnsCorrectMessage) {
	const std::string RefAnalysisErrorMessage("error message");

	AnalysisError ex(RefAnalysisErrorMessage);

	ASSERT_EQ(RefAnalysisErrorMessage, ex.what());
}

} // namespace tests
} // namespace retdec
