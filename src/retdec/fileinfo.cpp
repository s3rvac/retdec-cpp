///
/// @file      retdec/fileinfo.cpp
/// @copyright (c) 2015 by Petr Zemek (s3rvac@gmail.com) and contributors
/// @license   MIT, see the @c LICENSE file for more details
/// @brief     Implementation of the fileinfo service.
///

#include "retdec/analysis.h"
#include "retdec/analysis_arguments.h"
#include "retdec/fileinfo.h"
#include "retdec/internal/connection_managers/real_connection_manager.h"
#include "retdec/internal/service_with_resources_impl.h"
#include "retdec/settings.h"

using namespace retdec::internal;

namespace retdec {
namespace internal {

///
/// Private implementation of Fileinfo.
///
class FileinfoImpl: public ServiceWithResourcesImpl {
public:
	FileinfoImpl(const Settings &settings,
		const std::shared_ptr<ConnectionManager> &connectionManager);
	virtual ~FileinfoImpl() override;
};

///
/// Constructs a private implementation.
///
/// @param[in] settings Settings for the service.
/// @param[in] connectionManager Manager of connections.
///
FileinfoImpl::FileinfoImpl(const Settings &settings,
		const std::shared_ptr<ConnectionManager> &connectionManager):
	ServiceWithResourcesImpl(
		settings,
		connectionManager,
		"fileinfo",
		"analyses"
	) {}

// Override.
FileinfoImpl::~FileinfoImpl() = default;

} // namespace internal

///
/// Constructs a fileinfo with the given settings.
///
Fileinfo::Fileinfo(const Settings &settings):
	Fileinfo(settings, std::make_shared<RealConnectionManager>()) {}

///
/// Constructs a fileinfo with the given settings and connection manager.
///
Fileinfo::Fileinfo(const Settings &settings,
		// The qualification in ::ConnectionManager below has to be be used due
		// to Doxygen limitations.
		const std::shared_ptr<::ConnectionManager> &connectionManager):
	Service(std::make_unique<FileinfoImpl>(settings, connectionManager)) {}

// Override.
Fileinfo::~Fileinfo() = default;

///
/// Runs a new analysis with the given arguments.
///
std::unique_ptr<Analysis> Fileinfo::runAnalysis(const AnalysisArguments &args) {
	return impl()->runResource<Analysis>(args);
}

///
/// Returns a properly cast private implementation.
///
FileinfoImpl *Fileinfo::impl() noexcept {
	return static_cast<FileinfoImpl *>(pimpl.get());
}

///
/// Constant overload of impl().
///
const FileinfoImpl *Fileinfo::impl() const noexcept {
	return static_cast<const FileinfoImpl *>(pimpl.get());
}

} // namespace retdec
