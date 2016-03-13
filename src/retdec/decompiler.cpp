///
/// @file      retdec/decompiler.cpp
/// @copyright (c) 2015-2016 by Petr Zemek (s3rvac@gmail.com) and contributors
/// @license   MIT, see the @c LICENSE file for more details
/// @brief     Implementation of the decompilation service.
///

#include "retdec/decompilation.h"
#include "retdec/decompilation_arguments.h"
#include "retdec/decompiler.h"
#include "retdec/internal/connection_managers/real_connection_manager.h"
#include "retdec/internal/service_impl.h"
#include "retdec/settings.h"

using namespace retdec::internal;

namespace retdec {
namespace internal {

///
/// Private implementation of Decompiler.
///
class DecompilerImpl: public ServiceImpl {
public:
	DecompilerImpl(const Settings &settings,
		const std::shared_ptr<ConnectionManager> &connectionManager);
	virtual ~DecompilerImpl() override;
};

///
/// Constructs a private implementation.
///
/// @param[in] settings Settings for the service.
/// @param[in] connectionManager Manager of connections.
///
DecompilerImpl::DecompilerImpl(const Settings &settings,
		const std::shared_ptr<ConnectionManager> &connectionManager):
	ServiceImpl(settings, connectionManager, "decompiler", "decompilations") {}

// Override.
DecompilerImpl::~DecompilerImpl() = default;

} // namespace internal

///
/// Constructs a decompiler with the given settings.
///
Decompiler::Decompiler(const Settings &settings):
	Decompiler(settings, std::make_shared<RealConnectionManager>()) {}

///
/// Constructs a decompiler with the given settings and connection manager.
///
Decompiler::Decompiler(const Settings &settings,
		// The qualification in ::ConnectionManager below has to be be used due
		// to Doxygen limitations.
		const std::shared_ptr<::ConnectionManager> &connectionManager):
	Service(std::make_unique<DecompilerImpl>(settings, connectionManager)) {}

// Override.
Decompiler::~Decompiler() = default;

///
/// Runs a new decompilation with the given arguments.
///
std::unique_ptr<Decompilation> Decompiler::runDecompilation(
		const DecompilationArguments &args) {
	return impl()->runResource<Decompilation>(args);
}

///
/// Returns a properly cast private implementation.
///
DecompilerImpl *Decompiler::impl() noexcept {
	return static_cast<DecompilerImpl *>(pimpl.get());
}

///
/// Constant overload of impl().
///
const DecompilerImpl *Decompiler::impl() const noexcept {
	return static_cast<const DecompilerImpl *>(pimpl.get());
}

} // namespace retdec
