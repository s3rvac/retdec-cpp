///
/// @file      retdec/decompilation_arguments_tests.cpp
/// @copyright (c) 2015-2016 by Petr Zemek (s3rvac@gmail.com) and contributors
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

	ASSERT_EQ("c", args.mode());
}

TEST_F(DecompilationArgumentsTests,
WithModeReturnsNewArgumentsWithCorrectMode) {
	DecompilationArguments args;

	auto newArgs = args.withMode("c");

	ASSERT_EQ("c", newArgs.mode());
}

TEST_F(DecompilationArgumentsTests,
HasModeReturnsTrueWhenModeIsSet) {
	auto args = DecompilationArguments()
		.withMode("c");

	ASSERT_TRUE(args.hasMode());
}

TEST_F(DecompilationArgumentsTests,
HasModeReturnsFalseWhenModeIsNotSet) {
	DecompilationArguments args;

	ASSERT_FALSE(args.hasMode());
}

// Selective decompilation: ranges.

TEST_F(DecompilationArgumentsTests,
SelDecompRangesSetsNewRangesInPlace) {
	DecompilationArguments args;

	args.selDecompRanges("0x0-0x1");

	ASSERT_EQ("0x0-0x1", args.selDecompRanges());
}

TEST_F(DecompilationArgumentsTests,
WithSelDecompRangesReturnsNewArgumentsWithCorrectRanges) {
	DecompilationArguments args;

	auto newArgs = args.withSelDecompRanges("0x0-0x1");

	ASSERT_EQ("0x0-0x1", newArgs.selDecompRanges());
}

TEST_F(DecompilationArgumentsTests,
HasSelDecompRangesReturnsTrueWhenSelDecompRangesIsSet) {
	auto args = DecompilationArguments()
		.withSelDecompRanges("0x0-0x1");

	ASSERT_TRUE(args.hasSelDecompRanges());
}

TEST_F(DecompilationArgumentsTests,
HasSelDecompRangesReturnsFalseWhenSelDecompRangesIsNotSet) {
	DecompilationArguments args;

	ASSERT_FALSE(args.hasSelDecompRanges());
}

// Selective decompilation: decoding.

TEST_F(DecompilationArgumentsTests,
SelDecompDecodingSetsNewDecodingInPlace) {
	DecompilationArguments args;

	args.selDecompDecoding("only");

	ASSERT_EQ("only", args.selDecompDecoding());
}

TEST_F(DecompilationArgumentsTests,
WithSelDecompDecodingReturnsNewArgumentsWithCorrectDecoding) {
	DecompilationArguments args;

	auto newArgs = args.withSelDecompDecoding("only");

	ASSERT_EQ("only", newArgs.selDecompDecoding());
}

TEST_F(DecompilationArgumentsTests,
HasSelDecompDecodingReturnsTrueWhenSelDecompDecodingIsSet) {
	auto args = DecompilationArguments()
		.withSelDecompDecoding("only");

	ASSERT_TRUE(args.hasSelDecompDecoding());
}

TEST_F(DecompilationArgumentsTests,
HasSelDecompDecodingReturnsFalseWhenSelDecompDecodingIsNotSet) {
	DecompilationArguments args;

	ASSERT_FALSE(args.hasSelDecompDecoding());
}

// Files: input.

TEST_F(DecompilationArgumentsTests,
InputFileSetsNewInputFileInPlace) {
	DecompilationArguments args;
	auto file = std::make_shared<FileMock>();

	args.inputFile(file);

	ASSERT_EQ(file, args.inputFile());
}

TEST_F(DecompilationArgumentsTests,
WithInputFileReturnsNewArgumentsWithCorrectInputFile) {
	DecompilationArguments args;
	auto file = std::make_shared<FileMock>();

	auto newArgs = args.withInputFile(file);

	ASSERT_EQ(file, newArgs.inputFile());
}

TEST_F(DecompilationArgumentsTests,
HasInputFileReturnsTrueWhenInputFileIsSet) {
	auto args = DecompilationArguments()
		.withInputFile(std::make_shared<FileMock>());

	ASSERT_TRUE(args.hasInputFile());
}

TEST_F(DecompilationArgumentsTests,
HasInputFileReturnsFalseWhenInputFileIsNotSet) {
	DecompilationArguments args;

	ASSERT_FALSE(args.hasInputFile());
}

// Chaining.

TEST_F(DecompilationArgumentsTests,
InPlaceSettersAllowChainingForLValue) {
	DecompilationArguments args;
	auto file = std::make_shared<FileMock>();

	args.mode("c")
		.inputFile(file);

	ASSERT_EQ("c", args.mode());
	ASSERT_EQ(file, args.inputFile());
}

TEST_F(DecompilationArgumentsTests,
InPlaceSettersAllowChainingForRValue) {
	auto file = std::make_shared<FileMock>();

	auto args = DecompilationArguments()
		.mode("c")
		.inputFile(file);

	ASSERT_EQ("c", args.mode());
	ASSERT_EQ(file, args.inputFile());
}

TEST_F(DecompilationArgumentsTests,
NotModifyingSettersAllowChaining) {
	auto file = std::make_shared<FileMock>();

	auto args = DecompilationArguments()
		.withMode("c")
		.withInputFile(file);

	ASSERT_EQ("c", args.mode());
	ASSERT_EQ(file, args.inputFile());
}

} // namespace tests
} // namespace retdec
