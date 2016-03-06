///
/// @file      retdec/analysis_arguments.h
/// @copyright (c) 2015-2016 by Petr Zemek (s3rvac@gmail.com) and contributors
/// @license   MIT, see the @c LICENSE file for more details
/// @brief     Arguments for analyses.
///

#ifndef RETDEC_ANALYSIS_ARGUMENTS_H
#define RETDEC_ANALYSIS_ARGUMENTS_H

#include <map>
#include <memory>
#include <string>

#include "retdec/resource_arguments.h"

namespace retdec {

///
/// Arguments for analyses.
///
class AnalysisArguments: public ResourceArguments {
public:
	/// @name Construction, Assignment, and Destruction
	/// @{
	using ResourceArguments::ResourceArguments;
	using ResourceArguments::operator=;
	~AnalysisArguments();
	/// @}

	/// @name Verbose
	/// @{
	AnalysisArguments &verbose(bool verbose);
	AnalysisArguments withVerbose(bool verbose) const;
	bool hasVerbose() const;
	bool verbose() const;
	/// @}

	/// @name Files: Input
	/// @{
	AnalysisArguments &inputFile(const std::shared_ptr<File> &file);
	AnalysisArguments withInputFile(const std::shared_ptr<File> &file) const;
	bool hasInputFile() const;
	std::shared_ptr<File> inputFile() const;
	/// @}

	/// @name Generic Access To Arguments
	/// @{
	using ResourceArguments::argument;
	AnalysisArguments &argument(const std::string &id,
		const std::string &value);
	AnalysisArguments withArgument(const std::string &id,
		const std::string &value) const;
	/// @}

	/// @name Generic Access To Files
	/// @{
	using ResourceArguments::file;
	AnalysisArguments &file(const std::string &id,
		const std::shared_ptr<File> &file);
	AnalysisArguments withFile(const std::string &id,
		const std::shared_ptr<File> &file) const;
	/// @}
};

} // namespace retdec

#endif
