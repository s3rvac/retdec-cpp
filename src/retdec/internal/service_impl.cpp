///
/// @file      retdec/internal/service_impl.cpp
/// @copyright (c) 2015-2016 by Petr Zemek (s3rvac@gmail.com) and contributors
/// @license   MIT, see the @c LICENSE file for more details
/// @brief     Implementation of the base class of private service
///            implementations.
///

#include "retdec/internal/service_impl.h"
#include "retdec/internal/utilities/connection.h"

namespace retdec {
namespace internal {

///
/// Constructs a private implementation.
///
/// @param[in] settings Settings for the service.
/// @param[in] connectionManager Manager of connections.
/// @param[in] serviceName Name of the service.
///
ServiceImpl::ServiceImpl(const Settings &settings,
		const std::shared_ptr<ConnectionManager> &connectionManager,
		const std::string &serviceName):
	settings(settings),
	connectionManager(connectionManager),
	baseUrl(settings.apiUrl() + "/" + serviceName) {}

///
/// Destructs the private implementation.
///
ServiceImpl::~ServiceImpl() = default;

} // namespace internal
} // namespace retdec
