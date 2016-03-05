///
/// @file      retdec/analysis_tests.cpp
/// @copyright (c) 2015-2016 by Petr Zemek (s3rvac@gmail.com) and contributors
/// @license   MIT, see the @c LICENSE file for more details
/// @brief     Tests for the analysis.
///

#include <memory>

#include <gtest/gtest.h>
#include <json/json.h>

#include "retdec/analysis.h"
#include "retdec/internal/connection_mock.h"
#include "retdec/internal/utilities/json.h"
#include "retdec/settings.h"

using namespace testing;
using namespace retdec::internal;
using namespace retdec::internal::tests;

namespace retdec {
namespace tests {

///
/// Tests for Analysis.
///
class AnalysisTests: public Test {};

TEST_F(AnalysisTests,
IsCreatedSuccessfully) {
	auto conn = std::make_shared<NiceMock<ConnectionMock>>();
	ON_CALL(*conn, getApiUrl())
		.WillByDefault(Return("https://retdec.com/service/api"));

	Analysis analysis("id", conn);
}

TEST_F(AnalysisTests,
GetIdReturnsCorrectValue) {
	auto conn = std::make_shared<NiceMock<ConnectionMock>>();
	ON_CALL(*conn, getApiUrl())
		.WillByDefault(Return("https://retdec.com/service/api"));

	Analysis analysis("123", conn);

	ASSERT_EQ("123", analysis.getId());
}

TEST_F(AnalysisTests,
HasFinishedSendsCorrectRequestWhenNoFinishedInfo) {
	auto refResponse = std::make_unique<NiceMock<ResponseMock>>();
	ON_CALL(*refResponse, statusCode())
		.WillByDefault(Return(200)); // HTTP 200 OK
	ON_CALL(*refResponse, bodyAsJson())
		.WillByDefault(Return(toJson("{\"finished\": false}")));

	auto conn = std::make_shared<NiceMock<ConnectionMock>>();
	ON_CALL(*conn, getApiUrl())
		.WillByDefault(Return("https://retdec.com/service/api"));
	EXPECT_CALL(*conn, sendGetRequestProxy(
			"https://retdec.com/service/api/fileinfo/analyses/123/status"))
		.WillOnce(Return(refResponse.release()));

	Analysis analysis("123", conn);
	analysis.hasFinished();
}

} // namespace tests
} // namespace retdec
