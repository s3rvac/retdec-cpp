##
## Project:   retdec-cpp
## Copyright: (c) 2015 by Petr Zemek <s3rvac@gmail.com> and contributors
## License:   MIT, see the LICENSE file for more details
##
## CMake configuration file for the tools.
##

if(NOT RETDEC_TOOLS)
	return()
endif()

set(DECOMPILE_SOURCES
	decompile.cpp
)

add_executable(decompile ${DECOMPILE_SOURCES})
target_link_libraries(decompile retdec)

install(TARGETS decompile DESTINATION "${INSTALL_BIN_DIR}")
