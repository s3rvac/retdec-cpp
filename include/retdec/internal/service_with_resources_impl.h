///
/// @file      retdec/internal/service_with_resources_impl.h
/// @copyright (c) 2015 by Petr Zemek (s3rvac@gmail.com) and contributors
/// @license   MIT, see the @c LICENSE file for more details
/// @brief     Base class of private implementation of services with resources.
///

#ifndef RETDEC_INTERNAL_SERVICE_WITH_RESOURCES_IMPL_H
#define RETDEC_INTERNAL_SERVICE_WITH_RESOURCES_IMPL_H

#include <memory>
#include <string>

#include <json/json.h>

#include "retdec/internal/connection_manager.h"
#include "retdec/internal/service_impl.h"

namespace retdec {
namespace internal {

///
/// Base class of private implementation of services.
///
class ServiceWithResourcesImpl: public ServiceImpl {
public:
	ServiceWithResourcesImpl(const Settings &settings,
		const std::shared_ptr<ConnectionManager> &connectionManager,
		const std::string &serviceName,
		const std::string &resourcesName);
	virtual ~ServiceWithResourcesImpl() override;

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

	/// URL to resources.
	const std::string resourcesUrl;
};

} // namespace internal
} // namespace retdec

#endif
