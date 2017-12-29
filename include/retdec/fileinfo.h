///
/// @file      retdec/fileinfo.h
/// @copyright (c) 2015 by Petr Zemek (s3rvac@gmail.com) and contributors
/// @license   MIT, see the @c LICENSE file for more details
/// @brief     Runner of analyses.
///

#ifndef RETDEC_FILEINFO_H
#define RETDEC_FILEINFO_H

#include <memory>

#include "retdec/service.h"

namespace retdec {

class Analysis;
class AnalysisArguments;
class Settings;

namespace internal {

class ConnectionManager;
class FileinfoImpl;

} // namespace internal

///
/// Runner of analyses.
///
class Fileinfo: public Service {
public:
	/// @name Construction and Destruction
	/// @{
	Fileinfo(const Settings &settings);
	/// @cond internal
	Fileinfo(const Settings &settings,
		const std::shared_ptr<::retdec::internal::ConnectionManager> &connectionManager);
	/// @endcond
	virtual ~Fileinfo() override;
	/// @}

	/// @name Analyses
	/// @{
	std::unique_ptr<Analysis> runAnalysis(const AnalysisArguments &args);
	/// @}

private:
	internal::FileinfoImpl *impl() noexcept;
	const internal::FileinfoImpl *impl() const noexcept;
};

} // namespace retdec

#endif
