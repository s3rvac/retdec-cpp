#
# From:        https://github.com/sourcey/libsourcey
# Author:      Kam Low <hello@sourcey.com>
# Modified By: Petr Zemek <s3rvac@gmail.com>
# Licence:     LGPL
#

########################################################################
# Cmake module for finding JsonCpp
#
# The following variabled will be defined:
#
#  JsonCpp_FOUND
#  JsonCpp_INCLUDE_DIR
#  JsonCpp_LIBRARY
#

# ----------------------------------------------------------------------
# Find JsonCpp include path
# ----------------------------------------------------------------------
FIND_PATH(JsonCpp_INCLUDE_DIR
  NAMES
    json/json.h
  PATHS
    ${JsonCpp_SOURCE_DIR}/jsoncpp
    ${JsonCpp_SOURCE_DIR}/jsoncpp/include
)

# ----------------------------------------------------------------------
# Find JsonCpp library
# ----------------------------------------------------------------------
if(WIN32 AND MSVC)

  find_library(JsonCpp_DEBUG_LIBRARY
    NAMES
      jsoncppd
    PATHS
      ${JsonCpp_BUILD_DIR}/jsoncpp
      ${JsonCpp_INSTALL_DIR}/lib
    )

  find_library(JsonCpp_RELEASE_LIBRARY
    NAMES
      jsoncpp
    PATHS
      ${JsonCpp_BUILD_DIR}/jsoncpp
      ${JsonCpp_INSTALL_DIR}/lib
    )

  if(JsonCpp_DEBUG_LIBRARY OR JsonCpp_RELEASE_LIBRARY)
    if(CMAKE_CONFIGURATION_TYPES OR CMAKE_BUILD_TYPE)
      if (JsonCpp_RELEASE_LIBRARY)
        list(APPEND JsonCpp_LIBRARY "optimized" ${JsonCpp_RELEASE_LIBRARY})
      endif()
      if (JsonCpp_DEBUG_LIBRARY)
        list(APPEND JsonCpp_LIBRARY "debug" ${JsonCpp_DEBUG_LIBRARY})
      endif()
    else()
      if (JsonCpp_RELEASE_LIBRARY)
        list(APPEND JsonCpp_LIBRARY ${JsonCpp_RELEASE_LIBRARY})
      elseif (JsonCpp_DEBUG_LIBRARY)
        list(APPEND JsonCpp_LIBRARY ${JsonCpp_DEBUG_LIBRARY})
      endif()
    endif()
    mark_as_advanced(JsonCpp_DEBUG_LIBRARY JsonCpp_RELEASE_LIBRARY)
  endif()

else()

  find_library(JsonCpp_LIBRARY
    NAMES
      jsoncpp
      libjsoncpp
    PATHS
       ${JsonCpp_BUILD_DIR}/jsoncpp
       ${JsonCpp_INSTALL_DIR}/lib
    )

endif()

if(JsonCpp_LIBRARY AND JsonCpp_INCLUDE_DIR)
  set(JsonCpp_FOUND 1)
  mark_as_advanced(JsonCpp_LIBRARY JsonCpp_INCLUDE_DIR)
else()
  set(JsonCpp_FOUND 0)
endif()

# Display status.
if(NOT JsonCpp_FOUND)
   if(JsonCpp_FIND_REQUIRED)
      message(FATAL_ERROR "JsonCpp was not found. Please build dependencies first, or specify the path manually.")
   endif()
endif()

# Adhere to standards.
include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(JsonCpp JsonCpp_INCLUDE_DIR JsonCpp_LIBRARY)
