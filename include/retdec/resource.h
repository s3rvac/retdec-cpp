///
/// @file      resource.h
/// @copyright (c) 2015-2017 by Petr Zemek (s3rvac@gmail.com) and contributors
/// @license   MIT, see the @c LICENSE file for more details
/// @brief     Base class of all resources.
///

#ifndef RETDEC_RESOURCE_H
#define RETDEC_RESOURCE_H

#include <memory>

namespace retdec {

namespace internal {

class ResourceImpl;

} // namespace internal

///
/// Base class of all resources.
///
class Resource {
public:
	/// @cond internal
	Resource(std::unique_ptr<internal::ResourceImpl> impl);
	/// @endcond
	virtual ~Resource() = 0;

	/// @name Querying
	/// @{
	std::string getId() const;
	bool hasFinished();
	bool hasFinished() const noexcept;
	bool hasSucceeded();
	bool hasSucceeded() const noexcept;
	bool hasFailed();
	bool hasFailed() const noexcept;
	std::string getError();
	std::string getError() const;
	/// @}

	/// @name Disabled
	/// @{
	Resource(const Resource &) = delete;
	Resource(Resource &&) = delete;
	Resource &operator=(const Resource &) = delete;
	Resource &operator=(Resource &&) = delete;
	/// @}

protected:
	/// Private implementation.
	std::unique_ptr<internal::ResourceImpl> pimpl;
};

} // namespace retdec

#endif
