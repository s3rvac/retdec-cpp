///
/// @file      retdec/decompilation_arguments_tests.cpp
/// @copyright (c) 2015 by Petr Zemek (s3rvac@gmail.com) and contributors
/// @license   MIT, see the @c LICENSE file for more details
/// @brief     Tests for the decompilation arguments.
///

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "retdec/decompilation_arguments.h"
#include "retdec/file_mock.h"

using namespace testing;

namespace retdec {
namespace tests {

///
/// Tests for DecompilationArguments.
///
class DecompilationArgumentsTests: public Test {};

// Mode.

TEST_F(DecompilationArgumentsTests,
ModeSetsNewModeInPlace) {
	DecompilationArguments args;

	args.mode("c");

	EXPECT_EQ("c", args.mode());
}

TEST_F(DecompilationArgumentsTests,
WithModeReturnsNewArgumentsWithCorrectMode) {
	DecompilationArguments args;

	auto newArgs = args.withMode("c");

	EXPECT_EQ("c", newArgs.mode());
}

TEST_F(DecompilationArgumentsTests,
HasModeReturnsTrueWhenModeIsSet) {
	auto args = DecompilationArguments()
		.withMode("c");

	EXPECT_TRUE(args.hasMode());
}

TEST_F(DecompilationArgumentsTests,
HasModeReturnsFalseWhenModeIsNotSet) {
	DecompilationArguments args;

	EXPECT_FALSE(args.hasMode());
}

// Selective decompilation: ranges.

TEST_F(DecompilationArgumentsTests,
SelDecompRangesSetsNewRangesInPlace) {
	DecompilationArguments args;

	args.selDecompRanges("0x0-0x1");

	EXPECT_EQ("0x0-0x1", args.selDecompRanges());
}

TEST_F(DecompilationArgumentsTests,
WithSelDecompRangesReturnsNewArgumentsWithCorrectRanges) {
	DecompilationArguments args;

	auto newArgs = args.withSelDecompRanges("0x0-0x1");

	EXPECT_EQ("0x0-0x1", newArgs.selDecompRanges());
}

TEST_F(DecompilationArgumentsTests,
HasSelDecompRangesReturnsTrueWhenSelDecompRangesIsSet) {
	auto args = DecompilationArguments()
		.withSelDecompRanges("0x0-0x1");

	EXPECT_TRUE(args.hasSelDecompRanges());
}

TEST_F(DecompilationArgumentsTests,
HasSelDecompRangesReturnsFalseWhenSelDecompRangesIsNotSet) {
	DecompilationArguments args;

	EXPECT_FALSE(args.hasSelDecompRanges());
}

// Selective decompilation: decoding.

TEST_F(DecompilationArgumentsTests,
SelDecompDecodingSetsNewDecodingInPlace) {
	DecompilationArguments args;

	args.selDecompDecoding("only");

	EXPECT_EQ("only", args.selDecompDecoding());
}

TEST_F(DecompilationArgumentsTests,
WithSelDecompDecodingReturnsNewArgumentsWithCorrectDecoding) {
	DecompilationArguments args;

	auto newArgs = args.withSelDecompDecoding("only");

	EXPECT_EQ("only", newArgs.selDecompDecoding());
}

TEST_F(DecompilationArgumentsTests,
HasSelDecompDecodingReturnsTrueWhenSelDecompDecodingIsSet) {
	auto args = DecompilationArguments()
		.withSelDecompDecoding("only");

	EXPECT_TRUE(args.hasSelDecompDecoding());
}

TEST_F(DecompilationArgumentsTests,
HasSelDecompDecodingReturnsFalseWhenSelDecompDecodingIsNotSet) {
	DecompilationArguments args;

	EXPECT_FALSE(args.hasSelDecompDecoding());
}

// Files: input.

TEST_F(DecompilationArgumentsTests,
InputFileSetsNewInputFileInPlace) {
	DecompilationArguments args;
	auto file = std::make_shared<FileMock>();

	args.inputFile(file);

	EXPECT_EQ(file, args.inputFile());
}

TEST_F(DecompilationArgumentsTests,
WithInputFileReturnsNewArgumentsWithCorrectInputFile) {
	DecompilationArguments args;
	auto file = std::make_shared<FileMock>();

	auto newArgs = args.withInputFile(file);

	EXPECT_EQ(file, newArgs.inputFile());
}

TEST_F(DecompilationArgumentsTests,
HasInputFileReturnsTrueWhenInputFileIsSet) {
	auto args = DecompilationArguments()
		.withInputFile(std::make_shared<FileMock>());

	EXPECT_TRUE(args.hasInputFile());
}

TEST_F(DecompilationArgumentsTests,
HasInputFileReturnsFalseWhenInputFileIsNotSet) {
	DecompilationArguments args;

	EXPECT_FALSE(args.hasInputFile());
}

// Generic access to arguments.

TEST_F(DecompilationArgumentsTests,
ArgumentSetsNewArgumentInPlace) {
	DecompilationArguments args;

	args.argument("id", "value");

	EXPECT_EQ("value", args.argument("id"));
}

TEST_F(DecompilationArgumentsTests,
WithArgumentReturnsNewArgumentsWithCorrectArgument) {
	DecompilationArguments args;

	auto newArgs = args.withArgument("id", "value");

	EXPECT_EQ("value", newArgs.argument("id"));
}

TEST_F(DecompilationArgumentsTests,
HasArgumentReturnsTrueWhenArgumentIsSet) {
	auto args = DecompilationArguments()
		.withArgument("id", "value");

	EXPECT_TRUE(args.hasArgument("id"));
}

TEST_F(DecompilationArgumentsTests,
HasArgumentReturnsFalseWhenArgumentIsNotSet) {
	DecompilationArguments args;

	EXPECT_FALSE(args.hasArgument("id"));
}

TEST_F(DecompilationArgumentsTests,
IterationOverArgumentsWorksCorrectly) {
	auto args = DecompilationArguments()
		.withArgument("id1", "value1")
		.withArgument("id2", "value2");

	auto it = args.argumentsBegin();
	EXPECT_EQ("id1", it->first);
	EXPECT_EQ("value1", it->second);
	++it;
	EXPECT_EQ("id2", it->first);
	EXPECT_EQ("value2", it->second);
	++it;
	EXPECT_EQ(args.argumentsEnd(), it);
}

// Generic access to files.

TEST_F(DecompilationArgumentsTests,
FileSetsNewFileInPlace) {
	DecompilationArguments args;
	auto file = std::make_shared<FileMock>();

	args.file("id", file);

	EXPECT_EQ(file, args.file("id"));
}

TEST_F(DecompilationArgumentsTests,
WithFileReturnsNewFilesWithCorrectFile) {
	DecompilationArguments args;
	auto file = std::make_shared<FileMock>();

	auto newArgs = args.withFile("id", file);

	EXPECT_EQ(file, newArgs.file("id"));
}

TEST_F(DecompilationArgumentsTests,
HasFileReturnsTrueWhenFileIsSet) {
	auto args = DecompilationArguments()
		.withFile("id", std::make_shared<FileMock>());
	EXPECT_TRUE(args.hasFile("id"));

}

TEST_F(DecompilationArgumentsTests,
HasFileReturnsFalseWhenFileIsNotSet) {
	DecompilationArguments args;

	EXPECT_FALSE(args.hasFile("id"));
}

TEST_F(DecompilationArgumentsTests,
IterationOverFilesWorksCorrectly) {
	auto file1 = std::make_shared<FileMock>();
	auto file2 = std::make_shared<FileMock>();
	auto args = DecompilationArguments()
		.withFile("id1", file1)
		.withFile("id2", file2);

	auto it = args.filesBegin();
	EXPECT_EQ("id1", it->first);
	EXPECT_EQ(file1, it->second);
	++it;
	EXPECT_EQ("id2", it->first);
	EXPECT_EQ(file2, it->second);
	++it;
	EXPECT_EQ(args.filesEnd(), it);
}

// Chaining.

TEST_F(DecompilationArgumentsTests,
InPlaceSettersAllowChainingForLValue) {
	DecompilationArguments args;
	auto file = std::make_shared<FileMock>();

	args.mode("c")
		.inputFile(file);

	EXPECT_EQ("c", args.mode());
	EXPECT_EQ(file, args.inputFile());
}

TEST_F(DecompilationArgumentsTests,
InPlaceSettersAllowChainingForRValue) {
	auto file = std::make_shared<FileMock>();

	auto args = DecompilationArguments()
		.mode("c")
		.inputFile(file);

	EXPECT_EQ("c", args.mode());
	EXPECT_EQ(file, args.inputFile());
}

TEST_F(DecompilationArgumentsTests,
NotModifyingSettersAllowChaining) {
	auto file = std::make_shared<FileMock>();

	auto args = DecompilationArguments()
		.withMode("c")
		.withInputFile(file);

	EXPECT_EQ("c", args.mode());
	EXPECT_EQ(file, args.inputFile());
}

} // namespace tests
} // namespace retdec
