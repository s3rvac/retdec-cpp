///
/// @file      retdec/analysis.cpp
/// @copyright (c) 2015-2016 by Petr Zemek (s3rvac@gmail.com) and contributors
/// @license   MIT, see the @c LICENSE file for more details
/// @brief     Implementation of the analysis.
///

#include <utility>

#include <json/json.h>

#include "retdec/analysis.h"
#include "retdec/exceptions.h"
#include "retdec/file.h"
#include "retdec/internal/connections/real_connection.h"
#include "retdec/internal/resource_impl.h"
#include "retdec/internal/utilities/connection.h"
#include "retdec/internal/utilities/os.h"

using namespace retdec::internal;

namespace retdec {
namespace internal {

///
/// Private implementation of Analysis.
///
class AnalysisImpl: public ResourceImpl {
public:
	AnalysisImpl(
		const std::string &id,
		const std::shared_ptr<Connection> &conn,
		const std::string &serviceName,
		const std::string &resourcesName
	);
	virtual ~AnalysisImpl() override;

	void getAndStoreOutputAsFile();

	/// URL to obtain the output of the analysis.
	const Connection::Url outputUrl;

	/// Output as a file.
	std::shared_ptr<File> outputAsFile;
};

///
/// Constructs a private implementation.
///
/// @param[in] id Identifier of the resource.
/// @param[in] conn Connection to be used to communicate with the API.
/// @param[in] serviceName Name of the service.
/// @param[in] resourcesName Name of the resources (plural).
///
AnalysisImpl::AnalysisImpl(
		const std::string &id,
		const std::shared_ptr<Connection> &conn,
		const std::string &serviceName,
		const std::string &resourcesName
	): ResourceImpl(id, conn, serviceName, resourcesName),
	outputUrl(baseUrl + "/output")
	{}

///
/// Destructs the private implementation.
///
AnalysisImpl::~AnalysisImpl() = default;

///
/// Gets and stores the results as an output file.
///
void AnalysisImpl::getAndStoreOutputAsFile() {
	auto response = conn->sendGetRequest(outputUrl);
	outputAsFile = response->bodyAsFile();
}

} // namespace internal

///
/// Constructs an analysis.
///
Analysis::Analysis(const std::string &id,
		// The qualification in ::Connection below has to be be used due to
		// doxygen limitations.
		const std::shared_ptr<::Connection> &conn):
	Resource(std::make_unique<AnalysisImpl>(
		id,
		conn,
		"fileinfo",
		"analyses"
	)) {}

///
/// Destructs the analysis.
///
Analysis::~Analysis() = default;

///
/// Waits until the analysis is finished.
///
/// @param[in] onError Should AnalysisError be thrown when the
///                    analysis fails?
///
/// May access the API.
///
void Analysis::waitUntilFinished(OnError onError) {
	// Currently, there is no other choice but polling.
	while (!impl()->finished) {
		impl()->updateStatus();

		// Wait a bit before the next try to update the status.
		sleep(500);
	}

	if (impl()->failed && onError == OnError::Throw) {
		throw AnalysisError(impl()->error);
	}
}

///
/// Returns the results of the analysis as a file.
///
/// This function should be called only after the analysis has finished,
/// i.e. hasFinished() returns @c true.
///
/// May access the API.
///
std::shared_ptr<File> Analysis::getOutputAsFile() {
	if (!impl()->outputAsFile) {
		impl()->getAndStoreOutputAsFile();
	}
	return impl()->outputAsFile;
}

///
/// Returns the results of the analysis.
///
/// This function should be called only after the analysis has finished,
/// i.e. hasFinished() returns @c true.
///
/// May access the API.
///
std::string Analysis::getOutput() {
	return getOutputAsFile()->getContent();
}

///
/// Returns a properly cast private implementation.
///
AnalysisImpl *Analysis::impl() noexcept {
	return static_cast<AnalysisImpl *>(pimpl.get());
}

///
/// Constant overload of impl().
///
const AnalysisImpl *Analysis::impl() const noexcept {
	return static_cast<const AnalysisImpl *>(pimpl.get());
}

} // namespace retdec
