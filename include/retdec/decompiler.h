///
/// @file      retdec/decompiler.h
/// @copyright (c) 2015-2017 by Petr Zemek (s3rvac@gmail.com) and contributors
/// @license   MIT, see the @c LICENSE file for more details
/// @brief     Runner of decompilations.
///

#ifndef RETDEC_DECOMPILER_H
#define RETDEC_DECOMPILER_H

#include <memory>

#include "retdec/service.h"

namespace retdec {

class Decompilation;
class DecompilationArguments;
class Settings;

namespace internal {

class DecompilerImpl;
class ConnectionManager;

} // namespace internal

///
/// Runner of decompilations.
///
class Decompiler: public Service {
public:
	/// @name Construction and Destruction
	/// @{
	Decompiler(const Settings &settings);
	/// @cond internal
	Decompiler(const Settings &settings,
		const std::shared_ptr<::retdec::internal::ConnectionManager> &connectionManager);
	/// @endcond
	virtual ~Decompiler() override;
	/// @}

	/// @name Decompilations
	/// @{
	std::unique_ptr<Decompilation> runDecompilation(
		const DecompilationArguments &args);
	/// @}

private:
	internal::DecompilerImpl *impl() noexcept;
	const internal::DecompilerImpl *impl() const noexcept;
};

} // namespace retdec

#endif
