///
/// @file      retdec/settings.cpp
/// @copyright (c) 2015-2016 by Petr Zemek (s3rvac@gmail.com) and contributors
/// @license   MIT, see the @c LICENSE file for more details
/// @brief     Implementation of the library settings.
///

#include <utility>

#include "retdec/internal/utilities/os.h"
#include "retdec/settings.h"

using namespace retdec::internal;

namespace retdec {

///
/// Constructs a default settings.
///
Settings::Settings():
	apiUrl_(DefaultApiUrl), apiKey_(DefaultApiKey),
	userAgent_(DefaultUserAgent) {}

///
/// Copy-constructs settings from the given settings.
///
Settings::Settings(const Settings &) = default;

///
/// Move-constructs settings from the given settings.
///
Settings::Settings(Settings &&) = default;

///
/// Copy-assigns the given settings.
///
Settings &Settings::operator=(const Settings &) = default;

///
/// Move-assigns the given settings.
///
Settings &Settings::operator=(Settings &&) = default;

///
/// Destructs the settings.
///
Settings::~Settings() = default;

///
/// Sets a new API key.
///
/// @returns Reference to the modified settings (i.e. @c *this).
///
Settings &Settings::apiKey(const std::string &apiKey) {
	apiKey_ = apiKey;
	return *this;
}

///
/// Returns a copy of the settings with a new API key.
///
Settings Settings::withApiKey(const std::string &apiKey) const {
	auto copy = *this;
	copy.apiKey(apiKey);
	return copy;
}

///
/// Returns the API key.
///
std::string Settings::apiKey() const {
	return apiKey_;
}

///
/// Sets a new URL to the API.
///
/// @returns Reference to the modified settings (i.e. @c *this).
///
Settings &Settings::apiUrl(const std::string &apiUrl) {
	apiUrl_ = apiUrl;
	return *this;
}

///
/// Returns a copy of the settings with a new URL to the API.
///
Settings Settings::withApiUrl(const std::string &apiUrl) const {
	auto copy = *this;
	copy.apiUrl(apiUrl);
	return copy;
}

///
/// Returns the URL to the API.
///
std::string Settings::apiUrl() const {
	return apiUrl_;
}

///
/// Sets a new user agent.
///
/// @returns Reference to the modified settings (i.e. @c *this).
///
Settings &Settings::userAgent(const std::string &userAgent) {
	userAgent_ = userAgent;
	return *this;
}

///
/// Returns a copy of the settings with a new user agent.
///
Settings Settings::withUserAgent(const std::string &userAgent) const {
	auto copy = *this;
	copy.userAgent(userAgent);
	return copy;
}

///
/// Returns the user agent.
///
std::string Settings::userAgent() const {
	return userAgent_;
}

/// Default URL to the API.
const std::string Settings::DefaultApiUrl = "https://retdec.com/service/api";

/// Default API key.
const std::string Settings::DefaultApiKey = "";

/// Default user agent.
const std::string Settings::DefaultUserAgent = "retdec-cpp/" +
	operatingSystemName();

} // namespace retdec
