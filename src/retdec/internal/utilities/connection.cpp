///
/// @file      retdec/internal/utilities/connection.cpp
/// @copyright (c) 2015-2017 by Petr Zemek (s3rvac@gmail.com) and contributors
/// @license   MIT, see the @c LICENSE file for more details
/// @brief     Implementation of the connection utilities.
///

#include <json/json.h>

#include "retdec/exceptions.h"
#include "retdec/internal/utilities/connection.h"
#include "retdec/internal/utilities/json.h"

namespace retdec {
namespace internal {

namespace {

///
/// Throws ApiError or its subclass, depending on @a code.
///
void throwApiError(int code, const std::string &message,
		const std::string &description = "") {
	if (code == 401) {
		throw AuthError(code, message, description);
	}
	throw ApiError(code, message, description);
}

} // anonymous namespace

///
/// Checks if a request resulted in the given @a response succeeded.
///
bool requestSucceeded(const Connection::Response &response) {
	// Status codes other than 2xx signalize a failure.
	auto code = response.statusCode();
	return code >= 200 && code <= 299;
}

///
/// Verifies that a request resulted in the given @a response succeeded.
///
/// @throws ApiError When the request failed.
///
void verifyRequestSucceeded(const Connection::Response &response) {
	if (!requestSucceeded(response)) {
		try {
			auto jsonBody = response.bodyAsJson();
			return throwApiError(
				jsonBody.get("code", response.statusCode()).asInt(),
				jsonBody.get("message", response.statusMessage()).asString(),
				jsonBody.get("description", "").asString()
			);
		} catch (const JsonDecodingError &) {
			return throwApiError(
				response.statusCode(),
				response.statusMessage()
			);
		}
	}
}

///
/// Creates a verifying connection by wrapping a connection.
///
ResponseVerifyingConnection::ResponseVerifyingConnection(
		const std::shared_ptr<Connection> &conn):
	conn(conn) {}

///
/// Destructs the connection.
///
ResponseVerifyingConnection::~ResponseVerifyingConnection() {}

// Override.
Connection::Url ResponseVerifyingConnection::getApiUrl() const {
	return conn->getApiUrl();
}

// Override.
std::unique_ptr<Connection::Response> ResponseVerifyingConnection::sendGetRequest(
		const Url &url) {
	auto response = conn->sendGetRequest(url);
	verifyRequestSucceeded(*response);
	return response;
}

// Override.
std::unique_ptr<Connection::Response> ResponseVerifyingConnection::sendGetRequest(
		const Connection::Url &url, const RequestArguments &args) {
	auto response = conn->sendGetRequest(url, args);
	verifyRequestSucceeded(*response);
	return response;
}

// Override.
std::unique_ptr<Connection::Response> ResponseVerifyingConnection::sendPostRequest(
		const Url &url, const RequestArguments &args,
		const RequestFiles &files) {
	auto response = conn->sendPostRequest(url, args, files);
	verifyRequestSucceeded(*response);
	return response;
}

} // namespace internal
} // namespace retdec
