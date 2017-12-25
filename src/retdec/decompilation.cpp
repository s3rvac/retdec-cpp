///
/// @file      retdec/decompilation.cpp
/// @copyright (c) 2015-2017 by Petr Zemek (s3rvac@gmail.com) and contributors
/// @license   MIT, see the @c LICENSE file for more details
/// @brief     Implementation of the decompilation.
///

#include <utility>

#include <json/json.h>

#include "retdec/decompilation.h"
#include "retdec/exceptions.h"
#include "retdec/file.h"
#include "retdec/internal/connections/real_connection.h"
#include "retdec/internal/resource_impl.h"
#include "retdec/internal/utilities/connection.h"
#include "retdec/internal/utilities/os.h"

using namespace retdec::internal;

namespace retdec {

namespace {

/// Callback doing nothing.
const Decompilation::Callback CallbackDoingNothing = [](const Decompilation &) {};

} // anonymous namespace

namespace internal {

///
/// Private implementation of Decompilation.
///
class DecompilationImpl: public ResourceImpl {
public:
	DecompilationImpl(
		const std::string &id,
		const std::shared_ptr<Connection> &conn,
		const std::string &serviceName,
		const std::string &resourcesName
	);
	virtual ~DecompilationImpl() override;

	/// @name Status Update
	/// @{
	virtual void updateResourceSpecificStatus(const Json::Value &jsonBody) override;
	/// @}

	void getAndStoreOutputHllFile();

	/// URL to obtain the outputs of the resource.
	const Connection::Url outputsUrl;

	/// Completion (in percentages, 0-100).
	int completion = 0;

	/// Output HLL file.
	std::shared_ptr<File> outputHllFile;
};

///
/// Constructs a private implementation.
///
/// @param[in] id Identifier of the resource.
/// @param[in] conn Connection to be used to communicate with the API.
/// @param[in] serviceName Name of the service.
/// @param[in] resourcesName Name of the resources (plural).
///
DecompilationImpl::DecompilationImpl(
		const std::string &id,
		const std::shared_ptr<Connection> &conn,
		const std::string &serviceName,
		const std::string &resourcesName
	): ResourceImpl(id, conn, serviceName, resourcesName),
	outputsUrl(baseUrl + "/outputs")
	{}

// Override.
DecompilationImpl::~DecompilationImpl() = default;

// Override.
void DecompilationImpl::updateResourceSpecificStatus(const Json::Value &jsonBody) {
	completion = jsonBody.get("completion", false).asInt();
}

///
/// Gets and stores the output HLL file.
///
void DecompilationImpl::getAndStoreOutputHllFile() {
	auto response = conn->sendGetRequest(outputsUrl + "/hll");
	outputHllFile = response->bodyAsFile();
}

} // namespace internal

///
/// Constructs a decompilation.
///
Decompilation::Decompilation(const std::string &id,
		const std::shared_ptr<Connection> &conn):
	Resource(std::make_unique<DecompilationImpl>(
		id,
		conn,
		"decompiler",
		"decompilations"
	)) {}

// Override.
Decompilation::~Decompilation() = default;

///
/// Returns the completion status (in percentages, 0-100).
///
/// May access the API.
///
int Decompilation::getCompletion() {
	impl()->updateStatusIfNeeded();
	return impl()->completion;
}

///
/// Returns the completion status (in percentages, 0-100).
///
/// Does not access the API.
///
int Decompilation::getCompletion() const noexcept {
	return impl()->completion;
}

///
/// Waits until the decompilation is finished.
///
/// @param[in] onError Should DecompilationError be thrown when the
///                    decompilation fails?
///
/// May access the API.
///
void Decompilation::waitUntilFinished(OnError onError) {
	waitUntilFinished(CallbackDoingNothing, onError);
}

///
/// Waits and reports changes until the decompilation is finished.
///
/// @param[in] callback Function to be called when the decompilation status
///                     changes.
/// @param[in] onError Should DecompilationError be thrown when the
///                    decompilation fails?
///
/// May access the API.
///
void Decompilation::waitUntilFinished(const Callback &callback,
		OnError onError) {
	// Currently, there is no other choice but polling.
	while (!impl()->finished) {
		auto lastCompletion = impl()->completion;
		impl()->updateStatus();
		if (impl()->completion != lastCompletion) {
			callback(*this);
		}
		// Wait a bit before the next try to update the status.
		sleep(500);
	}

	if (impl()->failed && onError == OnError::Throw) {
		throw DecompilationError(impl()->error);
	}
}

///
/// Returns the output HLL file (C, Python').
///
/// This function should be called only after the decompilation has finished,
/// i.e. hasFinished() returns @c true.
///
/// May access the API.
///
std::shared_ptr<File> Decompilation::getOutputHllFile() {
	if (!impl()->outputHllFile) {
		impl()->getAndStoreOutputHllFile();
	}
	return impl()->outputHllFile;
}

///
/// Returns the content of the output HLL file (C, Python').
///
/// This function should be called only after the decompilation has finished,
/// i.e. hasFinished() returns @c true.
///
/// May access the API.
///
std::string Decompilation::getOutputHll() {
	return getOutputHllFile()->getContent();
}

///
/// Returns a properly cast private implementation.
///
DecompilationImpl *Decompilation::impl() noexcept {
	return static_cast<DecompilationImpl *>(pimpl.get());
}

///
/// Constant overload of impl().
///
const DecompilationImpl *Decompilation::impl() const noexcept {
	return static_cast<const DecompilationImpl *>(pimpl.get());
}

} // namespace retdec
