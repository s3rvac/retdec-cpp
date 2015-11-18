##
## Project:   retdec-cpp
## Copyright: (c) 2015 by Petr Zemek <s3rvac@gmail.com> and contributors
## License:   MIT, see the LICENSE file for more details
##
## CMake configuration file for the library source files.
##

set(RETDEC_SOURCES
	decompilation_arguments.cpp
	decompilation.cpp
	decompiler.cpp
	exceptions.cpp
	file.cpp
	internal/connection.cpp
	internal/connection_manager.cpp
	internal/connection_managers/real_connection_manager.cpp
	internal/connections/real_connection.cpp
	internal/files/filesystem_file.cpp
	internal/files/string_file.cpp
	internal/utilities/connection.cpp
	internal/utilities/json.cpp
	internal/utilities/os.cpp
	internal/utilities/string.cpp
	settings.cpp
)

add_library(retdec ${RETDEC_SOURCES})
if(NOT CPP-NETLIB_FOUND)
	add_dependencies(retdec cpp-netlib)
endif()
if(NOT JsonCpp_FOUND)
	add_dependencies(retdec json-cpp)
endif()
target_link_libraries(retdec
	${Boost_LIBRARIES}
	${OPENSSL_LIBRARIES}
	${CPP-NETLIB_LIBRARIES}
	${JsonCpp_LIBRARY}
	${CMAKE_THREAD_LIBS_INIT}
)

install(TARGETS retdec DESTINATION "${INSTALL_LIB_DIR}" EXPORT retdec)
install(EXPORT retdec DESTINATION "${INSTALL_LIB_CMAKE_DIR}")

# Configuration file for find_package(retdec).
configure_file(
	retdec-config.cmake.in
	"${CMAKE_BINARY_DIR}/retdec-config-install.cmake"
	@ONLY
)
install(
	FILES "${CMAKE_BINARY_DIR}/retdec-config-install.cmake"
	DESTINATION "${INSTALL_LIB_CMAKE_DIR}"
	RENAME retdec-config.cmake
)
