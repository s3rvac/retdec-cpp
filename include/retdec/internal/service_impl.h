///
/// @file      retdec/internal/service_impl.h
/// @copyright (c) 2015-2016 by Petr Zemek (s3rvac@gmail.com) and contributors
/// @license   MIT, see the @c LICENSE file for more details
/// @brief     Base class for private implementation of services.
///

#ifndef RETDEC_INTERNAL_SERVICE_IMPL_H
#define RETDEC_INTERNAL_SERVICE_IMPL_H

#include <string>

#include "retdec/settings.h"

namespace retdec {
namespace internal {

class ConnectionManager;

///
/// Base class for private implementation of services.
///
class ServiceImpl {
public:
	ServiceImpl(const Settings &settings,
		const std::shared_ptr<ConnectionManager> &connectionManager,
		const std::string &serviceName);
	virtual ~ServiceImpl();

	/// Settings.
	const Settings settings;

	/// Connection manager.
	const std::shared_ptr<ConnectionManager> connectionManager;

	/// Base URL.
	const std::string baseUrl;
};

} // namespace internal
} // namespace retdec

#endif
