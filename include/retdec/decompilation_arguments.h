///
/// @file      retdec/decompilation_arguments.h
/// @copyright (c) 2015-2016 by Petr Zemek (s3rvac@gmail.com) and contributors
/// @license   MIT, see the @c LICENSE file for more details
/// @brief     Arguments for decompilations.
///

#ifndef RETDEC_DECOMPILATION_ARGUMENTS_H
#define RETDEC_DECOMPILATION_ARGUMENTS_H

#include <map>
#include <memory>
#include <string>

namespace retdec {

class File;

///
/// Arguments for decompilations.
///
class DecompilationArguments {
private:
	/// Container to store arguments.
	using Arguments = std::map<std::string, std::string>;

	/// Container to store files.
	using Files = std::map<std::string, std::shared_ptr<File>>;

public:
	/// Iterator for arguments.
	using ArgumentIterator = Arguments::const_iterator;

	/// Iterator for files.
	using FileIterator = Files::const_iterator;

public:
	/// @name Construction, Assignment, and Destruction
	/// @{
	DecompilationArguments();
	DecompilationArguments(const DecompilationArguments &other);
	DecompilationArguments(DecompilationArguments &&other);
	DecompilationArguments &operator=(const DecompilationArguments &other);
	DecompilationArguments &operator=(DecompilationArguments &&other);
	~DecompilationArguments();
	/// @}

	/// @name Mode
	/// @{
	DecompilationArguments &mode(const std::string &mode);
	DecompilationArguments withMode(const std::string &mode) const;
	bool hasMode() const;
	std::string mode() const;
	/// @}

	/// @name Selective Decompilation: Ranges
	/// @{
	DecompilationArguments &selDecompRanges(const std::string &ranges);
	DecompilationArguments withSelDecompRanges(const std::string &ranges);
	bool hasSelDecompRanges() const;
	std::string selDecompRanges() const;
	/// @}

	/// @name Selective Decompilation: Decoding
	/// @{
	DecompilationArguments &selDecompDecoding(const std::string &decoding);
	DecompilationArguments withSelDecompDecoding(const std::string &decoding);
	bool hasSelDecompDecoding() const;
	std::string selDecompDecoding() const;
	/// @}

	/// @name Files: Input
	/// @{
	DecompilationArguments &inputFile(const std::shared_ptr<File> &file);
	DecompilationArguments withInputFile(const std::shared_ptr<File> &file) const;
	bool hasInputFile() const;
	std::shared_ptr<File> inputFile() const;
	/// @}

	/// @name Generic Access To Arguments
	/// @{
	DecompilationArguments &argument(const std::string &id,
		const std::string &value);
	DecompilationArguments withArgument(const std::string &id,
		const std::string &value) const;
	bool hasArgument(const std::string &id) const;
	std::string argument(const std::string &id) const;
	ArgumentIterator argumentsBegin() const;
	ArgumentIterator argumentsEnd() const;
	/// @}

	/// @name Generic Access To Files
	/// @{
	DecompilationArguments &file(const std::string &id,
		const std::shared_ptr<File> &file);
	DecompilationArguments withFile(const std::string &id,
		const std::shared_ptr<File> &file) const;
	bool hasFile(const std::string &id) const;
	std::shared_ptr<File> file(const std::string &id) const;
	FileIterator filesBegin() const;
	FileIterator filesEnd() const;
	/// @}

private:
	/// Arguments.
	Arguments arguments;

	/// Files.
	Files files;
};

} // namespace retdec

#endif
