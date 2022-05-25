find_package(PkgConfig)

find_path(ESPEAK_INCLUDE_DIR speak_lib.h
          PATH_SUFFIXES espeak-ng)

find_library(ESPEAK_LIBRARY NAMES espeak-ng libespeak-ng)

set(ESPEAK_LIBRARIES ${JSONC_LIBRARY})
set(ESPEAK_INCLUDE_DIRS ${JSONC_INCLUDE_DIR})

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Espeak DEFAULT_MSG
        ESPEAK_LIBRARY ESPEAK_INCLUDE_DIR)
mark_as_advanced(ESPEAK_INCLUDE_DIR ESPEAK_LIBRARY)