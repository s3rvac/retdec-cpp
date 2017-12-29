///
/// @file      retdec/decompiler_tests.cpp
/// @copyright (c) 2015 by Petr Zemek (s3rvac@gmail.com) and contributors
/// @license   MIT, see the @c LICENSE file for more details
/// @brief     Tests for the decompilation service.
///

#include <gtest/gtest.h>

#include "retdec/decompiler.h"
#include "retdec/internal/connection_manager_mock.h"
#include "retdec/settings.h"

using namespace testing;
using namespace retdec::internal;
using namespace retdec::internal::tests;

namespace retdec {
namespace tests {

///
/// Tests for Decompiler.
///
class DecompilerTests: public Test {};

TEST_F(DecompilerTests,
IsCreatedSuccessfullyWithDefaultConnectionManager) {
	Decompiler decompiler{
		Settings()
	};
}

TEST_F(DecompilerTests,
IsCreatedSuccessfullyWithCustomConnectionManager) {
	auto connectionManager = std::make_shared<ConnectionManagerMock>();
	Decompiler decompiler(
		Settings(),
		connectionManager
	);
}

} // namespace tests
} // namespace retdec
