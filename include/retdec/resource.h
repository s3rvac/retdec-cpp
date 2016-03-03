///
/// @file      resource.h
/// @copyright (c) 2015-2016 by Petr Zemek (s3rvac@gmail.com) and contributors
/// @license   MIT, see the @c LICENSE file for more details
/// @brief     Base class of all resources.
///

#ifndef RETDEC_RESOURCE_H
#define RETDEC_RESOURCE_H

namespace retdec {

///
/// Base class of all resources.
///
class Resource {
public:
	Resource();
	virtual ~Resource() = 0;

	/// @name Disabled
	/// @{
	Resource(const Resource &) = delete;
	Resource(Resource &&) = delete;
	Resource &operator=(const Resource &) = delete;
	Resource &operator=(Resource &&) = delete;
	/// @}
};

} // namespace retdec

#endif
