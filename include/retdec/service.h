///
/// @file      retdec/service.h
/// @copyright (c) 2015-2016 by Petr Zemek (s3rvac@gmail.com) and contributors
/// @license   MIT, see the @c LICENSE file for more details
/// @brief     Base class of all services.
///

#ifndef RETDEC_SERVICE_H
#define RETDEC_SERVICE_H

#include <memory>

namespace retdec {

namespace internal {

class ServiceImpl;

} // namespace internal

///
/// Base class of all services.
///
class Service {
public:
	/// @cond internal
	Service(std::unique_ptr<internal::ServiceImpl> impl);
	/// @endcond
	virtual ~Service() = 0;

	/// @name Disabled
	/// @{
	Service(const Service &) = delete;
	Service(Service &&) = delete;
	Service &operator=(const Service &) = delete;
	Service &operator=(Service &&) = delete;
	/// @}

protected:
	/// Private implementation.
	std::unique_ptr<internal::ServiceImpl> pimpl;
};

} // namespace retdec

#endif
