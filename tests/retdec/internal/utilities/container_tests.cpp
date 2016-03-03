///
/// @file      retdec/internal/utilities/containertests.cpp
/// @copyright (c) 2015-2016 by Petr Zemek (s3rvac@gmail.com) and contributors
/// @license   MIT, see the @c LICENSE file for more details
/// @brief     Tests for container utilities.
///

#include <map>

#include <gtest/gtest.h>

#include "retdec/internal/utilities/container.h"

using namespace testing;

namespace retdec {
namespace internal {
namespace tests {

///
/// Tests for hasKey().
///
class HasKeyTests: public Test {};

TEST_F(HasKeyTests,
ReturnsTrueWhenMapHasKey) {
	std::map<int, int> map{
		{1, 2}
	};

	ASSERT_TRUE(hasKey(map, 1));
}

TEST_F(HasKeyTests,
ReturnsFalseWhenMapDoesNotHaveKey) {
	std::map<int, int> map;

	ASSERT_FALSE(hasKey(map, 1));
}

///
/// Tests for getValue().
///
class GetValueTests: public Test {};

TEST_F(GetValueTests,
ReturnsValueWhenMapHasKey) {
	std::map<int, int> map{
		{1, 2}
	};

	ASSERT_EQ(2, getValue(map, 1));
}

TEST_F(GetValueTests,
ReturnsDefaultValueWhenMapDoesNotHaveKey) {
	std::map<int, int> map;

	ASSERT_EQ(0, getValue(map, 1));
}

} // namespace tests
} // namespace internal
} // namespace retdec
