///
/// @file      retdec/internal/service_impl.cpp
/// @copyright (c) 2015-2017 by Petr Zemek (s3rvac@gmail.com) and contributors
/// @license   MIT, see the @c LICENSE file for more details
/// @brief     Implementation of the base class of private service
///            implementations.
///

#include "retdec/internal/service_impl.h"
#include "retdec/resource_arguments.h"

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

///
/// Constructs Connection::RequestArguments from the given resource arguments.
///
Connection::RequestArguments ServiceImpl::createRequestArguments(
		const ResourceArguments &args) const {
	return Connection::RequestArguments(
		args.argumentsBegin(), args.argumentsEnd()
	);
}

///
/// Constructs Connection::RequestFiles from the given resource arguments.
///
Connection::RequestFiles ServiceImpl::createRequestFiles(
		const ResourceArguments &args) const {
	return Connection::RequestFiles(
		args.filesBegin(), args.filesEnd()
	);
}

} // namespace internal
} // namespace retdec
