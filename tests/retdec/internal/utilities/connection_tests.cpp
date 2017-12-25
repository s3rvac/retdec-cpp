///
/// @file      retdec/internal/utilities/connection_tests.cpp
/// @copyright (c) 2015-2017 by Petr Zemek (s3rvac@gmail.com) and contributors
/// @license   MIT, see the @c LICENSE file for more details
/// @brief     Tests for connection utilities.
///

#include <memory>

#include <gtest/gtest.h>
#include <json/json.h>

#include "retdec/exceptions.h"
#include "retdec/internal/connection_mock.h"
#include "retdec/internal/utilities/connection.h"
#include "retdec/internal/utilities/json.h"

using namespace testing;

namespace retdec {
namespace internal {
namespace tests {

///
/// Tests for requestSucceeded().
///
class RequestSucceededTests: public Test {};

TEST_F(RequestSucceededTests,
ReturnsTrueWhenStatusCodeIs200) {
	StrictMock<ResponseMock> response;
	EXPECT_CALL(response, statusCode())
		.WillOnce(Return(200)); // HTTP 200 OK

	ASSERT_TRUE(requestSucceeded(response));
}

TEST_F(RequestSucceededTests,
ReturnsTrueWhenStatusCodeIs201) {
	StrictMock<ResponseMock> response;
	EXPECT_CALL(response, statusCode())
		.WillOnce(Return(201)); // HTTP 201 Created

	ASSERT_TRUE(requestSucceeded(response));
}

TEST_F(RequestSucceededTests,
ReturnsTrueWhenStatusCodeIs300) {
	StrictMock<ResponseMock> response;
	EXPECT_CALL(response, statusCode())
		.WillOnce(Return(300)); // HTTP 300 Multiple Choices

	ASSERT_FALSE(requestSucceeded(response));
}

///
/// Tests for verifyRequestSucceeded().
///
class VerifyRequestSucceededTests: public Test {};

TEST_F(VerifyRequestSucceededTests,
DoesNotThrowApiErrorWhenRequestSucceeded) {
	NiceMock<ResponseMock> response;
	ON_CALL(response, statusCode())
		.WillByDefault(Return(200)); // HTTP 200 OK

	verifyRequestSucceeded(response);
}

TEST_F(VerifyRequestSucceededTests,
ThrowsApiErrorWithCorrectMessageWhenRequestFailedAndResponseHasNotJsonBody) {
	NiceMock<ResponseMock> response;
	ON_CALL(response, statusCode())
		.WillByDefault(Return(400)); // HTTP 400 Bad Request
	ON_CALL(response, statusMessage())
		.WillByDefault(Return("Bad Request"));
	ON_CALL(response, bodyAsJson())
		.WillByDefault(Throw(JsonDecodingError("decoding failed")));

	try {
		verifyRequestSucceeded(response);
		FAIL() << "expected ApiError to be thrown";
	} catch (const ApiError &ex) {
		ASSERT_EQ(400, ex.getCode());
		ASSERT_EQ("Bad Request", ex.getMessage());
		ASSERT_EQ(ex.what(), ex.getDescription());
	}
}

TEST_F(VerifyRequestSucceededTests,
ThrowsApiErrorWithCorrectMessageWhenRequestFailedAndResponseHasJsonBody) {
	NiceMock<ResponseMock> response;
	ON_CALL(response, statusCode())
		.WillByDefault(Return(422)); // HTTP 422 Unprocessable Entity
	ON_CALL(response, statusMessage())
		.WillByDefault(Return("Unprocessable Entity"));
	ON_CALL(response, bodyAsJson())
		.WillByDefault(Return(toJson(R"(
			{
				"code": 422,
				"message": "Missing Parameter",
				"description": "Parameter 'x' is missing."
			}
		)")));

	try {
		verifyRequestSucceeded(response);
		FAIL() << "expected ApiError to be thrown";
	} catch (const ApiError &ex) {
		ASSERT_EQ(422, ex.getCode());
		ASSERT_EQ("Missing Parameter", ex.getMessage());
		ASSERT_EQ("Parameter 'x' is missing.", ex.getDescription());
	}
}

TEST_F(VerifyRequestSucceededTests,
ThrowsAuthErrorWithCorrectMessageWhenRequestFailedDueToAuthError) {
	NiceMock<ResponseMock> response;
	ON_CALL(response, statusCode())
		.WillByDefault(Return(401)); // HTTP 401 Unauthorized
	ON_CALL(response, statusMessage())
		.WillByDefault(Return("Unauthorized"));
	ON_CALL(response, bodyAsJson())
		.WillByDefault(Return(toJson(R"(
			{
				"code": 401,
				"message": "Unauthorized",
				"description": "Unauthorized."
			}
		)")));

	try {
		verifyRequestSucceeded(response);
		FAIL() << "expected AuthError to be thrown";
	} catch (const AuthError &ex) {
		ASSERT_EQ(401, ex.getCode());
		ASSERT_EQ("Unauthorized", ex.getMessage());
		ASSERT_EQ("Unauthorized.", ex.getDescription());
	}
}

///
/// Tests for ResponseVerifyingConnection().
///
class ResponseVerifyingConnectionTests: public Test {
public:
	static std::unique_ptr<NiceMock<ResponseMock>> responseForFailedRequest();
};

///
/// Creates and returns a response for a failed request.
///
std::unique_ptr<NiceMock<ResponseMock>>
		ResponseVerifyingConnectionTests::responseForFailedRequest() {
	auto response = std::make_unique<NiceMock<ResponseMock>>();
	ON_CALL(*response, statusCode())
		.WillByDefault(Return(422)); // HTTP 422 Unprocessable Entity
	ON_CALL(*response, statusMessage())
		.WillByDefault(Return("Unprocessable Entity"));
	ON_CALL(*response, bodyAsJson())
		.WillByDefault(Return(toJson(R"(
			{
				"code": 422,
				"message": "Missing Parameter",
				"description": "Parameter 'x' is missing."
			}
		)")));
	return response;
}

TEST_F(ResponseVerifyingConnectionTests,
GetApiUrlReturnsApiUrlFromWrappedConnection) {
	auto conn = std::make_shared<StrictMock<ConnectionMock>>();
	EXPECT_CALL(*conn, getApiUrl())
		.WillOnce(Return("https://retdec.com/service/api"));
	ResponseVerifyingConnection rvconn(conn);

	ASSERT_EQ("https://retdec.com/service/api", rvconn.getApiUrl());
}

TEST_F(ResponseVerifyingConnectionTests,
SendGetRequestWithUrlCallsSendGetRequestOnWrappedConnectionAndReturnsResponseWhenSucceeded) {
	auto refResponse = new NiceMock<ResponseMock>();
	ON_CALL(*refResponse, statusCode())
		.WillByDefault(Return(200)); // HTTP 200 OK
	auto conn = std::make_shared<StrictMock<ConnectionMock>>();
	Connection::Url url("https://retdec.com/service/api");
	EXPECT_CALL(*conn, sendGetRequestProxy(url))
		.WillOnce(Return(refResponse));
	ResponseVerifyingConnection rvconn(conn);

	auto response = rvconn.sendGetRequest(url);

	ASSERT_EQ(refResponse, response.get());
}

TEST_F(ResponseVerifyingConnectionTests,
SendGetRequestWithUrlCallsSendGetRequestOnWrappedConnectionAndThrowsApiErrorWhenFailed) {
	auto response = responseForFailedRequest();
	auto conn = std::make_shared<StrictMock<ConnectionMock>>();
	Connection::Url url("https://retdec.com/service/api");
	EXPECT_CALL(*conn, sendGetRequestProxy(url))
		.WillOnce(Return(response.release()));
	ResponseVerifyingConnection rvconn(conn);

	ASSERT_THROW(rvconn.sendGetRequest(url), ApiError);
}

TEST_F(ResponseVerifyingConnectionTests,
SendGetRequestWithUrlAndArgsCallsSendGetRequestOnWrappedConnectionAndReturnsResponseWhenSucceeded) {
	auto refResponse = new NiceMock<ResponseMock>();
	ON_CALL(*refResponse, statusCode())
		.WillByDefault(Return(200)); // HTTP 200 OK
	auto conn = std::make_shared<StrictMock<ConnectionMock>>();
	Connection::Url url("https://retdec.com/service/api");
	Connection::RequestArguments args;
	EXPECT_CALL(*conn, sendGetRequestProxy(url, args))
		.WillOnce(Return(refResponse));
	ResponseVerifyingConnection rvconn(conn);

	auto response = rvconn.sendGetRequest(url, args);

	ASSERT_EQ(refResponse, response.get());
}

TEST_F(ResponseVerifyingConnectionTests,
SendGetRequestWithUrlAndArgsCallsSendGetRequestOnWrappedConnectionAndThrowsApiErrorWhenFailed) {
	auto response = responseForFailedRequest();
	auto conn = std::make_shared<StrictMock<ConnectionMock>>();
	Connection::Url url("https://retdec.com/service/api");
	Connection::RequestArguments args;
	EXPECT_CALL(*conn, sendGetRequestProxy(url, args))
		.WillOnce(Return(response.release()));
	ResponseVerifyingConnection rvconn(conn);

	ASSERT_THROW(rvconn.sendGetRequest(url, args), ApiError);
}

TEST_F(ResponseVerifyingConnectionTests,
SendPostRequestCallsSendPostRequestOnWrappedConnectionAndReturnsResponseWhenSucceeded) {
	auto refResponse = new NiceMock<ResponseMock>();
	ON_CALL(*refResponse, statusCode())
		.WillByDefault(Return(200)); // HTTP 200 OK
	auto conn = std::make_shared<StrictMock<ConnectionMock>>();
	Connection::Url url("https://retdec.com/service/api");
	Connection::RequestArguments args;
	Connection::RequestFiles files;
	EXPECT_CALL(*conn, sendPostRequestProxy(url, args, files))
		.WillOnce(Return(refResponse));
	ResponseVerifyingConnection rvconn(conn);

	auto response = rvconn.sendPostRequest(url, args, files);

	ASSERT_EQ(refResponse, response.get());
}

TEST_F(ResponseVerifyingConnectionTests,
SendPostRequestCallsSendGetRequestOnWrappedConnectionAndThrowsApiErrorWhenFailed) {
	auto response = responseForFailedRequest();
	auto conn = std::make_shared<StrictMock<ConnectionMock>>();
	Connection::Url url("https://retdec.com/service/api");
	Connection::RequestArguments args;
	Connection::RequestFiles files;
	EXPECT_CALL(*conn, sendPostRequestProxy(url, args, files))
		.WillOnce(Return(response.release()));
	ResponseVerifyingConnection rvconn(conn);

	ASSERT_THROW(rvconn.sendPostRequest(url, args, files), ApiError);
}

} // namespace tests
} // namespace internal
} // namespace retdec
