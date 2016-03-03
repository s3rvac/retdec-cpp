///
/// @file      retdec/service.h
/// @copyright (c) 2015-2016 by Petr Zemek (s3rvac@gmail.com) and contributors
/// @license   MIT, see the @c LICENSE file for more details
/// @brief     Base class of all services.
///

#ifndef RETDEC_SERVICE_H
#define RETDEC_SERVICE_H

namespace retdec {

///
/// Base class of all services.
///
class Service {
public:
	/// @name Construction and Destruction
	/// @{
	Service();
	virtual ~Service() = 0;
	/// @}

	/// @name Disabled
	/// @{
	Service(const Service &) = delete;
	Service(Service &&) = delete;
	Service &operator=(const Service &) = delete;
	Service &operator=(Service &&) = delete;
	/// @}
};

} // namespace retdec

#endif
