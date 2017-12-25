///
/// @file      retdec/internal/connection_mock.h
/// @copyright (c) 2015-2017 by Petr Zemek (s3rvac@gmail.com) and contributors
/// @license   MIT, see the @c LICENSE file for more details
/// @brief     Mock for Connection.
///

#ifndef RETDEC_INTERNAL_CONNECTION_MOCK_H
#define RETDEC_INTERNAL_CONNECTION_MOCK_H

#include <gmock/gmock.h>

#include "retdec/file.h"
#include "retdec/internal/connection.h"

namespace retdec {
namespace internal {
namespace tests {

///
/// Mock for Connection::Response.
///
class ResponseMock: public Connection::Response {
public:
	ResponseMock() = default;
	virtual ~ResponseMock() override = default;

	MOCK_CONST_METHOD0(statusCode, int());
	MOCK_CONST_METHOD0(statusMessage, std::string ());
	MOCK_CONST_METHOD0(body, std::string ());
	MOCK_CONST_METHOD0(bodyAsJson, Json::Value ());

	// A workaround is needed due to the lack of support of non-copyable return
	// types/parameters in Google Mock.
	// http://stackoverflow.com/a/11548191/2580955
	virtual std::unique_ptr<File> bodyAsFile() const override {
		return std::unique_ptr<File>(bodyAsFileProxy());
	}
	MOCK_CONST_METHOD0(bodyAsFileProxy, File * ());
};

///
/// Mock for Connection.
///
class ConnectionMock: public Connection {
public:
	ConnectionMock() = default;
	virtual ~ConnectionMock() override = default;

	MOCK_CONST_METHOD0(getApiUrl, Url());

	// Workarounds are needed due to the lack of support of non-copyable return
	// types/parameters in Google Mock.
	// http://stackoverflow.com/a/11548191/2580955

	virtual std::unique_ptr<Response> sendGetRequest(const Url &url) override {
		return std::unique_ptr<Response>(sendGetRequestProxy(url));
	}
	MOCK_METHOD1(sendGetRequestProxy, Response * (const Url &));

	virtual std::unique_ptr<Response> sendGetRequest(const Url &url,
			const RequestArguments &args) override {
		return std::unique_ptr<Response>(sendGetRequestProxy(url, args));
	}
	MOCK_METHOD2(sendGetRequestProxy, Response * (const Url &,
		const RequestArguments &));

	virtual std::unique_ptr<Response> sendPostRequest(const Url &url,
			const RequestArguments &args,
			const RequestFiles &files) override {
		return std::unique_ptr<Response>(sendPostRequestProxy(url, args, files));
	}
	MOCK_METHOD3(sendPostRequestProxy, Response * (const Url &,
		const RequestArguments &, const RequestFiles &));
};

} // namespace tests
} // namespace internal
} // namespace retdec

#endif
