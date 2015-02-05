#
# From:        https://github.com/kirkshoop/allup
# Author:      Kirk Shoop <http://kirkshoop.blogspot.com/>
# Modified By: Petr Zemek <s3rvac@gmail.com>
# Licence:     Boost Software License
#

# Finds the C++ Network (CPP-NETLIB) Library
#
#  CPP-NETLIB_INCLUDE_DIR   - Directory to include to get CPP-NETLIB headers
#  CPP-NETLIB_LIBRARIES     - Libraries to link against for the common CPP-NETLIB

SET(_CPP-NETLIB_ALL_PLUGINS    uri client-connections server-parsers)
SET(_CPP-NETLIB_REQUIRED_VARS  CPP-NETLIB_LIBRARIES CPP-NETLIB_INCLUDE_DIR)

#
# Find the headers.
#
FIND_PATH(
    CPP-NETLIB_INCLUDE_DIR boost/network/protocol/http/client.hpp
    PATH "${CPP-NETLIB_SOURCE_DIR}"
    DOC "cppnetlib include directory")
MARK_AS_ADVANCED(CPP-NETLIB_INCLUDE_DIR)

#
# Find all installed plugins if the header was found.
#
IF(CPP-NETLIB_INCLUDE_DIR)

    FOREACH(plugin IN LISTS _CPP-NETLIB_ALL_PLUGINS)
        FIND_LIBRARY(
            CPP-NETLIB_${plugin}_PLUGIN
            NAMES cppnetlib-${plugin}
            HINTS ${CPP-NETLIB_TARGET_DIR}
			PATH_SUFFIXES "" "network/src" "lib${LIB_SUFFIX}")
        MARK_AS_ADVANCED(CPP-NETLIB_${plugin}_PLUGIN)

        IF(CPP-NETLIB_${plugin}_PLUGIN)
            SET(CPP-NETLIB_${plugin}_FOUND True)
            SET(CPP-NETLIB_LIBRARY ${CPP-NETLIB_LIBRARY} ${CPP-NETLIB_${plugin}_PLUGIN})
        ENDIF()
    ENDFOREACH()

    #
    # Check if the required components were all found.
    #
    MESSAGE(STATUS "Found the following CPP-NETLIB libraries:")
    FOREACH(component ${CPP-NETLIB_FIND_COMPONENTS})
        IF(${CPP-NETLIB_${component}_FOUND})
            MESSAGE(STATUS "  ${component}")
            # Does not work with NOT ... . No idea why.
        ELSE()
            MESSAGE(SEND_ERROR "Required component ${component} not found.")
        ENDIF()
    ENDFOREACH()

ENDIF()

FOREACH(component ${CPP-NETLIB_FIND_COMPONENTS})
    SET(CPP-NETLIB_LIBRARIES ${CPP-NETLIB_LIBRARIES} ${CPP-NETLIB_${component}_PLUGIN})
ENDFOREACH()

# Adhere to standards.
include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(CPP-NETLIB DEFAULT_MSG ${_CPP-NETLIB_REQUIRED_VARS})
