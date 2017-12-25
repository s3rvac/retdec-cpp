///
/// @file      retdec/internal/connection_manager.h
/// @copyright (c) 2015-2017 by Petr Zemek (s3rvac@gmail.com) and contributors
/// @license   MIT, see the @c LICENSE file for more details
/// @brief     Base class of managers of connections to the API.
///

#ifndef RETDEC_INTERNAL_CONNECTION_MANAGER_H
#define RETDEC_INTERNAL_CONNECTION_MANAGER_H

#include <memory>

namespace retdec {

class Settings;

namespace internal {

class Connection;

///
/// Base class of managers of connections to the API.
///
class ConnectionManager {
public:
	virtual ~ConnectionManager() = 0;

	virtual std::shared_ptr<Connection> newConnection(const Settings &settings) = 0;

protected:
	ConnectionManager();
};

} // namespace internal
} // namespace retdec

#endif
