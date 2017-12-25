##
## Project:   retdec-cpp
## Copyright: (c) 2015-2017 by Petr Zemek <s3rvac@gmail.com> and contributors
## License:   MIT, see the LICENSE file for more details
##
## CMake configuration file for tests.
##

if(NOT RETDEC_TESTS)
	return()
endif()

##
## Dependencies.
##

# Google Test
find_package(GTest)
if(NOT GTEST_FOUND)
	message(STATUS "  --> GTest will be built as an external project")
	ExternalProject_Add(googletest
		URL http://googletest.googlecode.com/files/gtest-1.7.0.zip
		CMAKE_ARGS
			-DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
		# Disable the install step.
		INSTALL_COMMAND ""
		# Wrap the download, configure and build steps in a script to log the
		# output.
		LOG_DOWNLOAD ON
		LOG_CONFIGURE ON
		LOG_BUILD ON
	)
	ExternalProject_Get_Property(googletest source_dir)
	ExternalProject_Get_Property(googletest binary_dir)
	set(GTEST_INCLUDE_DIR "${source_dir}/include")
	set(GTEST_LIBRARY_DIR "${binary_dir}")
	set(GTEST_LIBRARY "gtest")
	link_directories(${GTEST_LIBRARY_DIR})
endif()
include_directories(SYSTEM ${GTEST_INCLUDE_DIR})

# Google Mock
find_package(GMock)
if(NOT GMOCK_FOUND)
	message(STATUS "  --> GMock will be built as an external project")
	ExternalProject_Add(googlemock
		URL http://googlemock.googlecode.com/files/gmock-1.7.0.zip
		# Disable the install step.
		CMAKE_ARGS
			-DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
		INSTALL_COMMAND ""
		# Wrap the download, configure and build steps in a script to log the
		# output.
		LOG_DOWNLOAD ON
		LOG_CONFIGURE ON
		LOG_BUILD ON
	)
	ExternalProject_Get_Property(googlemock source_dir)
	ExternalProject_Get_Property(googlemock binary_dir)
	set(GMOCK_INCLUDE_DIR "${source_dir}/include")
	set(GMOCK_LIBRARY_DIR "${binary_dir}")
	set(GMOCK_LIBRARY "gmock")
	set(GMOCK_MAIN_LIBRARY "gmock_main")
	link_directories(${GMOCK_LIBRARY_DIR})
endif()
include_directories(SYSTEM ${GMOCK_INCLUDE_DIR})

##
## Includes.
##

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

##
## Subdirectories.
##

add_subdirectory(retdec)
