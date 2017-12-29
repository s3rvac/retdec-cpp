///
/// @file      retdec/internal/utilities/smart_ptr.h
/// @copyright (c) 2015 by Petr Zemek (s3rvac@gmail.com) and contributors
/// @license   MIT, see the @c LICENSE file for more details
/// @brief     Utilities for smart pointers.
///

#ifndef RETDEC_INTERNAL_UTILITIES_SMART_PTR_H
#define RETDEC_INTERNAL_UTILITIES_SMART_PTR_H

#include <memory>

namespace retdec {
namespace internal {

/// @name Smart Pointers
/// @{

///
/// Casts the given shared pointer to a pointer of a different type.
///
/// @param[in] ptr Pointer to be casted.
///
/// @tparam To Output type.
/// @tparam From Input type.
///
/// It represents a more concise alternative to
/// <tt>std::dynamic_pointer_cast<To>(ptr)</tt>.
///
template <typename To, typename From>
std::shared_ptr<To> cast(const std::shared_ptr<From> &ptr) noexcept {
	return std::dynamic_pointer_cast<To>(ptr);
}

///
/// Checks if @a ptr is of type @c To or can be casted from @c From to @c To.
///
/// @param[in] ptr Pointer to be tested.
///
/// @tparam To Output type.
/// @tparam From Input type.
///
/// It represents a more concise and readable alternative to
/// <tt>std::dynamic_pointer_cast<To>(ptr) != nullptr</tt>.
///
template <typename To, typename From>
bool isa(const std::shared_ptr<From> &ptr) noexcept {
	return cast<To>(ptr) != nullptr;
}

/// @}

} // namespace internal
} // namespace retdec

#endif
