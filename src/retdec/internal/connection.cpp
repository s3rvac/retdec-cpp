///
/// @file      retdec/internal/connection.cpp
/// @copyright (c) 2015 by Petr Zemek (s3rvac@gmail.com) and contributors
/// @license   MIT, see the @c LICENSE file for more details
/// @brief     Implementation of the base class for connections to the API.
///

#include "retdec/internal/connection.h"

namespace retdec {
namespace internal {

///
/// Constructs a response.
///
Connection::Response::Response() = default;

///
/// Destructs the response.
///
Connection::Response::~Response() = default;

/// @fn Connection::Response::statusCode()
///
/// Returns the status code.
///

/// @fn Connection::Response::statusMessage()
///
/// Returns the status message.
///

/// @fn Connection::Response::body()
///
/// Returns the body of the response (raw).
///

/// @fn Connection::Response::bodyAsJson()
///
/// Returns the body of the response as JSON.
///

/// @fn Connection::Response::bodyAsFile()
///
/// Returns the body of the response as a file.
///

///
/// Constructs a connection.
///
Connection::Connection() = default;

///
/// Destructs the connection.
///
Connection::~Connection() = default;

/// @fn Connection::getApiUrl()
///
/// Returns the API URL to which this connection is connected.
///

/// @fn std::unique_ptr<Response> Connection::sendGetRequest(const Url &url)
///
/// Sends a GET request to the API and returns the response.
///
/// @param[in] url URL to which the request is sent.
///

/// @fn std::unique_ptr<Response> Connection::sendGetRequest(const Url &url,
///     const RequestArguments &args)
///
/// Sends a GET request with arguments to the API and returns the response.
///
/// @param[in] url URL to which the request is sent.
/// @param[in] args Arguments passed to the request.
///

/// @fn Connection::sendPostRequest()
///
/// Sends a POST request to the API and returns the response.
///
/// @param[in] url URL to which the request is sent.
/// @param[in] args Arguments passed in the request.
/// @param[in] files Files passed in the request.
///

} // namespace internal
} // namespace retdec
