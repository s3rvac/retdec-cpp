///
/// @file      retdec/settings.h
/// @copyright (c) 2015-2016 by Petr Zemek (s3rvac@gmail.com) and contributors
/// @license   MIT, see the @c LICENSE file for more details
/// @brief     Library settings.
///

#ifndef RETDEC_SETTINGS_H
#define RETDEC_SETTINGS_H

#include <memory>
#include <string>

namespace retdec {

///
/// Library settings.
///
class Settings {
public:
	/// @name Construction, Assignment, and Destruction
	/// @{
	Settings();
	Settings(const Settings &other);
	Settings(Settings &&other);
	Settings &operator=(const Settings &other);
	Settings &operator=(Settings &&other);
	~Settings();
	/// @}

	/// @name API Key
	/// @{
	Settings &apiKey(const std::string &apiKey);
	Settings withApiKey(const std::string &apiKey) const;
	std::string apiKey() const;
	/// @}

	/// @name API URL
	/// @{
	Settings &apiUrl(const std::string &apiUrl);
	Settings withApiUrl(const std::string &apiUrl) const;
	std::string apiUrl() const;
	/// @}

	/// @name User Agent
	/// @{
	Settings &userAgent(const std::string &userAgent);
	Settings withUserAgent(const std::string &userAgent) const;
	std::string userAgent() const;
	/// @}

public:
	/// @name Default Values
	/// @{
	static const std::string DefaultApiUrl;
	static const std::string DefaultApiKey;
	static const std::string DefaultUserAgent;
	/// @}

private:
	/// URL to the API.
	std::string apiUrl_;

	/// API key.
	std::string apiKey_;

	/// User agent.
	std::string userAgent_;
};

} // namespace retdec

#endif
