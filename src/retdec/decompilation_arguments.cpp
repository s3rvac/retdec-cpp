///
/// @file      retdec/decompilation_arguments.cpp
/// @copyright (c) 2015-2016 by Petr Zemek (s3rvac@gmail.com) and contributors
/// @license   MIT, see the @c LICENSE file for more details
/// @brief     Implementation of the decompilation arguments.
///

#include "retdec/decompilation_arguments.h"

namespace retdec {

namespace {

/// ID for the input file.
const std::string InputFileId = "input";

/// ID for the mode argument.
const std::string ModeId = "mode";

/// ID for the ranges argument of selective decompilation.
const std::string SelDecompRangesId = "sel_decomp_ranges";

/// ID for the decoding argument of selective decompilation.
const std::string SelDecompDecodingId = "sel_decomp_decoding";

///
/// Has @a map the given key?
///
template <typename Map>
inline bool hasKey(const Map &map, const std::string &key) {
	return map.find(key) != map.end();
}

///
/// Returns the value of the given key in @a map or the default value.
///
template <typename Map>
inline typename Map::mapped_type getValue(const Map &map,
		const std::string &key) {
	auto it = map.find(key);
	return it != map.end() ? it->second : typename Map::mapped_type();
}

} // anonymous namespace

///
/// Destructs the arguments.
///
DecompilationArguments::~DecompilationArguments() = default;

///
/// Sets the mode.
///
/// Available modes are:
/// - <tt>bin</tt>: %Decompilation of a binary file in the ELF or WinPE format.
/// - <tt>c</tt>: %Decompilation of a C file.
///
DecompilationArguments &DecompilationArguments::mode(const std::string &mode) {
	return argument(ModeId, mode);
}

///
/// Returns a copy of the arguments with a different mode.
///
/// See the description of <tt>mode(const std::string &mode)</tt> for more
/// details.
///
DecompilationArguments DecompilationArguments::withMode(
		const std::string &mode) const {
	return withArgument(ModeId, mode);
}

///
/// Is the mode set?
///
bool DecompilationArguments::hasMode() const {
	return hasArgument(ModeId);
}

///
/// Returns the mode.
///
std::string DecompilationArguments::mode() const {
	return argument(ModeId);
}

///
/// Sets ranges for selective decompilation.
///
/// Each range is of the form <tt>ADDRESS-ADDRESS</tt>, where <tt>ADDRESS</tt>
/// is a non-negative hexadecimal number. The ranges have to be divided by
/// commas. The addresses are case-insensitive, so <tt>0xFF</tt> is the same as
/// <tt>0xff</tt>. The addresses can be surrounded by spaces.
///
/// @par Examples
/// @code
/// args.selDecompRanges("0x0-0xffff")
/// args.selDecompRanges("0x0-0x2eef,0x3000-0x4fff")
/// args.selDecompRanges(" 0x0 - 0xfa, 0xFC - 0xFF ")
/// @endcode
///
DecompilationArguments &DecompilationArguments::selDecompRanges(
		const std::string &ranges) {
	return argument(SelDecompRangesId, ranges);
}

///
/// Returns a copy of the arguments with a different ranges for selective
/// decompilation.
///
/// See the description of <tt>selDecompRanges(const std::string &ranges)</tt>
/// for more details.
///
DecompilationArguments DecompilationArguments::withSelDecompRanges(
		const std::string &ranges) {
	return withArgument(SelDecompRangesId, ranges);
}

///
/// Are the ranges for selective decompilation set?
///
bool DecompilationArguments::hasSelDecompRanges() const {
	return hasArgument(SelDecompRangesId);
}

///
/// Returns the ranges for selective decompilation.
///
std::string DecompilationArguments::selDecompRanges() const {
	return argument(SelDecompRangesId);
}

///
/// Sets type of decoding for selective decompilation.
///
DecompilationArguments &DecompilationArguments::selDecompDecoding(
		const std::string &decoding) {
	return argument(SelDecompDecodingId, decoding);
}

///
/// Returns a copy of the arguments with a different type of decoding for
/// selective decompilation.
///
DecompilationArguments DecompilationArguments::withSelDecompDecoding(
		const std::string &decoding) {
	return withArgument(SelDecompDecodingId, decoding);
}

///
/// Is the type of decoding for selective decompilation set?
///
bool DecompilationArguments::hasSelDecompDecoding() const {
	return hasArgument(SelDecompDecodingId);
}

///
/// Returns the type of decoding for selective decompilation.
///
std::string DecompilationArguments::selDecompDecoding() const {
	return argument(SelDecompDecodingId);
}

///
/// Sets the input file.
///
DecompilationArguments &DecompilationArguments::inputFile(
		const std::shared_ptr<File> &file) {
	return this->file(InputFileId, file);
}

///
/// Returns a copy of the arguments with a different input file.
///
DecompilationArguments DecompilationArguments::withInputFile(
		const std::shared_ptr<File> &file) const {
	return withFile(InputFileId, file);
}

///
/// Is the input file set?
///
bool DecompilationArguments::hasInputFile() const {
	return hasFile(InputFileId);
}

///
/// Returns the input file.
///
std::shared_ptr<File> DecompilationArguments::inputFile() const {
	return file(InputFileId);
}

///
/// Sets the argument of the given ID to the given value.
///
DecompilationArguments &DecompilationArguments::argument(
		const std::string &id, const std::string &value) {
	return static_cast<DecompilationArguments &>(
		ResourceArguments::argument(id, value)
	);
}

///
/// Returns a copy of the arguments with a differing argument of the given ID.
///
DecompilationArguments DecompilationArguments::withArgument(
		const std::string &id, const std::string &value) const {
	auto copy = *this;
	copy.argument(id, value);
	return copy;
}

///
/// Sets the file of the given ID to the given value.
///
DecompilationArguments &DecompilationArguments::file(
		const std::string &id, const std::shared_ptr<File> &file) {
	return static_cast<DecompilationArguments &>(
		ResourceArguments::file(id, file)
	);
}

///
/// Returns a copy of the files with a differing file of the given ID.
///
DecompilationArguments DecompilationArguments::withFile(
		const std::string &id, const std::shared_ptr<File> &file) const {
	auto copy = *this;
	copy.file(id, file);
	return copy;
}

} // namespace retdec
