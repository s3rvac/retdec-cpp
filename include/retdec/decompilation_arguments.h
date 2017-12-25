///
/// @file      retdec/decompilation_arguments.h
/// @copyright (c) 2015-2017 by Petr Zemek (s3rvac@gmail.com) and contributors
/// @license   MIT, see the @c LICENSE file for more details
/// @brief     Arguments for decompilations.
///

#ifndef RETDEC_DECOMPILATION_ARGUMENTS_H
#define RETDEC_DECOMPILATION_ARGUMENTS_H

#include <map>
#include <memory>
#include <string>

#include "retdec/resource_arguments.h"

namespace retdec {

///
/// Arguments for decompilations.
///
class DecompilationArguments: public ResourceArguments {
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
	using ResourceArguments::argument;
	DecompilationArguments &argument(const std::string &id,
		const std::string &value);
	DecompilationArguments withArgument(const std::string &id,
		const std::string &value) const;
	/// @}

	/// @name Generic Access To Files
	/// @{
	using ResourceArguments::file;
	DecompilationArguments &file(const std::string &id,
		const std::shared_ptr<File> &file);
	DecompilationArguments withFile(const std::string &id,
		const std::shared_ptr<File> &file) const;
	/// @}
};

} // namespace retdec

#endif
