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

namespace retdec {

class File;

namespace internal {

class Connection;

} // namespace internal

///
/// Representation of a decompilation.
///
class Decompilation {
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
	~Decompilation();

	/// @name Querying
	/// @{
	std::string getId() const;
	bool hasFinished();
	bool hasFinished() const noexcept;
	bool hasSucceeded();
	bool hasSucceeded() const noexcept;
	bool hasFailed();
	bool hasFailed() const noexcept;
	int getCompletion();
	int getCompletion() const noexcept;
	std::string getError();
	std::string getError() const;
	/// @}

	/// @name Waiting For Decompilation To Finish
	/// @{
	void waitUntilFinished(OnError onError = OnError::Throw);
	void waitUntilFinished(const Callback &callback,
		OnError onError = OnError::Throw);
	/// @}

	/// @name Getting Outputs
	/// @{
	std::shared_ptr<File> getOutputHllFile();
	std::string getOutputHll();
	/// @}

	/// @name Disabled
	/// @{
	Decompilation(const Decompilation &) = delete;
	Decompilation(Decompilation &&) = delete;
	Decompilation &operator=(const Decompilation &) = delete;
	Decompilation &operator=(Decompilation &&) = delete;
	/// @}

private:
	struct Impl;
	/// Private implementation.
	std::unique_ptr<Impl> impl;
};

} // namespace retdec

#endif
