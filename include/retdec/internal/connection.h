///
/// @file      retdec/internal/connection.h
/// @copyright (c) 2015-2016 by Petr Zemek (s3rvac@gmail.com) and contributors
/// @license   MIT, see the @c LICENSE file for more details
/// @brief     Base class of connections to the API.
///

#ifndef RETDEC_INTERNAL_CONNECTION_H
#define RETDEC_INTERNAL_CONNECTION_H

#include <map>
#include <memory>
#include <string>
#include <utility>
#include <vector>

namespace Json {

class Value;

} // namespace Json

namespace retdec {

class File;

namespace internal {

///
/// Base class of connections to the API.
///
class Connection {
public:
	///
	/// Base class of responses returned from requests.
	///
	class Response {
	public:
		virtual ~Response() = 0;

		virtual int statusCode() const = 0;
		virtual std::string statusMessage() const = 0;
		virtual std::string body() const = 0;
		virtual Json::Value bodyAsJson() const = 0;
		virtual std::unique_ptr<File> bodyAsFile() const = 0;

	protected:
		Response();
	};

	/// URL.
	using Url = std::string;

	/// Name of an argument.
	using ArgumentName = std::string;

	/// Value of an argument.
	using ArgumentValue = std::string;

	/// Argument passed to a request.
	using RequestArgument = std::pair<ArgumentName, ArgumentValue>;

	/// Arguments passed to a request.
	using RequestArguments = std::vector<RequestArgument>;

	/// Name of a file argument.
	using FileArgumentName = std::string;

	/// Files passed to a request.
	using RequestFiles = std::map<FileArgumentName, std::shared_ptr<File>>;

public:
	virtual ~Connection() = 0;

	virtual Url getApiUrl() const = 0;

	virtual std::unique_ptr<Response> sendGetRequest(const Url &url) = 0;
	virtual std::unique_ptr<Response> sendGetRequest(const Url &url,
		const RequestArguments &args) = 0;
	virtual std::unique_ptr<Response> sendPostRequest(const Url &url,
		const RequestArguments &args, const RequestFiles &files) = 0;

protected:
	Connection();
};

} // namespace internal
} // namespace retdec

#endif
