##
## Project:   retdec-cpp
## Copyright: (c) 2015 by Petr Zemek <s3rvac@gmail.com>
## License:   MIT, see the LICENSE file for more details
##
## The project's main CMake configuration file.
##

cmake_minimum_required(VERSION 3.0)

project(retdec-cpp CXX C)

##
## Options.
##

option(RETDEC_DOC "Build public API documentation (requires Doxygen)." OFF)
option(RETDEC_INTERNAL_DOC "Build also the internal parts of the API documentation." OFF)
option(RETDEC_TOOLS "Build tools." OFF)
option(RETDEC_COVERAGE "Build with code coverage support (requires lcov and build with tests)." OFF)
option(RETDEC_TESTS "Build tests." OFF)

if(${RETDEC_INTERNAL_DOC})
	set(RETDEC_DOC ON)
endif()

if(${RETDEC_COVERAGE})
	set(RETDEC_TESTS ON)
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

# OpenSSL
find_package(OpenSSL REQUIRED)
include_directories(SYSTEM ${OPENSSL_INCLUDE_DIRS})

# cpp-netlib
find_package(CPP-NETLIB COMPONENTS "uri" "client-connections")
if(NOT CPP-NETLIB_FOUND)
	ExternalProject_Add(cpp-netlib
		URL http://storage.googleapis.com/cpp-netlib-downloads/0.11.1/cpp-netlib-0.11.1-final.zip
		CMAKE_ARGS -DCPP-NETLIB_BUILD_TESTS:BOOL=OFF -DCPP-NETLIB_BUILD_EXAMPLES:BOOL=OFF
		INSTALL_COMMAND ""
		# Wrap the download, configure and build steps in a script to log the
		# output.
		LOG_DOWNLOAD ON
		LOG_CONFIGURE ON
		LOG_BUILD ON
	)
	ExternalProject_Get_Property(cpp-netlib source_dir)
	ExternalProject_Get_Property(cpp-netlib binary_dir)
	set(CPP-NETLIB_INCLUDE_DIR "${source_dir}")
	set(CPP-NETLIB_LIBRARY_DIR "${binary_dir}/libs/network/src")
	set(CPP-NETLIB_LIBRARIES "cppnetlib-uri" "cppnetlib-client-connections")
	link_directories(${CPP-NETLIB_LIBRARY_DIR})
endif()
include_directories(SYSTEM ${CPP-NETLIB_INCLUDE_DIR})
# Enable HTTPS. The following symbol has to be defined prior to including
# cpp-netlib headers.
add_definitions(-DBOOST_NETWORK_ENABLE_HTTPS)

# json-cpp
find_package(JsonCpp)
if(NOT JsonCpp_FOUND)
	ExternalProject_Add(json-cpp
		URL https://github.com/open-source-parsers/jsoncpp/archive/1.0.0.zip
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
	set(JsonCpp_LIBRARY_DIR "${binary_dir}/lib")
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

# C++11 is required.
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pedantic")

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
	if(CXX_COMPILER_VERSION VERSION_GREATER 4.8 OR CXX_COMPILER_VERSION VERSION_EQUAL 4.8)
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wuseless-cast")
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
		COMMAND mkdir -p coverage
		COMMAND lcov --capture --no-external
			--directory include --directory "${PROJECT_BINARY_DIR}/include"
			--directory src --directory "${PROJECT_BINARY_DIR}/src"
			# Comment out the next line if you want to omit test code from the
			# coverage.
			--directory tests --directory "${PROJECT_BINARY_DIR}/tests"
			--output-file coverage/coverage.info
		COMMAND genhtml --show-details --num-spaces 4 --demangle-cpp
			--legend --title "retdec code coverage"
			coverage/coverage.info --output-directory coverage
		WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}")
endif()

##
## Subdirectories.
##

add_subdirectory(doc)
add_subdirectory(include)
add_subdirectory(src)
add_subdirectory(tests)
