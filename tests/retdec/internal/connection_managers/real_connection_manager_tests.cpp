///
/// @file      retdec/internal/connection_managers/real_connection_manager_tests.cpp
/// @copyright (c) 2015 by Petr Zemek (s3rvac@gmail.com) and contributors
/// @license   MIT, see the @c LICENSE file for more details
/// @brief     Tests for the manager of the connections to the API.
///

#include <gtest/gtest.h>

#include "retdec/internal/connection_managers/real_connection_manager.h"
#include "retdec/internal/connections/real_connection.h"
#include "retdec/internal/utilities/smart_ptr.h"
#include "retdec/settings.h"

using namespace testing;

namespace retdec {
namespace internal {
namespace tests {

///
/// Tests for RealConnectionManager.
///
class RealConnectionManagerTests: public Test {};

TEST_F(RealConnectionManagerTests,
NewConnectionReturnsRealConnection) {
	RealConnectionManager cm;
	auto conn = cm.newConnection(Settings());
	EXPECT_TRUE(isa<RealConnection>(conn));
}

} // namespace tests
} // namespace internal
} // namespace retdec
