///
/// @file      retdec/internal/connection_manager_mock.h
/// @copyright (c) 2015 by Petr Zemek (s3rvac@gmail.com) and contributors
/// @license   MIT, see the @c LICENSE file for more details
/// @brief     Mock for ConnectionManager.
///

#ifndef RETDEC_INTERNAL_CONNECTION_MANAGER_MOCK_H
#define RETDEC_INTERNAL_CONNECTION_MANAGER_MOCK_H

#include <gmock/gmock.h>

#include "retdec/internal/connection_manager.h"

namespace retdec {
namespace internal {
namespace tests {

///
/// Mock for ConnectionManager.
///
class ConnectionManagerMock: public ConnectionManager {
public:
	ConnectionManagerMock() = default;
	virtual ~ConnectionManagerMock() override = default;

	MOCK_METHOD1(newConnection, std::shared_ptr<Connection> (const Settings &settings));
};

} // namespace tests
} // namespace internal
} // namespace retdec

#endif
