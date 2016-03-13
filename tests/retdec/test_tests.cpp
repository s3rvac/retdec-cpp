///
/// @file      retdec/test_tests.cpp
/// @copyright (c) 2015-2016 by Petr Zemek (s3rvac@gmail.com) and contributors
/// @license   MIT, see the @c LICENSE file for more details
/// @brief     Tests for the testing service.
///

#include <gtest/gtest.h>

#include "retdec/test.h"
#include "retdec/internal/connection_manager_mock.h"
#include "retdec/settings.h"

using namespace retdec::internal;
using namespace retdec::internal::tests;

namespace retdec {
namespace tests {

///
/// Tests for Test.
///
class TestTests: public testing::Test {};

TEST_F(TestTests,
IsCreatedSuccessfullyWithDefaultConnectionManager) {
	retdec::Test test{
		Settings()
	};
}

TEST_F(TestTests,
IsCreatedSuccessfullyWithCustomConnectionManager) {
	auto connectionManager = std::make_shared<ConnectionManagerMock>();
	retdec::Test test(
		Settings(),
		connectionManager
	);
}

} // namespace tests
} // namespace retdec
