///
/// @file      retdec/internal/utilities/os_tests.cpp
/// @copyright (c) 2015 by Petr Zemek (s3rvac@gmail.com) and contributors
/// @license   MIT, see the @c LICENSE file for more details
/// @brief     Tests for operating-system-related utilities.
///

#include <gtest/gtest.h>

#include "retdec/exceptions.h"
#include "retdec/internal/utilities/os.h"
#include "retdec/test_utilities/tmp_file.h"

using namespace testing;
using namespace retdec::tests;

namespace retdec {
namespace internal {
namespace tests {

///
/// Tests for fileNameFromPath().
///
class FileNameFromPathTests: public Test {};

TEST_F(FileNameFromPathTests,
FileNameFromPathReturnsCorrectNameForPathWithSeparators) {
#ifdef RETDEC_OS_WINDOWS
	EXPECT_EQ("file.txt", fileNameFromPath(R"(C:\\path\to\file.txt)"));
#else
	EXPECT_EQ("file.txt", fileNameFromPath("/path/to/file.txt"));
#endif
}

TEST_F(FileNameFromPathTests,
FileNameFromPathContainingJustFileNameReturnsCorrectFileName) {
	EXPECT_EQ("file.txt", fileNameFromPath("file.txt"));
}

TEST_F(FileNameFromPathTests,
FileNameFromPathContainingNoFileNameReturnsEmptyString) {
#ifdef RETDEC_OS_WINDOWS
	EXPECT_EQ("", fileNameFromPath(R"(C:\\path\to\dir\)"));
#else
	EXPECT_EQ("", fileNameFromPath("/path/to/dir/"));
#endif
}

///
/// Tests for readFile().
///
class ReadFileTests: public Test {};

TEST_F(ReadFileTests,
ReturnsCorrectContentWhenFileExists) {
	auto tmpFile = TmpFile::createWithContent("content");

	EXPECT_EQ("content", readFile(tmpFile->getPath()));
}

TEST_F(ReadFileTests,
ThrowsFilesystemErrorWhenFileDoesNotExist) {
	EXPECT_THROW(readFile("nonexisting-file"), FilesystemError);
}

///
/// Tests for writeFile().
///
class WriteFileTests: public Test {};

///
/// Tests for copyFile().
///
class CopyFileTests: public Test {};

TEST_F(CopyFileTests,
ThrowsFilesystemErrorWhenSourceFileDoesNotExist) {
	EXPECT_THROW(copyFile("nonexisting-file", "any-file"), FilesystemError);
}

} // namespace tests
} // namespace internal
} // namespace retdec
