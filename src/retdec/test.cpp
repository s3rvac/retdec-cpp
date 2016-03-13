///
/// @file      retdec/test.cpp
/// @copyright (c) 2015-2016 by Petr Zemek (s3rvac@gmail.com) and contributors
/// @license   MIT, see the @c LICENSE file for more details
/// @brief     Implementation of the testing service.
///

#include <string>

#include "retdec/internal/connection_managers/real_connection_manager.h"
#include "retdec/internal/service_impl.h"
#include "retdec/settings.h"
#include "retdec/test.h"

using namespace retdec::internal;

namespace retdec {
namespace internal {

///
/// Private implementation of Test.
///
class TestImpl: public ServiceImpl {
public:
	TestImpl(const Settings &settings,
		const std::shared_ptr<ConnectionManager> &connectionManager);
	virtual ~TestImpl() override;

	/// URL to the @c echo sub-service.
	const std::string echoUrl;
};

///
/// Constructs a private implementation.
///
/// @param[in] settings Settings for the service.
/// @param[in] connectionManager Manager of connections.
///
TestImpl::TestImpl(const Settings &settings,
		const std::shared_ptr<ConnectionManager> &connectionManager):
	ServiceImpl(settings, connectionManager, "test"),
	echoUrl(baseUrl + "/" + "echo") {}

// Override.
TestImpl::~TestImpl() = default;

} // namespace internal

///
/// Constructs a test with the given settings.
///
Test::Test(const Settings &settings):
	Test(settings, std::make_shared<RealConnectionManager>()) {}

///
/// Constructs a test with the given settings and connection manager.
///
Test::Test(const Settings &settings,
		// The qualification in ::ConnectionManager below has to be be used due
		// to Doxygen limitations.
		const std::shared_ptr<::ConnectionManager> &connectionManager):
	Service(std::make_unique<TestImpl>(settings, connectionManager)) {}

// Override.
Test::~Test() = default;

///
/// Tries to authenticate.
///
/// @throws ApiError When the authentication fails.
///
/// Does nothing when the authentication succeeds.
///
void Test::auth() {
	auto conn = impl()->connectionManager->newConnection(impl()->settings);
	// We do not need any parameters; simply send a GET request to /test/echo,
	// and if the authentication fails, ApiError will be automatically thrown.
	auto response = conn->sendGetRequest(impl()->echoUrl);
	verifyRequestSucceeded(*response);
}

///
/// Returns a properly cast private implementation.
///
TestImpl *Test::impl() noexcept {
	return static_cast<TestImpl *>(pimpl.get());
}

///
/// Constant overload of impl().
///
const TestImpl *Test::impl() const noexcept {
	return static_cast<const TestImpl *>(pimpl.get());
}

} // namespace retdec
