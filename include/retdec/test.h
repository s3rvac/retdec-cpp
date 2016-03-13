///
/// @file      retdec/test.h
/// @copyright (c) 2015-2016 by Petr Zemek (s3rvac@gmail.com) and contributors
/// @license   MIT, see the @c LICENSE file for more details
/// @brief     Testing service.
///

#ifndef RETDEC_TEST_H
#define RETDEC_TEST_H

#include <memory>

#include "retdec/service.h"

namespace retdec {

class Settings;

namespace internal {

class ConnectionManager;
class TestImpl;

} // namespace internal

///
/// Runner of analyses.
///
class Test: public Service {
public:
	/// @name Construction and Destruction
	/// @{
	Test(const Settings &settings);
	/// @cond internal
	Test(const Settings &settings,
		const std::shared_ptr<::retdec::internal::ConnectionManager> &connectionManager);
	/// @endcond
	virtual ~Test() override;
	/// @}

	/// @name Testing
	/// @{
	void auth();
	/// @}

private:
	internal::TestImpl *impl() noexcept;
	const internal::TestImpl *impl() const noexcept;
};

} // namespace retdec

#endif
