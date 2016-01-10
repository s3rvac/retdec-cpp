##
## Project:   retdec-cpp
## Copyright: (c) 2015-2016 by Petr Zemek <s3rvac@gmail.com> and contributors
## License:   MIT, see the LICENSE file for more details
##
## CMake configuration file for the include files.
##

set(PUBLIC_INCLUDES
	retdec/decompilation_arguments.h
	retdec/decompilation.h
	retdec/decompiler.h
	retdec/exceptions.h
	retdec/file.h
	retdec/fwd_decls.h
	retdec/retdec.h
	retdec/settings.h
)

install(FILES ${PUBLIC_INCLUDES} DESTINATION "${INSTALL_INCLUDE_DIR}/retdec")
