///
/// @file      retdec/decompiler.h
/// @copyright (c) 2015 by Petr Zemek (s3rvac@gmail.com) and contributors
/// @license   MIT, see the @c LICENSE file for more details
/// @brief     Runner of decompilations.
///

#ifndef RETDEC_DECOMPILER_H
#define RETDEC_DECOMPILER_H

#include <memory>

namespace retdec {

class Decompilation;
class DecompilationArguments;
class Settings;

namespace internal {

class ConnectionManager;

} // namespace internal

///
/// Runner of decompilations.
///
class Decompiler {
public:
	/// @name Construction and Destruction
	/// @{
	Decompiler(const Settings &settings);
	/// @cond internal
	Decompiler(const Settings &settings,
		const std::shared_ptr<::retdec::internal::ConnectionManager> &connectionManager);
	/// @endcond
	~Decompiler();
	/// @}

	/// @name Decompilations
	/// @{
	std::unique_ptr<Decompilation> runDecompilation(
		const DecompilationArguments &args);
	/// @}

	/// @name Disabled
	/// @{
	Decompiler(const Decompiler &) = delete;
	Decompiler(Decompiler &&) = delete;
	Decompiler &operator=(const Decompiler &) = delete;
	Decompiler &operator=(Decompiler &&) = delete;
	/// @}

private:
	struct Impl;
	/// Private implementation.
	std::unique_ptr<Impl> impl;
};

} // namespace retdec

#endif
