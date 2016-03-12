##
## Project:   retdec-cpp
## Copyright: (c) 2015-2016 by Petr Zemek <s3rvac@gmail.com>
## License:   MIT, see the LICENSE file for more details
##
## The project's main CMake configuration file.
##

cmake_minimum_required(VERSION 2.8)

project(retdec-cpp CXX C)

##
## Options.
##

option(RETDEC_DOC "Build public API documentation (requires Doxygen)." OFF)
option(RETDEC_INTERNAL_DOC "Build also the internal parts of the API documentation." OFF)
option(RETDEC_TOOLS "Build tools." OFF)
option(RETDEC_COVERAGE "Build with code coverage support (requires GCC and lcov)." OFF)
option(RETDEC_TESTS "Build tests." OFF)

if(${RETDEC_INTERNAL_DOC})
	set(RETDEC_DOC ON)
endif()

if(${RETDEC_COVERAGE})
	set(RETDEC_TESTS ON)

	# The coverage currently works only for GCC builds.
	if(NOT CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
		message(FATAL_ERROR "Code coverage support requires GCC to be used.")
	endif()
endif()

##
## Paths.
##

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")
if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/install" CACHE PATH "default install path" FORCE)
endif()
set(INSTALL_BIN_DIR "${CMAKE_INSTALL_PREFIX}/bin")
set(INSTALL_DOC_DIR "${CMAKE_INSTALL_PREFIX}/doc")
set(INSTALL_INCLUDE_DIR "${CMAKE_INSTALL_PREFIX}/include")
set(INSTALL_LIB_DIR "${CMAKE_INSTALL_PREFIX}/lib")
set(INSTALL_LIB_CMAKE_DIR "${INSTALL_LIB_DIR}/cmake")

##
## Dependencies.
##

include(ExternalProject)

# The default root directory for external projects.
set_directory_properties(PROPERTIES EP_PREFIX ${CMAKE_BINARY_DIR}/third_party)

# Threads
find_package(Threads REQUIRED)

# Boost
find_package(Boost 1.55 COMPONENTS "filesystem" "system" "thread" REQUIRED)
include_directories(SYSTEM ${Boost_INCLUDE_DIRS})
# A workaround to link error "undefined reference to
# `boost::filesystem::detail::copy_file()" when using Boost < 1.57
# (https://www.robertnitsch.de/notes/cpp/cpp11_boost_filesystem_undefined_reference_copy_file).
add_definitions(-DBOOST_NO_CXX11_SCOPED_ENUMS)

# OpenSSL
find_package(OpenSSL REQUIRED)
include_directories(SYSTEM ${OPENSSL_INCLUDE_DIR})

# cpp-netlib
find_package(CPP-NETLIB COMPONENTS "uri" "client-connections")
if(NOT CPPNETLIB_FOUND)
	message(STATUS "  --> cppnetlib will be built as an external project")
	ExternalProject_Add(cpp-netlib
		URL http://downloads.cpp-netlib.org/0.11.2/cpp-netlib-0.11.2-final.zip
		CMAKE_ARGS
			-DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
			-DCPP-NETLIB_BUILD_TESTS:BOOL=OFF
			-DCPP-NETLIB_BUILD_EXAMPLES:BOOL=OFF
		# Disable the install step.
		INSTALL_COMMAND ""
		# Wrap the download, configure and build steps in a script to log the
		# output.
		LOG_DOWNLOAD ON
		LOG_CONFIGURE ON
		LOG_BUILD ON
	)
	ExternalProject_Get_Property(cpp-netlib source_dir)
	ExternalProject_Get_Property(cpp-netlib binary_dir)
	set(CPPNETLIB_INCLUDE_DIR "${source_dir}")
	set(CPPNETLIB_LIBRARY_DIR "${binary_dir}/libs/network/src")
	set(CPPNETLIB_LIBRARIES "cppnetlib-uri" "cppnetlib-client-connections")
	link_directories(${CPPNETLIB_LIBRARY_DIR})
endif()
include_directories(SYSTEM ${CPPNETLIB_INCLUDE_DIR})
# Enable HTTPS. The following symbol has to be defined prior to including
# cpp-netlib headers.
add_definitions(-DBOOST_NETWORK_ENABLE_HTTPS)

# json-cpp
find_package(JsonCpp)
if(NOT JsonCpp_FOUND)
	message(STATUS "  --> JsonCpp will be built as an external project")
	ExternalProject_Add(json-cpp
		URL https://github.com/open-source-parsers/jsoncpp/archive/1.6.5.zip
		CMAKE_ARGS
			-DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
			-DJSONCPP_WITH_TESTS:BOOL=OFF
		# Disable the install step.
		INSTALL_COMMAND ""
		# Wrap the download, configure and build steps in a script to log the
		# output.
		LOG_DOWNLOAD ON
		LOG_CONFIGURE ON
		LOG_BUILD ON
	)
	ExternalProject_Get_Property(json-cpp source_dir)
	ExternalProject_Get_Property(json-cpp binary_dir)
	set(JsonCpp_INCLUDE_DIR "${source_dir}/include")
	set(JsonCpp_LIBRARY_DIR "${binary_dir}/src/json_lib")
	set(JsonCpp_LIBRARY "jsoncpp")
	link_directories(${JsonCpp_LIBRARY_DIR})
endif()
include_directories(SYSTEM ${JsonCpp_INCLUDE_DIR})

##
## Includes.
##

include_directories(include)

##
## Compiler options.
##

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
	# C++14 is required.
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -pedantic")

	# Abort compilation upon the first error.
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wfatal-errors")

	# Standard warning parameters.
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

	# Enable additional warnings that are not included in -Wall and -Wextra
	# (according to `man gcc`).
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wcast-align")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wcast-qual")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wfloat-equal")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wold-style-cast")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wswitch-default")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wuninitialized")

	# Compiler-specific warnings.
	if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wuseless-cast")
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wzero-as-null-pointer-constant")
	elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wconditional-uninitialized")
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wheader-hygiene")
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wnon-literal-null-conversion")
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wreserved-id-macro")
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wsometimes-uninitialized")
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wunreachable-code")
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wunused-exception-parameter")
	endif()
endif()

##
## Code coverage.
##

if(RETDEC_COVERAGE)
	# Enable code coverage.
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")

	# Build with debugging information to make the output meaningful.
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

	# Disable optimizations to get the most accurate results.
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")

	# Add a custom target to generate the code coverage.
	add_custom_target(coverage
		COMMENT "Running the tests and generating code coverage"
		COMMAND "${PROJECT_BINARY_DIR}/tests/retdec/retdec_tests"
		COMMAND mkdir -p "${PROJECT_BINARY_DIR}/coverage"
		COMMAND lcov --capture --no-external
			--directory include --directory "${PROJECT_BINARY_DIR}/include"
			--directory src --directory "${PROJECT_BINARY_DIR}/src"
			# Comment out the next line if you want to omit test code from the
			# coverage.
			--directory tests --directory "${PROJECT_BINARY_DIR}/tests"
			--output-file "${PROJECT_BINARY_DIR}/coverage/coverage.info"
		COMMAND genhtml --show-details --num-spaces 4 --demangle-cpp
			--legend --title "retdec-cpp code coverage"
			--output-directory "${PROJECT_BINARY_DIR}/coverage"
			"${PROJECT_BINARY_DIR}/coverage/coverage.info"
		WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
	)
endif()

##
## Subdirectories.
##

add_subdirectory(doc)
add_subdirectory(include)
add_subdirectory(src)
add_subdirectory(tests)
