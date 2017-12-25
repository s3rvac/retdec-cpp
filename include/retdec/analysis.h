///
/// @file      retdec/analysis.h
/// @copyright (c) 2015-2017 by Petr Zemek (s3rvac@gmail.com) and contributors
/// @license   MIT, see the @c LICENSE file for more details
/// @brief     Representation of an analysis.
///

#ifndef RETDEC_ANALYSIS_H
#define RETDEC_ANALYSIS_H

#include <functional>
#include <memory>
#include <string>

#include "retdec/resource.h"

namespace retdec {

class File;

namespace internal {

class Connection;
class AnalysisImpl;

} // namespace internal

///
/// Representation of an analysis.
///
class Analysis: public Resource {
public:
	///
	/// What should the waiting member function do when an analysis fails?
	///
	enum class OnError {
		Throw,  ///< Throw AnalysisError when an analysis fails.
		NoThrow ///< Do not throw AnalysisError when an analysis fails.
	};

public:
	/// @cond internal
	Analysis(const std::string &id,
		const std::shared_ptr<::retdec::internal::Connection> &conn);
	/// @endcond
	virtual ~Analysis() override;

	/// @name Waiting For Analysis To Finish
	/// @{
	void waitUntilFinished(OnError onError = OnError::Throw);
	/// @}

	/// @name Obtaining Outputs
	/// @{
	std::shared_ptr<File> getOutputAsFile();
	std::string getOutput();
	/// @}

private:
	internal::AnalysisImpl *impl() noexcept;
	const internal::AnalysisImpl *impl() const noexcept;
};

} // namespace retdec

#endif
