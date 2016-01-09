///
/// @file      retdec/internal/files/filesystem_file_tests.cpp
/// @copyright (c) 2015 by Petr Zemek (s3rvac@gmail.com) and contributors
/// @license   MIT, see the @c LICENSE file for more details
/// @brief     Tests for the file stored in a filesystem.
///

#include <gtest/gtest.h>

#include "retdec/internal/files/filesystem_file.h"
#include "retdec/internal/utilities/os.h"
#include "retdec/test_utilities/tmp_file.h"

using namespace testing;
using namespace retdec::tests;

namespace retdec {
namespace internal {
namespace tests {

///
/// Tests for FilesystemFile.
///
class FilesystemFileTests: public Test {};

TEST_F(FilesystemFileTests,
GetNameReturnsCorrectValueWhenNoCustomNameIsGiven) {
#ifdef RETDEC_OS_WINDOWS
	FilesystemFile file(R"(C:\\/path/to/file.txt)");
#else
	FilesystemFile file("/path/to/file.txt");
#endif
	EXPECT_EQ("file.txt", file.getName());
}

TEST_F(FilesystemFileTests,
GetNameReturnsCorrectValueWhenCustomNameIsGiven) {
	FilesystemFile file("/path/to/file.txt", "another_file.txt");
	EXPECT_EQ("another_file.txt", file.getName());
}

TEST_F(FilesystemFileTests,
GetContentReturnsCorrectContent) {
	auto tmpFile = TmpFile::createWithContent("content");
	FilesystemFile file(tmpFile->getPath());
	EXPECT_EQ("content", file.getContent());
}

TEST_F(FilesystemFileTests,
SaveCopyToSavesCopyOfFileToGivenDirectory) {
	const std::string Content("content");
	auto tmpFile = TmpFile::createWithContent(Content);
	const std::string Name("retdec-cpp-filesystem-file-save-copy-to-test.txt");
	FilesystemFile file(tmpFile->getPath(), Name);

	file.saveCopyTo(".");

	RemoveFileOnDestruction remover(Name);
	EXPECT_EQ(Content, readFile(Name));
}

} // namespace tests
} // namespace internal
} // namespace retdec
