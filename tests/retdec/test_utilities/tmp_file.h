///
/// @file      retdec/test_utilities/tmp_file.h
/// @copyright (c) 2015-2016 by Petr Zemek (s3rvac@gmail.com) and contributors
/// @license   MIT, see the @c LICENSE file for more details
/// @brief     Temporary file utilities.
///

#include <memory>
#include <string>

namespace retdec {
namespace tests {

///
/// A temporary file that is automatically deleted when destructed.
///
class TmpFile {
public:
	~TmpFile();

	std::string getPath() const;

	static std::unique_ptr<TmpFile> createWithContent(
		const std::string &content);

private:
	TmpFile(const std::string &content);

private:
	struct Impl;
	/// Private implementation.
	std::unique_ptr<Impl> impl;
};

///
/// RAII helper that removes the given file in its destructor.
///
class RemoveFileOnDestruction {
public:
	RemoveFileOnDestruction(const std::string &path);
	~RemoveFileOnDestruction();

private:
	/// Path to the file to be removed.
	const std::string path;
};

} // namespace tests
} // namespace retdec
