///
/// @file      retdec/test_tests.cpp
/// @copyright (c) 2015-2017 by Petr Zemek (s3rvac@gmail.com) and contributors
/// @license   MIT, see the @c LICENSE file for more details
/// @brief     Tests for the testing service.
///

#include <gtest/gtest.h>
#include <json/json.h>

#include "retdec/exceptions.h"
#include "retdec/internal/connection_manager_mock.h"
#include "retdec/internal/connection_mock.h"
#include "retdec/internal/utilities/json.h"
#include "retdec/settings.h"
#include "retdec/test.h"

using namespace retdec::internal::tests;
using namespace retdec::internal;
using testing::NiceMock;
using testing::Return;
using testing::_;

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

///
/// Tests for Test::auth().
///
class TestAuthTests: public testing::Test {
public:
	virtual void SetUp() override;

	std::unique_ptr<ResponseMock> response =
		std::make_unique<ResponseMock>();

	std::shared_ptr<ConnectionMock> conn =
		std::make_shared<ConnectionMock>();

	std::shared_ptr<NiceMock<ConnectionManagerMock>> connectionManager =
		std::make_shared<NiceMock<ConnectionManagerMock>>();

	std::unique_ptr<retdec::Test> test = std::make_unique<retdec::Test>(
		Settings()
			.apiKey("API-KEY"),
		connectionManager
	);
};

void TestAuthTests::SetUp() {
	ON_CALL(*connectionManager, newConnection(_))
		.WillByDefault(Return(conn));
}

TEST_F(TestAuthTests,
AuthDoesNotThrowAuthErrorWhenAuthSucceeded) {
	EXPECT_CALL(*response, statusCode())
		.WillOnce(Return(200)); // HTTP 200 OK
	EXPECT_CALL(*conn, sendGetRequestProxy(
			"https://retdec.com/service/api/test/echo"))
		.WillOnce(Return(response.release()));

	test->auth();
}

TEST_F(TestAuthTests,
AuthThrowsAuthErrorWhenAuthFailed) {
	EXPECT_CALL(*response, statusCode())
		.WillRepeatedly(Return(401)); // HTTP 401 Unauthorized
	EXPECT_CALL(*response, statusMessage())
		.WillOnce(Return("Unauthorized"));
	EXPECT_CALL(*response, bodyAsJson())
		.WillOnce(Return(toJson(R"(
			{
				"code": 401,
				"message": "Unauthorized",
				"description": "Unauthorized."
			}
		)")));
	EXPECT_CALL(*conn, sendGetRequestProxy(
			"https://retdec.com/service/api/test/echo"))
		.WillOnce(Return(response.release()));

	try {
		test->auth();
		FAIL() << "expected AuthError to be thrown";
	} catch (const AuthError &ex) {
		ASSERT_EQ(401, ex.getCode());
		ASSERT_EQ("Unauthorized", ex.getMessage());
	}
}

} // namespace tests
} // namespace retdec
