///
/// @file      retdec/internal/files/filesystem_file.h
/// @copyright (c) 2015 by Petr Zemek (s3rvac@gmail.com) and contributors
/// @license   MIT, see the @c LICENSE file for more details
/// @brief     File stored in a filesystem.
///

#ifndef RETDEC_INTERNAL_FILES_FILESYSTEM_FILE_H
#define RETDEC_INTERNAL_FILES_FILESYSTEM_FILE_H

#include <string>

#include "retdec/file.h"

namespace retdec {
namespace internal {

///
/// File stored in a filesystem.
///
class FilesystemFile: public File {
public:
	explicit FilesystemFile(const std::string &path);
	FilesystemFile(std::string path, std::string name);
	virtual ~FilesystemFile() override;

	virtual std::string getName() const override;
	virtual std::string getContent() override;
	virtual void saveCopyTo(const std::string &directoryPath) override;
	virtual void saveCopyTo(const std::string &directoryPath,
		const std::string &name) override;

private:
	/// Path to the file in a filesystem.
	std::string path;

	/// Name of the file to be used.
	std::string name;
};

} // namespace internal
} // namespace retdec

#endif
