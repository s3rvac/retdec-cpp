///
/// @file      retdec/decompilation.cpp
/// @copyright (c) 2015-2016 by Petr Zemek (s3rvac@gmail.com) and contributors
/// @license   MIT, see the @c LICENSE file for more details
/// @brief     Implementation of the decompilation.
///

#include <memory>
#include <utility>

#include <json/json.h>

#include "retdec/decompilation.h"
#include "retdec/exceptions.h"
#include "retdec/file.h"
#include "retdec/internal/connections/real_connection.h"
#include "retdec/internal/utilities/connection.h"
#include "retdec/internal/utilities/os.h"

using namespace retdec::internal;

namespace retdec {

namespace {

/// Callback doing nothing.
const Decompilation::Callback CallbackDoingNothing = [] (const Decompilation &) {};

} // anonymous namespace

///
/// Private implementation of Decompilation.
///
struct Decompilation::Impl {
	Impl(const std::string &id, const std::shared_ptr<Connection> &conn):
		id(id), conn(std::make_shared<ResponseVerifyingConnection>(conn)),
		baseUrl(conn->getApiUrl() + "/decompiler/decompilations/" + id),
		statusUrl(baseUrl + "/status"),
		outputsUrl(baseUrl + "/outputs")
		{}

	bool shouldUpdateStatus();
	void updateStatus();
	void updateStatusIfNeeded();
	void getAndStoreOutputHllFile();

	/// Identifier.
	const std::string id;

	/// Connection to the API.
	const std::shared_ptr<ResponseVerifyingConnection> conn;

	/// Base URL of the decompilation.
	const Connection::Url baseUrl;

	/// URL to obtain the status of the decompilation.
	const Connection::Url statusUrl;

	/// URL to obtain the outputs of the decompilation.
	const Connection::Url outputsUrl;

	/// Has the decompilation finished?
	bool finished = false;

	/// Has the decompilation succeeded?
	bool succeeded = false;

	/// Has the decompilation failed?
	bool failed = false;

	/// Completion (in percentages, 0-100).
	int completion = 0;

	/// Error message.
	std::string error;

	/// Output HLL file.
	std::shared_ptr<File> outputHllFile;
};

///
/// Should the status be updated?
///
bool Decompilation::Impl::shouldUpdateStatus() {
	return !finished;
}

///
/// Updates the status of the decompilation.
///
void Decompilation::Impl::updateStatus() {
	auto response = conn->sendGetRequest(statusUrl);
	auto jsonBody = response->bodyAsJson();
	finished = jsonBody.get("finished", false).asBool();
	succeeded = jsonBody.get("succeeded", false).asBool();
	failed = jsonBody.get("failed", false).asBool();
	completion = jsonBody.get("completion", false).asInt();
	error = jsonBody.get("error", "").asString();
}

///
/// Updates the status (if needed).
///
void Decompilation::Impl::updateStatusIfNeeded() {
	if (shouldUpdateStatus()) {
		updateStatus();
	}
}

///
/// Gets and stores the output HLL file.
///
void Decompilation::Impl::getAndStoreOutputHllFile() {
	auto response = conn->sendGetRequest(outputsUrl + "/hll");
	outputHllFile = response->bodyAsFile();
}

///
/// Constructs a decompilation.
///
Decompilation::Decompilation(const std::string &id,
		// The qualification in ::Connection below has to be be used due to
		// doxygen limitations.
		const std::shared_ptr<::Connection> &conn):
	impl(std::make_unique<Impl>(id, conn)) {}

///
/// Destructs the decompilation.
///
Decompilation::~Decompilation() = default;

///
/// Returns the ID of the decompilation.
///
/// Does not access the API.
///
std::string Decompilation::getId() const {
	return impl->id;
}

///
/// Has the decompilation finished?
///
/// May access the API.
///
bool Decompilation::hasFinished() {
	impl->updateStatusIfNeeded();
	return impl->finished;
}

///
/// Has the decompilation finished?
///
/// Does not access the API.
///
bool Decompilation::hasFinished() const noexcept {
	return impl->finished;
}

///
/// Has the decompilation succeeded?
///
/// The output from this function is meaningful only if hasFinished() returns
/// @c true.
///
/// May access the API.
///
bool Decompilation::hasSucceeded() {
	impl->updateStatusIfNeeded();
	return impl->succeeded;
}

///
/// Has the decompilation succeeded?
///
/// The output from this function is meaningful only if hasFinished() returns
/// @c true.
///
/// Does not access the API.
///
bool Decompilation::hasSucceeded() const noexcept {
	return impl->succeeded;
}

///
/// Has the decompilation failed?
///
/// The output from this function is meaningful only if hasFinished() returns
/// @c true.
///
/// May access the API.
///
bool Decompilation::hasFailed() {
	impl->updateStatusIfNeeded();
	return impl->failed;
}

///
/// Has the decompilation failed?
///
/// The output from this function is meaningful only if hasFinished() returns
/// @c true.
///
/// Does not access the API.
///
bool Decompilation::hasFailed() const noexcept {
	return impl->failed;
}

///
/// Returns the completion status (in percentages, 0-100).
///
/// May access the API.
///
int Decompilation::getCompletion() {
	impl->updateStatusIfNeeded();
	return impl->completion;
}

///
/// Returns the completion status (in percentages, 0-100).
///
/// Does not access the API.
///
int Decompilation::getCompletion() const noexcept {
	return impl->completion;
}

///
/// Returns the error message (if any).
///
/// The output from this function is meaningful only if hasFinished() returns
/// @c true and hasFailed() returns @c true.
///
/// May access the API.
///
std::string Decompilation::getError() {
	impl->updateStatusIfNeeded();
	return impl->error;
}

///
/// Returns the error message (if any).
///
/// The output from this function is meaningful only if hasFinished() returns
/// @c true and hasFailed() returns @c true.
///
/// Does not access the API.
///
std::string Decompilation::getError() const {
	return impl->error;
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
	while (!impl->finished) {
		auto lastCompletion = impl->completion;
		impl->updateStatus();
		if (impl->completion != lastCompletion) {
			callback(*this);
		}
		// Wait a bit before the next try to update the status.
		sleep(500);
	}

	if (impl->failed && onError == OnError::Throw) {
		throw DecompilationError(impl->error);
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
	if (!impl->outputHllFile) {
		impl->getAndStoreOutputHllFile();
	}
	return impl->outputHllFile;
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

} // namespace retdec
