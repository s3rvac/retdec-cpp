///
/// @file      retdec/internal/resource_impl.cpp
/// @copyright (c) 2015-2016 by Petr Zemek (s3rvac@gmail.com) and contributors
/// @license   MIT, see the @c LICENSE file for more details
/// @brief     Implementation of the base class of private resource
///            implementations.
///

#include "retdec/internal/resource_impl.h"
#include "retdec/internal/utilities/connection.h"

namespace retdec {
namespace internal {

///
/// Constructs a private implementation.
///
/// @param[in] id Identifier of the resource.
/// @param[in] conn Connection to be used to communicate with the API.
/// @param[in] serviceName Name of the service.
/// @param[in] resourcesName Name of the resources (plural).
///
ResourceImpl::ResourceImpl(
		const std::string &id,
		const std::shared_ptr<Connection> &conn,
		const std::string &serviceName,
		const std::string &resourcesName
	):
	id(id),
	conn(std::make_shared<ResponseVerifyingConnection>(conn)),
	baseUrl(conn->getApiUrl() + "/" + serviceName + "/" + resourcesName + "/" + id),
	statusUrl(baseUrl + "/status"),
	outputsUrl(baseUrl + "/outputs")
	{}

///
/// Destructs the private implementation.
///
ResourceImpl::~ResourceImpl() = default;

///
/// Should the status be updated?
///
bool ResourceImpl::shouldUpdateStatus() {
	return !finished;
}

///
/// Updates the status of the resource.
///
void ResourceImpl::updateStatus() {
	auto response = conn->sendGetRequest(statusUrl);
	auto jsonBody = response->bodyAsJson();
	finished = jsonBody.get("finished", false).asBool();
	succeeded = jsonBody.get("succeeded", false).asBool();
	failed = jsonBody.get("failed", false).asBool();
	error = jsonBody.get("error", "").asString();
	updateResourceSpecificStatus(jsonBody);
}

///
/// Updates the status (if needed).
///
void ResourceImpl::updateStatusIfNeeded() {
	if (shouldUpdateStatus()) {
		updateStatus();
	}
}

/// @fn ResourceImpl::updateResourceSpecificStatus()
///
/// Updates resource-specific parts of the status.
///

} // namespace internal
} // namespace retdec
