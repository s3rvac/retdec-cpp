///
/// @file      retdec/internal/connection_managers/real_connection_manager.h
/// @copyright (c) 2015-2016 by Petr Zemek (s3rvac@gmail.com) and contributors
/// @license   MIT, see the @c LICENSE file for more details
/// @brief     Manager of connections to the API.
///

#ifndef RETDEC_INTERNAL_CONNECTION_MANAGERS_REAL_CONNECTION_MANAGER_H
#define RETDEC_INTERNAL_CONNECTION_MANAGERS_REAL_CONNECTION_MANAGER_H

#include "retdec/internal/connection_manager.h"

namespace retdec {
namespace internal {

///
/// Manager of connections to the API.
///
class RealConnectionManager: public ConnectionManager {
public:
	RealConnectionManager();
	virtual ~RealConnectionManager() override;

	virtual std::shared_ptr<Connection> newConnection(
		const Settings &settings) override;
};

} // namespace internal
} // namespace retdec

#endif
