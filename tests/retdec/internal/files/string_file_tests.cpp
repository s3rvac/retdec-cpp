///
/// @file      retdec/internal/files/string_file_tests.cpp
/// @copyright (c) 2015 by Petr Zemek (s3rvac@gmail.com) and contributors
/// @license   MIT, see the @c LICENSE file for more details
/// @brief     Tests for the file storing its content in a string.
///

#include <gtest/gtest.h>

#include "retdec/internal/files/string_file.h"

using namespace testing;

namespace retdec {
namespace internal {
namespace tests {

///
/// Tests for StringFile.
///
class StringFileTests: public Test {};

TEST_F(StringFileTests,
FileHasCorrectContentUponCreation) {
	StringFile file("content");
	EXPECT_EQ("content", file.getContent());
}

TEST_F(StringFileTests,
GetNameReturnsCorrectNameWhenFileHasName) {
	StringFile file("content", "file.txt");
	EXPECT_EQ("file.txt", file.getName());
}

TEST_F(StringFileTests,
GetNameReturnsEmptyStringWhenFileHasNoName) {
	StringFile file("content");
	EXPECT_EQ("", file.getName());
}

} // namespace tests
} // namespace internal
} // namespace retdec
