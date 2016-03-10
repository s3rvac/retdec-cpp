///
/// @file      retdec/internal/service_impl.h
/// @copyright (c) 2015-2016 by Petr Zemek (s3rvac@gmail.com) and contributors
/// @license   MIT, see the @c LICENSE file for more details
/// @brief     Base class for private implementation of services.
///

#ifndef RETDEC_INTERNAL_SERVICE_IMPL_H
#define RETDEC_INTERNAL_SERVICE_IMPL_H

#include <memory>
#include <string>

#include <json/json.h>

#include "retdec/internal/connection_manager.h"
#include "retdec/internal/utilities/connection.h"
#include "retdec/settings.h"

namespace retdec {

class ResourceArguments;

namespace internal {

class ConnectionManager;

///
/// Base class for private implementation of services.
///
class ServiceImpl {
public:
	ServiceImpl(const Settings &settings,
		const std::shared_ptr<ConnectionManager> &connectionManager,
		const std::string &serviceName,
		const std::string &resourcesName);
	virtual ~ServiceImpl();

	/// @name Request Arguments Creation
	/// @{
	Connection::RequestArguments createRequestArguments(
		const ResourceArguments &args) const;
	Connection::RequestFiles createRequestFiles(
		const ResourceArguments &args) const;
	/// @}

	///
	/// Runs a new resource with the given arguments.
	///
	template <typename ResourceType>
	std::unique_ptr<ResourceType> runResource(const ResourceArguments &args) {
		auto conn = connectionManager->newConnection(settings);
		auto response = conn->sendPostRequest(
			resourcesUrl,
			createRequestArguments(args),
			createRequestFiles(args)
		);
		verifyRequestSucceeded(*response);
		auto jsonBody = response->bodyAsJson();
		auto id = jsonBody.get("id", "?").asString();
		return std::make_unique<ResourceType>(id, conn);
	}

	/// Settings.
	const Settings settings;

	/// Connection manager.
	const std::shared_ptr<ConnectionManager> connectionManager;

	/// Base URL.
	const std::string baseUrl;

	/// URL to resources.
	const std::string resourcesUrl;
};

} // namespace internal
} // namespace retdec

#endif
