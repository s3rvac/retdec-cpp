///
/// @file      retdec/service.cpp
/// @copyright (c) 2015-2017 by Petr Zemek (s3rvac@gmail.com) and contributors
/// @license   MIT, see the @c LICENSE file for more details
/// @brief     Implementation of the base class of all services.
///

#include "retdec/internal/service_impl.h"
#include "retdec/service.h"

namespace retdec {

///
/// Constructs a service.
///
Service::Service(std::unique_ptr<internal::ServiceImpl> impl):
	pimpl(std::move(impl)) {}

///
/// Destructs the service.
///
Service::~Service() = default;

} // namespace retdec
