///
/// @file      retdec/internal/service_with_resources_impl.cpp
/// @copyright (c) 2015-2017 by Petr Zemek (s3rvac@gmail.com) and contributors
/// @license   MIT, see the @c LICENSE file for more details
/// @brief     Implementation of the base class of private implementations of
///            services with resources.
///

#include "retdec/internal/service_with_resources_impl.h"

namespace retdec {
namespace internal {

///
/// Constructs a private implementation.
///
/// @param[in] settings Settings for the service.
/// @param[in] connectionManager Manager of connections.
/// @param[in] serviceName Name of the service.
/// @param[in] resourcesName Name of the resources (plural).
///
ServiceWithResourcesImpl::ServiceWithResourcesImpl(const Settings &settings,
		const std::shared_ptr<ConnectionManager> &connectionManager,
		const std::string &serviceName,
		const std::string &resourcesName):
	ServiceImpl(settings, connectionManager, serviceName),
	resourcesUrl(baseUrl + "/" + resourcesName) {}

///
/// Destructs the private implementation.
///
ServiceWithResourcesImpl::~ServiceWithResourcesImpl() = default;

} // namespace internal
} // namespace retdec
