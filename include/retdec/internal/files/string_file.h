///
/// @file      retdec/internal/files/string_file.h
/// @copyright (c) 2015 by Petr Zemek (s3rvac@gmail.com) and contributors
/// @license   MIT, see the @c LICENSE file for more details
/// @brief     File storing its content in a string.
///

#ifndef RETDEC_INTERNAL_FILES_STRING_FILE_H
#define RETDEC_INTERNAL_FILES_STRING_FILE_H

#include <string>

#include "retdec/file.h"

namespace retdec {
namespace internal {

///
/// File storing its content in a string.
///
class StringFile: public File {
public:
	explicit StringFile(std::string content);
	StringFile(std::string content, std::string name);
	virtual ~StringFile() override;

	virtual std::string getName() const override;
	virtual std::string getContent() override;
	virtual void saveCopyTo(const std::string &directoryPath) override;
	virtual void saveCopyTo(const std::string &directoryPath,
		const std::string &name) override;

private:
	/// Content of the file.
	std::string content;

	/// Name of the file.
	std::string name;
};

} // namespace internal
} // namespace retdec

#endif
