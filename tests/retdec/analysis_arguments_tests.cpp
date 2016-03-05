///
/// @file      retdec/analysis_arguments_tests.cpp
/// @copyright (c) 2015-2016 by Petr Zemek (s3rvac@gmail.com) and contributors
/// @license   MIT, see the @c LICENSE file for more details
/// @brief     Tests for the analysis arguments.
///

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "retdec/analysis_arguments.h"
#include "retdec/file_mock.h"

using namespace testing;

namespace retdec {
namespace tests {

///
/// Tests for AnalysisArguments.
///
class AnalysisArgumentsTests: public Test {};

// Files: input.

TEST_F(AnalysisArgumentsTests,
InputFileSetsNewInputFileInPlace) {
	AnalysisArguments args;
	auto file = std::make_shared<FileMock>();

	args.inputFile(file);

	ASSERT_EQ(file, args.inputFile());
}

TEST_F(AnalysisArgumentsTests,
WithInputFileReturnsNewArgumentsWithCorrectInputFile) {
	AnalysisArguments args;
	auto file = std::make_shared<FileMock>();

	auto newArgs = args.withInputFile(file);

	ASSERT_EQ(file, newArgs.inputFile());
}

TEST_F(AnalysisArgumentsTests,
HasInputFileReturnsTrueWhenInputFileIsSet) {
	auto args = AnalysisArguments()
		.withInputFile(std::make_shared<FileMock>());

	ASSERT_TRUE(args.hasInputFile());
}

TEST_F(AnalysisArgumentsTests,
HasInputFileReturnsFalseWhenInputFileIsNotSet) {
	AnalysisArguments args;

	ASSERT_FALSE(args.hasInputFile());
}

} // namespace tests
} // namespace retdec
