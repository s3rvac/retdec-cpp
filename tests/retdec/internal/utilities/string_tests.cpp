///
/// @file      retdec/internal/utilities/string_tests.cpp
/// @copyright (c) 2015 by Petr Zemek (s3rvac@gmail.com) and contributors
/// @license   MIT, see the @c LICENSE file for more details
/// @brief     Tests for string utilities.
///

#include <gtest/gtest.h>

#include "retdec/internal/utilities/string.h"

using namespace testing;

namespace retdec {
namespace internal {
namespace tests {

///
/// Tests for capitalizeWords().
///
class CapitalizeWordsTests: public Test {};

TEST_F(CapitalizeWordsTests,
SingleLowercaseWordIsCapitalizedCorrectly) {
	EXPECT_EQ("Test", capitalizeWords("test"));
}

TEST_F(CapitalizeWordsTests,
TwoLowercaseWordsAreCapitalizedCorrectly) {
	EXPECT_EQ("Test Me", capitalizeWords("test me"));
}

TEST_F(CapitalizeWordsTests,
TwoUppercaseWordsAreCapitalizedCorrectly) {
	EXPECT_EQ("Test Me", capitalizeWords("TEST ME"));
}

TEST_F(CapitalizeWordsTests,
TwoMixedcaseWordsAreCapitalizedCorrectly) {
	EXPECT_EQ("Test Me", capitalizeWords("tEsT mE"));
}

TEST_F(CapitalizeWordsTests,
ManyWordsAreCapitalizedCorrectly) {
	EXPECT_EQ("My Name Is Jerry", capitalizeWords("my name is jerry"));
}

TEST_F(CapitalizeWordsTests,
WhitespaceIsPreserved) {
	EXPECT_EQ("  Test  \t Me\n", capitalizeWords("  test  \t me\n"));
}

TEST_F(CapitalizeWordsTests,
WordsBeginningWithNonAlphanumericCharactersAreNotModified) {
	EXPECT_EQ("5abc", capitalizeWords("5abc"));
	EXPECT_EQ(".abc", capitalizeWords(".abc"));
}

} // namespace tests
} // namespace internal
} // namespace retdec
