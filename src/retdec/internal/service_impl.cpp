///
/// @file      retdec/internal/service_impl.cpp
/// @copyright (c) 2015-2016 by Petr Zemek (s3rvac@gmail.com) and contributors
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
/// Constructs Connection::RequestArguments from the given decompilation
/// arguments.
///
Connection::RequestArguments ServiceImpl::createRequestArguments(
		const ResourceArguments &args) const {
	Connection::RequestArguments requestArgs;
	for (auto i = args.argumentsBegin(), e = args.argumentsEnd(); i != e; ++i) {
		requestArgs.emplace_back(i->first, i->second);
	}
	return requestArgs;
}

///
/// Constructs Connection::RequestFiles from the given decompilation arguments.
///
Connection::RequestFiles ServiceImpl::createRequestFiles(
		const ResourceArguments &args) const {
	Connection::RequestFiles requestFiles;
	for (auto i = args.filesBegin(), e = args.filesEnd(); i != e; ++i) {
		requestFiles.emplace(i->first, i->second);
	}
	return requestFiles;
}

} // namespace internal
} // namespace retdec
