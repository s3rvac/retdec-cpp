///
/// @file      retdec/internal/utilities/connection.h
/// @copyright (c) 2015-2016 by Petr Zemek (s3rvac@gmail.com) and contributors
/// @license   MIT, see the @c LICENSE file for more details
/// @brief     Connection utilities.
///

#ifndef RETDEC_INTERNAL_UTILITIES_CONNECTION_H
#define RETDEC_INTERNAL_UTILITIES_CONNECTION_H

#include <memory>

#include "retdec/internal/connection.h"

namespace retdec {
namespace internal {

bool requestSucceeded(const Connection::Response &response);
void verifyRequestSucceeded(const Connection::Response &response);

///
/// Connection wrapper verifying that requests succeed.
///
/// This class wraps an existing connection. Then, when a response from a
/// GET/POST request is received, it verifies that the request succeeded. If it
/// failed, it throws ApiError or its subclass.
///
class ResponseVerifyingConnection: public Connection {
public:
	ResponseVerifyingConnection(const std::shared_ptr<Connection> &conn);
	virtual ~ResponseVerifyingConnection();

	virtual Url getApiUrl() const override;
	virtual std::unique_ptr<Response> sendGetRequest(const Url &url) override;
	virtual std::unique_ptr<Response> sendGetRequest(const Url &url,
		const RequestArguments &args) override;
	virtual std::unique_ptr<Response> sendPostRequest(const Url &url,
		const RequestArguments &args, const RequestFiles &files) override;

private:
	/// Wrapped connection.
	std::shared_ptr<Connection> conn;
};

} // namespace internal
} // namespace retdec

#endif
