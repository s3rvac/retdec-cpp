///
/// @file      retdec/analysis_arguments.cpp
/// @copyright (c) 2015-2016 by Petr Zemek (s3rvac@gmail.com) and contributors
/// @license   MIT, see the @c LICENSE file for more details
/// @brief     Implementation of the analysis arguments.
///

#include "retdec/analysis_arguments.h"
#include "retdec/internal/utilities/container.h"

using namespace retdec::internal;

namespace retdec {

namespace {

/// ID for the input file.
const std::string InputFileId = "input";

} // anonymous namespace

///
/// Destructs the arguments.
///
AnalysisArguments::~AnalysisArguments() = default;

///
/// Sets the input file.
///
AnalysisArguments &AnalysisArguments::inputFile(
		const std::shared_ptr<File> &file) {
	return this->file(InputFileId, file);
}

///
/// Returns a copy of the arguments with a different input file.
///
AnalysisArguments AnalysisArguments::withInputFile(
		const std::shared_ptr<File> &file) const {
	return withFile(InputFileId, file);
}

///
/// Is the input file set?
///
bool AnalysisArguments::hasInputFile() const {
	return hasFile(InputFileId);
}

///
/// Returns the input file.
///
std::shared_ptr<File> AnalysisArguments::inputFile() const {
	return file(InputFileId);
}

///
/// Sets the argument of the given ID to the given value.
///
AnalysisArguments &AnalysisArguments::argument(
		const std::string &id, const std::string &value) {
	return static_cast<AnalysisArguments &>(
		ResourceArguments::argument(id, value)
	);
}

///
/// Returns a copy of the arguments with a differing argument of the given ID.
///
AnalysisArguments AnalysisArguments::withArgument(
		const std::string &id, const std::string &value) const {
	auto copy = *this;
	copy.argument(id, value);
	return copy;
}

///
/// Sets the file of the given ID to the given value.
///
AnalysisArguments &AnalysisArguments::file(
		const std::string &id, const std::shared_ptr<File> &file) {
	return static_cast<AnalysisArguments &>(
		ResourceArguments::file(id, file)
	);
}

///
/// Returns a copy of the files with a differing file of the given ID.
///
AnalysisArguments AnalysisArguments::withFile(
		const std::string &id, const std::shared_ptr<File> &file) const {
	auto copy = *this;
	copy.file(id, file);
	return copy;
}

} // namespace retdec
