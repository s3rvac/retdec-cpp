##
## Project:   retdec-cpp
## Copyright: (c) 2015-2016 by Petr Zemek <s3rvac@gmail.com> and contributors
## License:   MIT, see the LICENSE file for more details
##
## CMake configuration file for the include files.
##

set(PUBLIC_INCLUDES
	retdec/analysis.h
	retdec/analysis_arguments.h
	retdec/decompilation.h
	retdec/decompilation_arguments.h
	retdec/decompiler.h
	retdec/exceptions.h
	retdec/file.h
	retdec/fileinfo.h
	retdec/fwd_decls.h
	retdec/resource.h
	retdec/resource_arguments.h
	retdec/retdec.h
	retdec/service.h
	retdec/settings.h
	retdec/test.h
)

install(FILES ${PUBLIC_INCLUDES} DESTINATION "${INSTALL_INCLUDE_DIR}/retdec")
