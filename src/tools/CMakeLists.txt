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

# Decompiler.

set(DECOMPILER_SOURCES
	decompiler.cpp
)

add_executable(decompiler ${DECOMPILER_SOURCES})
target_link_libraries(decompiler retdec)

install(TARGETS decompiler DESTINATION "${INSTALL_BIN_DIR}")

# Fileinfo.

set(FILEINFO_SOURCES
	fileinfo.cpp
)

add_executable(fileinfo ${FILEINFO_SOURCES})
target_link_libraries(fileinfo retdec)

install(TARGETS fileinfo DESTINATION "${INSTALL_BIN_DIR}")
