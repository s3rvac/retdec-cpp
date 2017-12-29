///
/// @file      retdec/resource_arguments.h
/// @copyright (c) 2015 by Petr Zemek (s3rvac@gmail.com) and contributors
/// @license   MIT, see the @c LICENSE file for more details
/// @brief     Base class of arguments for all services.
///

#ifndef RETDEC_RESOURCE_ARGUMENTS_H
#define RETDEC_RESOURCE_ARGUMENTS_H

#include <map>
#include <memory>
#include <string>

namespace retdec {

class File;

///
/// Base class of arguments for all services.
///
class ResourceArguments {
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
	ResourceArguments();
	ResourceArguments(const ResourceArguments &other);
	ResourceArguments(ResourceArguments &&other);
	ResourceArguments &operator=(const ResourceArguments &other);
	ResourceArguments &operator=(ResourceArguments &&other);
	~ResourceArguments();
	/// @}

	/// @name Generic Access To Arguments
	/// @{
	ResourceArguments &argument(const std::string &id,
		const std::string &value);
	ResourceArguments withArgument(const std::string &id,
		const std::string &value) const;
	bool hasArgument(const std::string &id) const;
	std::string argument(const std::string &id) const;
	ArgumentIterator argumentsBegin() const;
	ArgumentIterator argumentsEnd() const;
	/// @}

	/// @name Generic Access To Files
	/// @{
	ResourceArguments &file(const std::string &id,
		const std::shared_ptr<File> &file);
	ResourceArguments withFile(const std::string &id,
		const std::shared_ptr<File> &file) const;
	bool hasFile(const std::string &id) const;
	std::shared_ptr<File> file(const std::string &id) const;
	FileIterator filesBegin() const;
	FileIterator filesEnd() const;
	/// @}

protected:
	/// Arguments.
	Arguments arguments;

	/// Files.
	Files files;
};

} // namespace retdec

#endif
