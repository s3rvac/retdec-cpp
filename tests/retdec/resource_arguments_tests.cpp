///
/// @file      retdec/resource_arguments_tests.cpp
/// @copyright (c) 2015 by Petr Zemek (s3rvac@gmail.com) and contributors
/// @license   MIT, see the @c LICENSE file for more details
/// @brief     Tests for the base class of arguments for all services.
///

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "retdec/resource_arguments.h"
#include "retdec/file_mock.h"

using namespace testing;

namespace retdec {
namespace tests {

///
/// Tests for ResourceArguments.
///
class ResourceArgumentsTests: public Test {};

// Generic access to arguments.

TEST_F(ResourceArgumentsTests,
ArgumentSetsNewArgumentInPlace) {
	ResourceArguments args;

	args.argument("id", "value");

	ASSERT_EQ("value", args.argument("id"));
}

TEST_F(ResourceArgumentsTests,
WithArgumentReturnsNewArgumentsWithCorrectArgument) {
	ResourceArguments args;

	auto newArgs = args.withArgument("id", "value");

	ASSERT_EQ("value", newArgs.argument("id"));
}

TEST_F(ResourceArgumentsTests,
HasArgumentReturnsTrueWhenArgumentIsSet) {
	auto args = ResourceArguments()
		.withArgument("id", "value");

	ASSERT_TRUE(args.hasArgument("id"));
}

TEST_F(ResourceArgumentsTests,
HasArgumentReturnsFalseWhenArgumentIsNotSet) {
	ResourceArguments args;

	ASSERT_FALSE(args.hasArgument("id"));
}

TEST_F(ResourceArgumentsTests,
IterationOverArgumentsWorksCorrectly) {
	auto args = ResourceArguments()
		.withArgument("id1", "value1")
		.withArgument("id2", "value2");

	auto it = args.argumentsBegin();
	ASSERT_EQ("id1", it->first);
	ASSERT_EQ("value1", it->second);
	++it;
	ASSERT_EQ("id2", it->first);
	ASSERT_EQ("value2", it->second);
	++it;
	ASSERT_EQ(args.argumentsEnd(), it);
}

// Generic access to files.

TEST_F(ResourceArgumentsTests,
FileSetsNewFileInPlace) {
	ResourceArguments args;
	auto file = std::make_shared<FileMock>();

	args.file("id", file);

	ASSERT_EQ(file, args.file("id"));
}

TEST_F(ResourceArgumentsTests,
WithFileReturnsNewFilesWithCorrectFile) {
	ResourceArguments args;
	auto file = std::make_shared<FileMock>();

	auto newArgs = args.withFile("id", file);

	ASSERT_EQ(file, newArgs.file("id"));
}

TEST_F(ResourceArgumentsTests,
HasFileReturnsTrueWhenFileIsSet) {
	auto args = ResourceArguments()
		.withFile("id", std::make_shared<FileMock>());
	ASSERT_TRUE(args.hasFile("id"));

}

TEST_F(ResourceArgumentsTests,
HasFileReturnsFalseWhenFileIsNotSet) {
	ResourceArguments args;

	ASSERT_FALSE(args.hasFile("id"));
}

TEST_F(ResourceArgumentsTests,
IterationOverFilesWorksCorrectly) {
	auto file1 = std::make_shared<FileMock>();
	auto file2 = std::make_shared<FileMock>();
	auto args = ResourceArguments()
		.withFile("id1", file1)
		.withFile("id2", file2);

	auto it = args.filesBegin();
	ASSERT_EQ("id1", it->first);
	ASSERT_EQ(file1, it->second);
	++it;
	ASSERT_EQ("id2", it->first);
	ASSERT_EQ(file2, it->second);
	++it;
	ASSERT_EQ(args.filesEnd(), it);
}

// Chaining.

TEST_F(ResourceArgumentsTests,
InPlaceSettersAllowChainingForLValue) {
	ResourceArguments args;

	args.argument("id1", "value1")
		.argument("id2", "value2");

	ASSERT_EQ("value1", args.argument("id1"));
	ASSERT_EQ("value2", args.argument("id2"));
}

TEST_F(ResourceArgumentsTests,
InPlaceSettersAllowChainingForRValue) {
	auto args = ResourceArguments()
		.argument("id1", "value1")
		.argument("id2", "value2");

	ASSERT_EQ("value1", args.argument("id1"));
	ASSERT_EQ("value2", args.argument("id2"));
}

TEST_F(ResourceArgumentsTests,
NotModifyingSettersAllowChaining) {
	auto args = ResourceArguments()
		.withArgument("id1", "value1")
		.withArgument("id2", "value2");

	ASSERT_EQ("value1", args.argument("id1"));
	ASSERT_EQ("value2", args.argument("id2"));
}

} // namespace tests
} // namespace retdec
