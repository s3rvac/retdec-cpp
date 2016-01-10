///
/// @file      retdec/internal/connections/real_connection_tests.cpp
/// @copyright (c) 2015-2016 by Petr Zemek (s3rvac@gmail.com) and contributors
/// @license   MIT, see the @c LICENSE file for more details
/// @brief     Tests for the real connection to the API.
///

// Currently, the tests for RealConnection can run only on Linux.
#include "retdec/internal/utilities/os.h"
#ifndef RETDEC_OS_WINDOWS

#include <cstdlib>
#include <signal.h>
#include <sstream>
#include <sys/types.h>
#include <unistd.h>

#include <boost/network/protocol/http/server.hpp>
#include <gtest/gtest.h>

#include "retdec/internal/connections/real_connection.h"
#include "retdec/settings.h"

///
/// Asserts that @a response contains @a text.
///
#define ASSERT_CONTAINS(response, text) \
	ASSERT_TRUE(contains(response.get(), text)) << response->body();

using namespace testing;

namespace retdec {
namespace internal {
namespace tests {

///
/// Tests for RealConnection.
///
class RealConnectionTests: public Test {
public:
	virtual void SetUp() override;
	virtual void TearDown() override;

	struct HttpServerHandler;

	/// Type of the used HTTP server.
	using HttpServer = boost::network::http::server<HttpServerHandler>;

	/// Handler for the HTTP server.
	struct HttpServerHandler {
		void operator()(const HttpServer::request &request,
			HttpServer::response &response);
		void log(const std::string &error);
	};

	void startHttpServer();
	void stopHttpServer();
	bool contains(const Connection::Response *response,
		const std::string &text);

	/// PID of the HTTP server.
	pid_t httpServerPid = -1;

	/// Host on which the HTTP server runs.
	static const std::string HttpServerHost;

	/// Port on which the HTTP server runs.
	static const std::string HttpServerPort;

	/// HTTP URL of the server.
	static const std::string HttpServerUrl;
};

// Static variable definitions.
const std::string RealConnectionTests::HttpServerHost = "127.0.0.1";
const std::string RealConnectionTests::HttpServerPort = "8000";
const std::string RealConnectionTests::HttpServerUrl = "http://" +
	HttpServerHost + ":" + HttpServerPort;

///
/// Handles the given request.
///
void RealConnectionTests::HttpServerHandler::operator()(
		const HttpServer::request &request, HttpServer::response &response) {
	// Put the request data into the response's body. In this way, we can later
	// check that a proper request was sent.
	//
	// Example:
	//
	//     GET /api HTTP/1.1
	//     Authorization: Basic LTo=
	//     Host: 127.0.0.1:8000
	//     Accept: */*
	//     Accept-Encoding: identity;q=1.0, *;q=0
	//
	//     $REQUEST_BODY
	//
	std::ostringstream body;
	body << request.method << " " << request.destination << " HTTP/" <<
		static_cast<int>(request.http_version_major) << "." <<
		static_cast<int>(request.http_version_minor) << "\r\n";
	for (auto &header : request.headers) {
		body << header.name << ": " << header.value << "\r\n";
	}
	body << "\r\n";
	body << request.body;
	response = HttpServer::response::stock_reply(
		HttpServer::response::ok, body.str());
}

///
/// Logs the given error.
///
void RealConnectionTests::HttpServerHandler::log(const std::string &error) {
	// Ignore errors as there is not much we can do.
	static_cast<void>(error);
}

// Override.
void RealConnectionTests::SetUp() {
	startHttpServer();
}

// Override.
void RealConnectionTests::TearDown() {
	stopHttpServer();
}

///
/// Checks if @a response contains the given text.
///
bool RealConnectionTests::contains(const Connection::Response *response,
		const std::string &text) {
	return response->body().find(text) != std::string::npos;
}

///
/// Starts the HTTP server (asynchronously).
///
void RealConnectionTests::startHttpServer() {
	// To run the server asynchronously, we run it in a separate process. I was
	// unable to use threads (boost::thread) to run the server since running
	// both the client and server in the same process failed to execute
	// properly (it segfaulted). To this end, we use processes, which work OK.
	// Alas, this solution is not portable so it requires a different
	// implementation for Linux and MS Windows.
	auto pid = fork();
	if (pid == 0) {
		// Child process.
		HttpServerHandler handler;
		HttpServer server(
			HttpServer::options(handler)
				.address(HttpServerHost)
				.port(HttpServerPort)
				.reuse_address(true)
		);
		// Enter an infinite event-processing loop.
		server.run();
		std::exit(0);
	} else {
		// Parent process.
		httpServerPid = pid;

		// Wait to make sure that the server has started.
		sleep(100);
	}
}

///
/// Stops the HTTP server.
///
void RealConnectionTests::stopHttpServer() {
	kill(httpServerPid, SIGTERM);
	waitpid(httpServerPid, nullptr, 0);
}

TEST_F(RealConnectionTests,
ApiUrlReturnsCorrectUrl) {
	RealConnection conn(Settings().withApiUrl("http://127.0.0.1:5000/api"));

	ASSERT_EQ("http://127.0.0.1:5000/api", conn.getApiUrl());
}

TEST_F(RealConnectionTests,
GetWithoutArgumentsSendsRequestWithCorrectMethodAndDestinationAndHttpVersion) {
	const auto ApiUrl = HttpServerUrl + "/api";
	RealConnection conn(Settings().withApiUrl(ApiUrl));

	auto response = conn.sendGetRequest(ApiUrl + "/test");

	ASSERT_CONTAINS(response, "GET /api/test HTTP/1.1");
}

TEST_F(RealConnectionTests,
GetSendsRequestWithUserAgentHeader) {
	const auto ApiUrl = HttpServerUrl + "/api";
	RealConnection conn(
		Settings()
			.withApiUrl(ApiUrl)
			.withUserAgent("my user agent")
	);

	auto response = conn.sendGetRequest(ApiUrl);

	ASSERT_CONTAINS(response, "User-Agent: my user agent");
}

} // namespace tests
} // namespace internal
} // namespace retdec

#endif
