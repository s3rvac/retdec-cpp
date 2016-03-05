///
/// @file      retdec/decompiler.cpp
/// @copyright (c) 2015-2016 by Petr Zemek (s3rvac@gmail.com) and contributors
/// @license   MIT, see the @c LICENSE file for more details
/// @brief     Implementation of the decompiler.
///

#include <memory>

#include <json/json.h>

#include "retdec/decompilation.h"
#include "retdec/decompilation_arguments.h"
#include "retdec/decompiler.h"
#include "retdec/internal/connection_managers/real_connection_manager.h"
#include "retdec/internal/connections/real_connection.h"
#include "retdec/internal/utilities/connection.h"
#include "retdec/settings.h"

using namespace retdec::internal;

namespace retdec {

namespace {

///
/// Constructs Connection::RequestArguments from the given decompilation
/// arguments.
///
Connection::RequestArguments createRequestArguments(
		const DecompilationArguments &args) {
	Connection::RequestArguments requestArgs;
	for (auto i = args.argumentsBegin(), e = args.argumentsEnd(); i != e; ++i) {
		requestArgs.emplace_back(i->first, i->second);
	}
	return requestArgs;
}

///
/// Constructs Connection::RequestFiles from the given decompilation arguments.
///
Connection::RequestFiles createRequestFiles(
		const DecompilationArguments &args) {
	Connection::RequestFiles requestFiles;
	for (auto i = args.filesBegin(), e = args.filesEnd(); i != e; ++i) {
		requestFiles.emplace(i->first, i->second);
	}
	return requestFiles;
}

} // anonymous namespace

///
/// Private implementation of Decompiler.
///
struct Decompiler::Impl {
	Impl(const Settings &settings,
		const std::shared_ptr<ConnectionManager> &connectionManager):
			settings(settings), connectionManager(connectionManager),
			baseUrl(settings.apiUrl() + "/decompiler") {}

	/// Settings.
	const Settings settings;

	/// Connection manager.
	const std::shared_ptr<ConnectionManager> connectionManager;

	/// Base URL.
	const std::string baseUrl;
};

///
/// Constructs a decompiler with the given settings.
///
Decompiler::Decompiler(const Settings &settings):
	impl(std::make_unique<Impl>(settings, std::make_shared<RealConnectionManager>())) {}

///
/// Constructs a decompiler with the given settings and connection manager.
///
Decompiler::Decompiler(const Settings &settings,
		// The qualification in ::ConnectionManager below has to be be used due
		// to doxygen limitations.
		const std::shared_ptr<::ConnectionManager> &connectionManager):
	impl(std::make_unique<Impl>(settings, connectionManager)) {}

///
/// Destructs the decompiler.
///
Decompiler::~Decompiler() = default;

///
/// Runs a new decompilation with the given arguments.
///
std::unique_ptr<Decompilation> Decompiler::runDecompilation(
		const DecompilationArguments &args) {
	auto conn = impl->connectionManager->newConnection(impl->settings);
	auto response = conn->sendPostRequest(
		impl->baseUrl + "/decompilations",
		createRequestArguments(args),
		createRequestFiles(args)
	);
	verifyRequestSucceeded(*response);
	auto jsonBody = response->bodyAsJson();
	auto id = jsonBody.get("id", "?").asString();
	return std::make_unique<Decompilation>(id, conn);
}

} // namespace retdec
