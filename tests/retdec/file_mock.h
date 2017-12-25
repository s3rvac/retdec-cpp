///
/// @file      retdec/internal/file_mock.h
/// @copyright (c) 2015-2017 by Petr Zemek (s3rvac@gmail.com) and contributors
/// @license   MIT, see the @c LICENSE file for more details
/// @brief     Mock for File.
///

#ifndef RETDEC_INTERNAL_FILE_MOCK_H
#define RETDEC_INTERNAL_FILE_MOCK_H

#include <gmock/gmock.h>

#include "retdec/file.h"

namespace retdec {
namespace tests {

///
/// Mock for File.
///
class FileMock: public File {
	MOCK_CONST_METHOD0(getName, std::string ());
	MOCK_METHOD0(getContent, std::string ());
	MOCK_METHOD1(saveCopyTo, void (const std::string &));
	MOCK_METHOD2(saveCopyTo, void (const std::string &, const std::string &));
};

} // namespace tests
} // namespace retdec

#endif
