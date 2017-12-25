##
## Project:   retdec-cpp
## Copyright: (c) 2015-2017 by Petr Zemek <s3rvac@gmail.com> and contributors
## License:   MIT, see the LICENSE file for more details
##
## CMake configuration file for the API documentation.
##

if(NOT RETDEC_DOC)
	return()
endif()

find_package(Doxygen REQUIRED)

set(DOXYGEN_CFG_IN "doxygen.in")
set(DOXYGEN_CFG "${CMAKE_CURRENT_BINARY_DIR}/doxygen.cfg")
# The trailing '/' after html is significant (otherwise, the files would be
# installed into ${INSTALL_DOC_DIR}/html instead of ${INSTALL_DOC_DIR}).
set(DOXYGEN_OUTPUT_DIR "${CMAKE_CURRENT_BINARY_DIR}/html/")

# Properly configure the Doxygen configuration file.
if(RETDEC_INTERNAL_DOC)
	# Generate also internal parts of the documentation.
	set(DOXYGEN_WARNINGS "YES")
	set(DOXYGEN_EXTRACT_PRIVATE "YES")
	set(DOXYGEN_EXTRACT_LOCAL_CLASSES "YES")
	set(DOXYGEN_INTERNAL_DOCS "YES")
	set(DOXYGEN_EXCLUDE_PATTERNS "")
	set(DOXYGEN_EXCLUDE_SYMBOLS "")
	set(DOXYGEN_ENABLED_SECTIONS "internal")
else()
	# Hide internal parts of the documentation.
	set(DOXYGEN_WARNINGS "NO")
	set(DOXYGEN_EXTRACT_PRIVATE "NO")
	set(DOXYGEN_EXTRACT_LOCAL_CLASSES "NO")
	set(DOXYGEN_INTERNAL_DOCS "NO")
	set(DOXYGEN_EXCLUDE_PATTERNS "*/internal/*")
	set(DOXYGEN_EXCLUDE_SYMBOLS "internal")
	set(DOXYGEN_ENABLED_SECTIONS "")
endif()
configure_file("${DOXYGEN_CFG_IN}" "${DOXYGEN_CFG}" @ONLY)

# Add a target to generate the documentation by running Doxygen.
add_custom_target(doc ALL
	COMMAND ${DOXYGEN_EXECUTABLE} "${DOXYGEN_CFG}"
	SOURCES "${DOXYGEN_CFG}"
	WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
	COMMENT "Generating API documentation with Doxygen" VERBATIM
)

# Cleanup.
set_directory_properties(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES "${DOXYGEN_OUTPUT_DIR}")

install(DIRECTORY "${DOXYGEN_OUTPUT_DIR}" DESTINATION "${INSTALL_DOC_DIR}/retdec")
