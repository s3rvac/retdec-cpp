///
/// @file      retdec/resource_arguments.cpp
/// @copyright (c) 2015-2016 by Petr Zemek (s3rvac@gmail.com) and contributors
/// @license   MIT, see the @c LICENSE file for more details
/// @brief     Implementation of the base class of arguments for all services.
///

#include "retdec/resource_arguments.h"

namespace retdec {

namespace {

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
/// Constructs default arguments.
///
ResourceArguments::ResourceArguments() = default;

///
/// Copy-constructs arguments from the given arguments.
///
ResourceArguments::ResourceArguments(
	const ResourceArguments &) = default;

///
/// Move-constructs arguments from the given arguments.
///
ResourceArguments::ResourceArguments(
	ResourceArguments &&) = default;

///
/// Copy-assigns the given arguments.
///
ResourceArguments &ResourceArguments::operator=(
	const ResourceArguments &) = default;

///
/// Move-assigns the given arguments.
///
ResourceArguments &ResourceArguments::operator=(
	ResourceArguments &&) = default;

///
/// Destructs the arguments.
///
ResourceArguments::~ResourceArguments() = default;

///
/// Sets the argument of the given ID to the given value.
///
ResourceArguments &ResourceArguments::argument(
		const std::string &id, const std::string &value) {
	arguments[id] = value;
	return *this;
}

///
/// Returns a copy of the arguments with a differing argument of the given ID.
///
ResourceArguments ResourceArguments::withArgument(
		const std::string &id, const std::string &value) const {
	auto copy = *this;
	copy.argument(id, value);
	return copy;
}

///
/// Is an argument of the given ID present?
///
bool ResourceArguments::hasArgument(const std::string &id) const {
	return hasKey(arguments, id);
}

///
/// Returns the value of the given argument.
///
/// If there is no such argument, it returns the empty string.
///
std::string ResourceArguments::argument(const std::string &id) const {
	return getValue(arguments, id);
}

///
/// Returns an iterator to the beginning of arguments.
///
ResourceArguments::ArgumentIterator ResourceArguments::argumentsBegin() const {
	return arguments.begin();
}

///
/// Returns an iterator past the last argument.
///
ResourceArguments::ArgumentIterator ResourceArguments::argumentsEnd() const {
	return arguments.end();
}

///
/// Sets the file of the given ID to the given value.
///
ResourceArguments &ResourceArguments::file(
		const std::string &id, const std::shared_ptr<File> &file) {
	files[id] = file;
	return *this;
}

///
/// Returns a copy of the files with a differing file of the given ID.
///
ResourceArguments ResourceArguments::withFile(
		const std::string &id, const std::shared_ptr<File> &file) const {
	auto copy = *this;
	copy.file(id, file);
	return copy;
}

///
/// Is a file of the given ID present?
///
bool ResourceArguments::hasFile(const std::string &id) const {
	return hasKey(files, id);
}

///
/// Returns the file of the given ID.
///
/// If there is no such file, it returns the null pointer.
///
std::shared_ptr<File> ResourceArguments::file(const std::string &id) const {
	return getValue(files, id);
}

///
/// Returns an iterator to the beginning of arguments.
///
ResourceArguments::FileIterator ResourceArguments::filesBegin() const {
	return files.begin();
}

///
/// Returns an iterator past the last argument.
///
ResourceArguments::FileIterator ResourceArguments::filesEnd() const {
	return files.end();
}

} // namespace retdec
