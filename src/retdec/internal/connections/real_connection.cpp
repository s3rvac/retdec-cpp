///
/// @file      retdec/internal/connections/real_connection.cpp
/// @copyright (c) 2015 by Petr Zemek (s3rvac@gmail.com) and contributors
/// @license   MIT, see the @c LICENSE file for more details
/// @brief     Implementation of the connection to the API.
///

#include <boost/network/protocol/http/client.hpp>
#include <boost/network/utils/base64/encode.hpp>
#include <boost/system/system_error.hpp>
#include <json/json.h>

#include "retdec/internal/connections/real_connection.h"
#include "retdec/internal/files/string_file.h"
#include "retdec/internal/utilities/json.h"
#include "retdec/internal/utilities/smart_ptr.h"
#include "retdec/internal/utilities/string.h"
#include "retdec/settings.h"

namespace retdec {
namespace internal {

/// HTTP client to be used.
// The default client does not use keep-alive connections.
using HttpClient = boost::network::http::basic_client<
	boost::network::http::tags::http_keepalive_8bit_tcp_resolve, 1, 1
>;

/// Encodes the given string by using the Base64 encoding.
///
std::string base64Encode(const std::string &str) {
	return boost::network::utils::base64::encode<std::string::value_type>(str);
}

///
/// Real response.
///
class RealResponse: public Connection::Response {
public:
	RealResponse(const HttpClient::response &response);
	virtual ~RealResponse();

	virtual int statusCode() const override;
	virtual std::string statusMessage() const override;
	virtual std::string body() const override;
	virtual Json::Value bodyAsJson() const override;
	virtual std::unique_ptr<File> bodyAsFile() const override;

private:
	std::string attachedFileName() const;

private:
	/// Underlying response.
	HttpClient::response response;
};

///
/// Constructs a response.
///
RealResponse::RealResponse(const HttpClient::response &response):
	response(response) {}

///
/// Destructs the response.
///
RealResponse::~RealResponse() = default;

// Override.
int RealResponse::statusCode() const {
	return response.status();
}

// Override.
std::string RealResponse::statusMessage() const {
	// cpp-netlib converts all letters in the status message to UPPER CASE, so
	// convert the message to Mixed Case.
	return capitalizeWords(response.status_message());
}

// Override.
std::string RealResponse::body() const {
	return response.body();
}

// Override.
Json::Value RealResponse::bodyAsJson() const {
	return toJson(response.body());
}

// Override.
std::unique_ptr<File> RealResponse::bodyAsFile() const {
	return make_unique<StringFile>(response.body(), attachedFileName());
}

///
/// Returns the file name from the response.
///
std::string RealResponse::attachedFileName() const {
	// TODO Implement this in a more robust way.
	// Content-Disposition: attachment; filename=$FILE_NAME
	const auto &headers = boost::network::http::headers(response);
	const auto &contentDisposition = headers["Content-Disposition"].front();
	return contentDisposition.second.substr(21);
}

///
/// Private implementation of RealConnection.
///
struct RealConnection::Impl {
	Impl(const Settings &settings):
		settings(settings) {}

	std::string createQuery(const RequestArguments &args);
	void addAuthToRequest(HttpClient::request &request);
	void addUserAgentToRequest(HttpClient::request &request);
	std::string addFilesToRequest(const RequestFiles &files,
		HttpClient::request &request);
	HttpClient::request createRequest(const Url &url,
		const RequestArguments &argss);

	/// Settings.
	const Settings settings;

	/// HTTP client.
	HttpClient client;
};

///
/// Creates and returns the query part of an URL (<tt>?key1=value1...</tt>).
///
std::string RealConnection::Impl::createQuery(const Connection::RequestArguments &args) {
	std::string query;
	for (auto &arg : args) {
		query += (query.empty() ? "?" : "&") + arg.first + "=" + arg.second;
	}
	return query;
}

///
/// Adds authorization to the given request.
///
void RealConnection::Impl::addAuthToRequest(HttpClient::request &request) {
	// Basic HTTP authorization is used, where the username is the API key, and
	// the password is empty. According to RFC 2617, the username and password
	// have to be separated by a colon and base64-encoded. See RFC 2617 (HTTP
	// Authentication: Basic and Digest Access Authentication) for more
	// details.
	auto credentials = settings.apiKey() + ":";
	auto encodedCredentials = base64Encode(credentials);
	request << boost::network::header("Authorization", "Basic " + encodedCredentials);
}

///
/// Adds a user-agent string to the given request.
///
void RealConnection::Impl::addUserAgentToRequest(HttpClient::request &request) {
	request << boost::network::header("User-Agent", settings.userAgent());
}

///
/// Adds the given files to the given request.
///
/// @returns Body of the request to be used when sending a POST request.
///
std::string RealConnection::Impl::addFilesToRequest(const RequestFiles &files,
		HttpClient::request &request) {
	// TODO Ensure that the given boundary does not appear in the files.
	const std::string boundary("6eaab101ea8e44848f8d033f5f11088a");
	request << boost::network::header("Content-Type",
		"multipart/form-data; boundary=" + boundary);

	std::string body;
	if (!files.empty()) {
		bool first = true;
		for (auto &file : files) {
			body +=	first ? "" : "\r\n";
			body +=	"--" + boundary + "\r\n" +
				"Content-Disposition: form-data; name=\"" + file.first +
					"\"; filename=\"" + file.second->getName() + "\"\r\n" +
				"\r\n" +
				file.second->getContent();
			first = false;
		}
		body += "\r\n--" + boundary + "--\r\n";
	}
	return body;
}

///
/// Creates a request from the given data.
///
HttpClient::request RealConnection::Impl::createRequest(const Url &url,
		const RequestArguments &args) {
	HttpClient::request request(url + createQuery(args));
	addAuthToRequest(request);
	addUserAgentToRequest(request);
	return request;
}

///
/// Constructs a connection.
///
RealConnection::RealConnection(const Settings &settings):
	impl(make_unique<Impl>(settings)) {}

// Override.
RealConnection::~RealConnection() = default;

// Override.
Connection::Url RealConnection::getApiUrl() const {
	return impl->settings.apiUrl();
}

// Override.
std::unique_ptr<Connection::Response> RealConnection::sendGetRequest(
		const Url &url) {
	return sendGetRequest(url, RequestArguments());
}

// Override.
std::unique_ptr<Connection::Response> RealConnection::sendGetRequest(
		const Url &url, const RequestArguments &args) {
	auto request = impl->createRequest(url, args);
	try {
		auto response = impl->client.get(request);
		return make_unique<RealResponse>(response);
	} catch (const boost::system::system_error &ex) {
		throw ConnectionError(ex.what());
	}
}

// Override.
std::unique_ptr<Connection::Response> RealConnection::sendPostRequest(
		const Url &url, const RequestArguments &args, const RequestFiles &files) {
	// TODO Pass arguments in the body. Example:
	//
	// --fc4a7d4771a04bdb89d94ab0ec2209f9
	// Content-Disposition: form-data; name="mode"
	//
	// c
	// --fc4a7d4771a04bdb89d94ab0ec2209f9
	auto request = impl->createRequest(url, args);
	auto body = impl->addFilesToRequest(files, request);
	try {
		auto response = impl->client.post(request, body);
		return make_unique<RealResponse>(response);
	} catch (const boost::system::system_error &ex) {
		throw ConnectionError(ex.what());
	}
}

} // namespace internal
} // namespace retdec
