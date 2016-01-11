///
/// @file      retdec/internal/connections/real_connection.h
/// @copyright (c) 2015-2016 by Petr Zemek (s3rvac@gmail.com) and contributors
/// @license   MIT, see the @c LICENSE file for more details
/// @brief     Connection to the API.
///

#ifndef RETDEC_INTERNAL_CONNECTIONS_REAL_CONNECTION_H
#define RETDEC_INTERNAL_CONNECTIONS_REAL_CONNECTION_H

#include <memory>

#include "retdec/internal/connection.h"

namespace retdec {

class Settings;

namespace internal {

///
/// Connection to the API.
///
class RealConnection: public Connection {
public:
	RealConnection(const Settings &settings);
	virtual ~RealConnection() override;

	virtual Url getApiUrl() const override;

	virtual std::unique_ptr<Response> sendGetRequest(const Url &url) override;
	virtual std::unique_ptr<Response> sendGetRequest(const Url &url,
		const RequestArguments &args) override;
	virtual std::unique_ptr<Response> sendPostRequest(const Url &url,
		const RequestArguments &args, const RequestFiles &files) override;

private:
	struct Impl;
	/// Private implementation.
	std::unique_ptr<Impl> impl;
};

} // namespace internal
} // namespace retdec

#endif
