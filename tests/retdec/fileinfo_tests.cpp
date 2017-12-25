///
/// @file      retdec/fileinfo_tests.cpp
/// @copyright (c) 2015-2017 by Petr Zemek (s3rvac@gmail.com) and contributors
/// @license   MIT, see the @c LICENSE file for more details
/// @brief     Tests for the fileinfo service.
///

#include <gtest/gtest.h>

#include "retdec/fileinfo.h"
#include "retdec/internal/connection_manager_mock.h"
#include "retdec/settings.h"

using namespace testing;
using namespace retdec::internal;
using namespace retdec::internal::tests;

namespace retdec {
namespace tests {

///
/// Tests for Fileinfo.
///
class FileinfoTests: public Test {};

TEST_F(FileinfoTests,
IsCreatedSuccessfullyWithDefaultConnectionManager) {
	Fileinfo fileinfo{
		Settings()
	};
}

TEST_F(FileinfoTests,
IsCreatedSuccessfullyWithCustomConnectionManager) {
	auto connectionManager = std::make_shared<ConnectionManagerMock>();
	Fileinfo fileinfo(
		Settings(),
		connectionManager
	);
}

} // namespace tests
} // namespace retdec
