///
/// @file      retdec/analysis_arguments_tests.cpp
/// @copyright (c) 2015-2017 by Petr Zemek (s3rvac@gmail.com) and contributors
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

// Verbose.

TEST_F(AnalysisArgumentsTests,
VerboseYesSetsVerboseToYesInPlace) {
	AnalysisArguments args;

	args.verbose("yes");

	ASSERT_EQ("yes", args.verbose());
}

TEST_F(AnalysisArgumentsTests,
VerboseNoSetsVerboseToNoInPlace) {
	AnalysisArguments args;

	args.verbose("no");

	ASSERT_EQ("no", args.verbose());
}

TEST_F(AnalysisArgumentsTests,
WithVerboseYesReturnsNewArgumentsWithVerboseSetToYes) {
	AnalysisArguments args;

	auto newArgs = args.withVerbose("yes");

	ASSERT_EQ("yes", newArgs.verbose());
	ASSERT_FALSE(args.hasVerbose());
}

TEST_F(AnalysisArgumentsTests,
HasVerboseReturnsFalseByDefault) {
	AnalysisArguments args;

	ASSERT_FALSE(args.hasVerbose());
}

TEST_F(AnalysisArgumentsTests,
HasVerboseReturnsTrueWhenVerboseIsSetToYes) {
	auto args = AnalysisArguments()
		.withVerbose("yes");

	ASSERT_TRUE(args.hasVerbose());
}

TEST_F(AnalysisArgumentsTests,
HasVerboseReturnsTrueWhenVerboseIsSetToNo) {
	auto args = AnalysisArguments()
		.withVerbose("no");

	ASSERT_TRUE(args.hasVerbose());
}

TEST_F(AnalysisArgumentsTests,
HasVerboseReturnsFalseWhenVerboseIsNotSet) {
	AnalysisArguments args;

	ASSERT_FALSE(args.hasVerbose());
}

// Input file.

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

// Chaining.

TEST_F(AnalysisArgumentsTests,
InPlaceSettersAllowChainingForLValue) {
	AnalysisArguments args;
	auto file = std::make_shared<FileMock>();

	args.verbose("yes")
		.inputFile(file);

	ASSERT_EQ("yes", args.verbose());
	ASSERT_EQ(file, args.inputFile());
}

TEST_F(AnalysisArgumentsTests,
InPlaceSettersAllowChainingForRValue) {
	auto file = std::make_shared<FileMock>();

	auto args = AnalysisArguments()
		.verbose("yes")
		.inputFile(file);

	ASSERT_EQ("yes", args.verbose());
	ASSERT_EQ(file, args.inputFile());
}

TEST_F(AnalysisArgumentsTests,
NotModifyingSettersAllowChaining) {
	auto file = std::make_shared<FileMock>();

	auto args = AnalysisArguments()
		.verbose("yes")
		.withInputFile(file);

	ASSERT_EQ("yes", args.verbose());
	ASSERT_EQ(file, args.inputFile());
}

} // namespace tests
} // namespace retdec
