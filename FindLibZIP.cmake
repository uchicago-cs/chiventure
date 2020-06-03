find_package(PkgConfig)

find_path(LIBZIP_INCLUDE_DIR zip.h)

find_library(LIBZIP_LIBRARY NAMES zip libzip)

set(LIBZIP_LIBRARIES ${LIBZIP_LIBRARY})
set(LIBZIP_INCLUDE_DIRS ${LIBZIP_INCLUDE_DIR})

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(LibZIP DEFAULT_MSG
        LIBZIP_LIBRARY LIBZIP_INCLUDE_DIR)
mark_as_advanced(LIBZIP_INCLUDE_DIR LIBZIP_LIBRARY)