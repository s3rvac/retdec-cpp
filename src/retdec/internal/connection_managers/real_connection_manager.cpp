///
/// @file      retdec/internal/connection_managers/real_connection_manager.cpp
/// @copyright (c) 2015-2017 by Petr Zemek (s3rvac@gmail.com) and contributors
/// @license   MIT, see the @c LICENSE file for more details
/// @brief     Implementation of the manager of connections to the API.
///

#include "retdec/internal/connection_managers/real_connection_manager.h"
#include "retdec/internal/connections/real_connection.h"

namespace retdec {
namespace internal {

///
/// Constructs a manager.
///
RealConnectionManager::RealConnectionManager() = default;

// Override.
RealConnectionManager::~RealConnectionManager() = default;

// Override.
std::shared_ptr<Connection> RealConnectionManager::newConnection(const Settings &settings) {
	return std::make_shared<RealConnection>(settings);
}

} // namespace internal
} // namespace retdec
