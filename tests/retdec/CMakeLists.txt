##
## Project:   retdec-cpp
## Copyright: (c) 2015-2016 by Petr Zemek <s3rvac@gmail.com> and contributors
## License:   MIT, see the LICENSE file for more details
##
## CMake configuration file for the tests of the library.
##

set(RETDEC_TESTS_SOURCES
	analysis_arguments_tests.cpp
	decompilation_arguments_tests.cpp
	decompilation_tests.cpp
	decompiler_tests.cpp
	exceptions_tests.cpp
	file_tests.cpp
	internal/connection_manager_tests.cpp
	internal/connection_managers/real_connection_manager_tests.cpp
	internal/connection_tests.cpp
	internal/connections/real_connection_tests.cpp
	internal/files/filesystem_file_tests.cpp
	internal/files/string_file_tests.cpp
	internal/utilities/connection_tests.cpp
	internal/utilities/container_tests.cpp
	internal/utilities/json_tests.cpp
	internal/utilities/os_tests.cpp
	internal/utilities/smart_ptr_tests.cpp
	internal/utilities/string_tests.cpp
	resource_arguments_tests.cpp
	settings_tests.cpp
	test_utilities/tmp_file.cpp
)

add_executable(retdec_tests ${RETDEC_TESTS_SOURCES})
if(NOT GTEST_FOUND)
	add_dependencies(retdec googletest)
endif()
if(NOT GMOCK_FOUND)
	add_dependencies(retdec googlemock)
endif()
target_link_libraries(retdec_tests
	retdec
	${GTEST_LIBRARY}
	${GMOCK_LIBRARY}
	${GMOCK_MAIN_LIBRARY}
)

install(TARGETS retdec_tests DESTINATION "${INSTALL_BIN_DIR}/tests")
