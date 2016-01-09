///
/// @file      retdec/settings_tests.cpp
/// @copyright (c) 2015 by Petr Zemek (s3rvac@gmail.com) and contributors
/// @license   MIT, see the @c LICENSE file for more details
/// @brief     Tests for the settings.
///

#include <gtest/gtest.h>

#include "retdec/internal/utilities/os.h"
#include "retdec/settings.h"

using namespace testing;
using namespace retdec::internal;

namespace retdec {
namespace tests {

///
/// Tests for Settings.
///
class SettingsTests: public Test {};

TEST_F(SettingsTests,
DefaultApiUrlHasCorrectValue) {
	EXPECT_EQ("https://retdec.com/service/api", Settings::DefaultApiUrl);
}

TEST_F(SettingsTests,
DefaultApiKeyHasCorrectValue) {
	EXPECT_EQ("", Settings::DefaultApiKey);
}

TEST_F(SettingsTests,
DefaultUserAgentHasCorrectValue) {
	EXPECT_EQ("retdec-cpp/" + operatingSystemName(), Settings::DefaultUserAgent);
}

TEST_F(SettingsTests,
HasDefaultValuesWhenCreatedWithDefaultConstructor) {
	Settings settings;

	EXPECT_EQ(Settings::DefaultApiKey, settings.apiKey());
	EXPECT_EQ(Settings::DefaultApiUrl, settings.apiUrl());
	EXPECT_EQ(Settings::DefaultUserAgent, settings.userAgent());
}

TEST_F(SettingsTests,
ApiKeyChangesSettingsInPlace) {
	Settings settings;

	settings.apiKey("my-api-key");

	EXPECT_EQ("my-api-key", settings.apiKey());
}

TEST_F(SettingsTests,
WithApiKeyReturnsSettingsWithNewApiKey) {
	Settings settings;

	auto newSettings = settings.withApiKey("my-api-key");

	EXPECT_EQ("my-api-key", newSettings.apiKey());
}

TEST_F(SettingsTests,
ApiUrlChangesSettingsInPlace) {
	Settings settings;

	settings.apiUrl("http://127.0.0.1/api");

	EXPECT_EQ("http://127.0.0.1/api", settings.apiUrl());
}

TEST_F(SettingsTests,
WithApiUrlReturnsSettingsWithNewApiUrl) {
	Settings settings;

	auto newSettings = settings.withApiUrl("http://127.0.0.1/api");

	EXPECT_EQ("http://127.0.0.1/api", newSettings.apiUrl());
}

TEST_F(SettingsTests,
UserAgentChangesSettingsInPlace) {
	Settings settings;

	settings.userAgent("my user agent");

	EXPECT_EQ("my user agent", settings.userAgent());
}

TEST_F(SettingsTests,
WithUserAgentReturnsSettingsWithNewUserAgent) {
	Settings settings;

	auto newSettings = settings.withUserAgent("my user agent");

	EXPECT_EQ("my user agent", newSettings.userAgent());
}

TEST_F(SettingsTests,
NotModifyingSettersAllowChaining) {
	auto settings = Settings()
		.withApiKey("my-api-key")
		.withApiUrl("http://127.0.0.1/api");

	EXPECT_EQ("my-api-key", settings.apiKey());
	EXPECT_EQ("http://127.0.0.1/api", settings.apiUrl());
}

TEST_F(SettingsTests,
InPlaceSettersAllowChainingForLValue) {
	Settings settings;

	settings.apiKey("my-api-key")
		.apiUrl("http://127.0.0.1/api");

	EXPECT_EQ("my-api-key", settings.apiKey());
	EXPECT_EQ("http://127.0.0.1/api", settings.apiUrl());
}

TEST_F(SettingsTests,
InPlaceSettersAllowChainingForRValue) {
	auto settings = Settings()
		.apiKey("my-api-key")
		.apiUrl("http://127.0.0.1/api");

	EXPECT_EQ("my-api-key", settings.apiKey());
	EXPECT_EQ("http://127.0.0.1/api", settings.apiUrl());
}

} // namespace tests
} // namespace retdec
