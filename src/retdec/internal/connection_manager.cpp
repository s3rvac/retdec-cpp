///
/// @file      retdec/internal/connection_manager.cpp
/// @copyright (c) 2015 by Petr Zemek (s3rvac@gmail.com) and contributors
/// @license   MIT, see the @c LICENSE file for more details
/// @brief     Implementation of the base class for managers of connections to
///            the API.
///

#include "retdec/internal/connection_manager.h"

namespace retdec {
namespace internal {

///
/// Constructs a connection manager.
///
ConnectionManager::ConnectionManager() = default;

///
/// Destructs the connection manager.
///
ConnectionManager::~ConnectionManager() = default;

/// @fn ConnectionManager::newConnection()
///
/// Creates a new connection.
///

} // namespace internal
} // namespace retdec
