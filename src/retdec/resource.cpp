///
/// @file      retdec/resource.cpp
/// @copyright (c) 2015-2017 by Petr Zemek (s3rvac@gmail.com) and contributors
/// @license   MIT, see the @c LICENSE file for more details
/// @brief     Implementation of the base class of all resources.
///

#include "retdec/internal/resource_impl.h"
#include "retdec/resource.h"

namespace retdec {

///
/// Constructs a resource.
///
Resource::Resource(std::unique_ptr<internal::ResourceImpl> impl):
	pimpl(std::move(impl)) {}

///
/// Destructs the resource.
///
Resource::~Resource() = default;

///
/// Returns the ID of the resource.
///
/// Does not access the API.
///
std::string Resource::getId() const {
	return pimpl->id;
}

///
/// Has the resource finished?
///
/// May access the API.
///
bool Resource::hasFinished() {
	pimpl->updateStatusIfNeeded();
	return pimpl->finished;
}

///
/// Has the resource finished?
///
/// Does not access the API.
///
bool Resource::hasFinished() const noexcept {
	return pimpl->finished;
}

///
/// Has the resource succeeded?
///
/// The output from this function is meaningful only if hasFinished() returns
/// @c true.
///
/// May access the API.
///
bool Resource::hasSucceeded() {
	pimpl->updateStatusIfNeeded();
	return pimpl->succeeded;
}

///
/// Has the resource succeeded?
///
/// The output from this function is meaningful only if hasFinished() returns
/// @c true.
///
/// Does not access the API.
///
bool Resource::hasSucceeded() const noexcept {
	return pimpl->succeeded;
}

///
/// Has the resource failed?
///
/// The output from this function is meaningful only if hasFinished() returns
/// @c true.
///
/// May access the API.
///
bool Resource::hasFailed() {
	pimpl->updateStatusIfNeeded();
	return pimpl->failed;
}

///
/// Has the resource failed?
///
/// The output from this function is meaningful only if hasFinished() returns
/// @c true.
///
/// Does not access the API.
///
bool Resource::hasFailed() const noexcept {
	return pimpl->failed;
}

///
/// Returns the error message (if any).
///
/// The output from this function is meaningful only if hasFinished() returns
/// @c true and hasFailed() returns @c true.
///
/// May access the API.
///
std::string Resource::getError() {
	pimpl->updateStatusIfNeeded();
	return pimpl->error;
}

///
/// Returns the error message (if any).
///
/// The output from this function is meaningful only if hasFinished() returns
/// @c true and hasFailed() returns @c true.
///
/// Does not access the API.
///
std::string Resource::getError() const {
	return pimpl->error;
}

} // namespace retdec
