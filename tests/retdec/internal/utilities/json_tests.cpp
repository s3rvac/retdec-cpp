///
/// @file      retdec/internal/utilities/json_tests.cpp
/// @copyright (c) 2015-2016 by Petr Zemek (s3rvac@gmail.com) and contributors
/// @license   MIT, see the @c LICENSE file for more details
/// @brief     Tests for string utilities.
///

#include <gtest/gtest.h>

#include "retdec/exceptions.h"
#include "retdec/internal/utilities/json.h"

using namespace testing;

namespace retdec {
namespace internal {
namespace tests {

///
/// Tests for JsonDecodingError.
///
class JsonDecodingErrorTests: public Test {};

TEST_F(JsonDecodingErrorTests,
WhatReturnsCorrectMessage) {
	const std::string RefFormattedErrors("line 1 column 1");
	JsonDecodingError e(RefFormattedErrors);

	ASSERT_EQ("JSON decoding failed: " + RefFormattedErrors, e.what());
}

///
/// Tests for toJson().
///
class ToJsonTests: public Test {};

TEST_F(ToJsonTests,
StringAsJsonIsParsedCorrectly) {
	auto asJson = toJson("\"text\"");

	ASSERT_EQ("text", asJson.asString());
}

TEST_F(ToJsonTests,
ObjectAsJsonIsParsedCorrectly) {
	auto asJson = toJson("{\"id\": 1}");

	ASSERT_TRUE(asJson.isMember("id"));
	ASSERT_EQ(1, asJson.size());
	ASSERT_EQ(1, asJson.get("id", 0).asInt());
}

TEST_F(ToJsonTests,
ThrowsJsonDecodingErrorWhenStringIsInvalid) {
	ASSERT_THROW(toJson("{xxx}"), JsonDecodingError);
}

} // namespace tests
} // namespace internal
} // namespace retdec
