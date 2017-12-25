///
/// @file      retdec/internal/utilities/container.h
/// @copyright (c) 2015-2017 by Petr Zemek (s3rvac@gmail.com) and contributors
/// @license   MIT, see the @c LICENSE file for more details
/// @brief     Utilities for containers.
///

#ifndef RETDEC_INTERNAL_UTILITIES_CONTAINER_H
#define RETDEC_INTERNAL_UTILITIES_CONTAINER_H

namespace retdec {
namespace internal {

/// @name Map
/// @{

///
/// Has @a map the given key?
///
template <typename Map, typename Key>
inline bool hasKey(const Map &map, const Key &key) {
	return map.find(key) != map.end();
}

///
/// Returns the value of the given key in @a map or the default value.
///
template <typename Map, typename Key>
inline typename Map::mapped_type getValue(const Map &map,
		const Key &key) {
	auto it = map.find(key);
	return it != map.end() ? it->second : typename Map::mapped_type();
}

/// @}

} // namespace internal
} // namespace retdec

#endif
