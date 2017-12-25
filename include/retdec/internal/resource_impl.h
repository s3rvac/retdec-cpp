///
/// @file      retdec/internal/resource_impl.h
/// @copyright (c) 2015-2017 by Petr Zemek (s3rvac@gmail.com) and contributors
/// @license   MIT, see the @c LICENSE file for more details
/// @brief     Base class of private implementation of resources.
///

#ifndef RETDEC_INTERNAL_RESOURCE_IMPL_H
#define RETDEC_INTERNAL_RESOURCE_IMPL_H

#include <memory>
#include <string>

#include <json/json.h>

#include "retdec/internal/connection.h"

namespace retdec {
namespace internal {

class ResponseVerifyingConnection;

///
/// Base class of private implementation of resources.
///
class ResourceImpl {
public:
	ResourceImpl(
		const std::string &id,
		const std::shared_ptr<Connection> &conn,
		const std::string &serviceName,
		const std::string &resourcesName
	);
	virtual ~ResourceImpl();

	/// @name Status Update
	/// @{
	bool shouldUpdateStatus();
	void updateStatus();
	void updateStatusIfNeeded();

	virtual void updateResourceSpecificStatus(const Json::Value &jsonBody);
	/// @}

	/// Identifier.
	const std::string id;

	/// Connection to the API.
	const std::shared_ptr<ResponseVerifyingConnection> conn;

	/// Base URL of the resource.
	const Connection::Url baseUrl;

	/// URL to obtain the status of the resource.
	const Connection::Url statusUrl;

	/// Has the resource finished?
	bool finished = false;

	/// Has the resource succeeded?
	bool succeeded = false;

	/// Has the resource failed?
	bool failed = false;

	/// Error message.
	std::string error;
};

} // namespace internal
} // namespace retdec

#endif
