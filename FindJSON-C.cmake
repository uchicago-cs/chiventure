find_package(PkgConfig)

find_path(JSONC_INCLUDE_DIR json.h
          PATH_SUFFIXES json-c)

find_library(JSONC_LIBRARY NAMES json-c libjson-c)

set(JSONC_LIBRARIES ${JSONC_LIBRARY})
set(JSONC_INCLUDE_DIRS ${JSONC_INCLUDE_DIR})

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(JSON-C DEFAULT_MSG
        JSONC_LIBRARY JSONC_INCLUDE_DIR)
mark_as_advanced(JSONC_INCLUDE_DIR JSONC_LIBRARY)