///
/// @file      retdec/decompilation.h
/// @copyright (c) 2015 by Petr Zemek (s3rvac@gmail.com) and contributors
/// @license   MIT, see the @c LICENSE file for more details
/// @brief     Representation of a decompilation.
///

#ifndef RETDEC_DECOMPILATION_H
#define RETDEC_DECOMPILATION_H

#include <functional>
#include <memory>
#include <string>

#include "retdec/resource.h"

namespace retdec {

class File;

namespace internal {

class Connection;
class DecompilationImpl;

} // namespace internal

///
/// Representation of a decompilation.
///
class Decompilation: public Resource {
public:
	/// Type of a callback for waitUntilFinished().
	using Callback = std::function<void (const Decompilation &decompilation)>;

	///
	/// What should the waiting member functions do when a decompilation
	/// fails?
	///
	enum class OnError {
		Throw,  ///< Throw DecompilationError when a decompilation fails.
		NoThrow ///< Do not throw DecompilationError when a decompilation fails.
	};

public:
	/// @cond internal
	Decompilation(const std::string &id,
		const std::shared_ptr<::retdec::internal::Connection> &conn);
	/// @endcond
	virtual ~Decompilation() override;

	/// @name Querying
	/// @{
	int getCompletion();
	int getCompletion() const noexcept;
	/// @}

	/// @name Waiting For Decompilation To Finish
	/// @{
	void waitUntilFinished(OnError onError = OnError::Throw);
	void waitUntilFinished(const Callback &callback,
		OnError onError = OnError::Throw);
	/// @}

	/// @name Obtaining Outputs
	/// @{
	std::shared_ptr<File> getOutputHllFile();
	std::string getOutputHll();
	/// @}

private:
	internal::DecompilationImpl *impl() noexcept;
	const internal::DecompilationImpl *impl() const noexcept;
};

} // namespace retdec

#endif
