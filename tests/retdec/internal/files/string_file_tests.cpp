///
/// @file      retdec/internal/files/string_file_tests.cpp
/// @copyright (c) 2015 by Petr Zemek (s3rvac@gmail.com) and contributors
/// @license   MIT, see the @c LICENSE file for more details
/// @brief     Tests for the file storing its content in a string.
///

#include <gtest/gtest.h>

#include "retdec/internal/files/string_file.h"
#include "retdec/internal/utilities/os.h"
#include "retdec/test_utilities/tmp_file.h"

using namespace testing;
using namespace retdec::tests;

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

TEST_F(StringFileTests,
SaveCopyToSavesCopyOfFileToGivenDirectory) {
	const std::string Content("content");
	const std::string Name("retdec-cpp-string-file-save-copy-to-test.txt");
	StringFile file{Content, Name};

	file.saveCopyTo(".");

	RemoveFileOnDestruction remover(Name);
	EXPECT_EQ(Content, readFile(Name));
}

} // namespace tests
} // namespace internal
} // namespace retdec
