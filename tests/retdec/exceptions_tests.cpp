///
/// @file      retdec/exceptions_tests.cpp
/// @copyright (c) 2015 by Petr Zemek (s3rvac@gmail.com) and contributors
/// @license   MIT, see the @c LICENSE file for more details
/// @brief     Tests for the decompilation.
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
	EXPECT_EQ(RefErrorMessage, ex.what());
}

///
/// Tests for IoError.
///
class IoErrorTests: public Test {};

TEST_F(IoErrorTests,
WhatReturnsCorrectMessage) {
	const std::string RefIoErrorMessage("error message");
	IoError ex(RefIoErrorMessage);
	EXPECT_EQ(RefIoErrorMessage, ex.what());
}

///
/// Tests for FilesystemError.
///
class FilesystemErrorTests: public Test {};

TEST_F(FilesystemErrorTests,
WhatReturnsCorrectMessage) {
	const std::string RefFilesystemErrorMessage("error message");
	FilesystemError ex(RefFilesystemErrorMessage);
	EXPECT_EQ(RefFilesystemErrorMessage, ex.what());
}

///
/// Tests for ConnectionError.
///
class ConnectionErrorTests: public Test {};

TEST_F(ConnectionErrorTests,
WhatReturnsCorrectMessage) {
	const std::string RefConnectionErrorMessage("error message");
	ConnectionError ex(RefConnectionErrorMessage);
	EXPECT_EQ(RefConnectionErrorMessage, ex.what());
}

///
/// Tests for ApiError.
///
class ApiErrorTests: public Test {};

TEST_F(ApiErrorTests,
GettersAndWhatReturnCorrectValuesWhenDescriptionIsGiven) {
	ApiError ex(404, "Not Found", "The page was not found.");
	EXPECT_STREQ("404 Not Found", ex.what());
	EXPECT_EQ(404, ex.getCode());
	EXPECT_EQ("Not Found", ex.getMessage());
	EXPECT_EQ("The page was not found.", ex.getDescription());
}

TEST_F(ApiErrorTests,
GetDescriptionReturnsSameValueAsWhatWhenDescriptionIsNotGiven) {
	ApiError e(404, "Not Found");
	EXPECT_EQ(e.what(), e.getDescription());
}

///
/// Tests for DecompilationError.
///
class DecompilationErrorTests: public Test {};

TEST_F(DecompilationErrorTests,
WhatReturnsCorrectMessage) {
	const std::string RefDecompilationErrorMessage("error message");
	DecompilationError ex(RefDecompilationErrorMessage);
	EXPECT_EQ(RefDecompilationErrorMessage, ex.what());
}

} // namespace tests
} // namespace retdec
