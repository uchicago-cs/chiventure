# Adapted from:
#  - https://gitlab.kitware.com/cmake/cmake/issues/17151
#  - https://github.com/sysrepo/sysrepo/blob/master/CMakeModules/FindProtobuf-c.cmake

function(PROTOBUF_GENERATE_C SRCS HDRS)
    if(NOT ARGN)
        message(SEND_ERROR "Error: PROTOBUF_GENERATE_C() called without any proto files")
        return()
    endif()

    if(PROTOBUF_GENERATE_C_APPEND_PATH)
        # Create an include path for each file specified
        foreach(FIL ${ARGN})
            get_filename_component(ABS_FIL ${FIL} ABSOLUTE)
            get_filename_component(ABS_PATH ${ABS_FIL} PATH)
            list(FIND _protobuf_include_path ${ABS_PATH} _contains_already)
            if(${_contains_already} EQUAL -1)
                list(APPEND _protobuf_include_path -I ${ABS_PATH})
            endif()
        endforeach()
    else()
        set(_protobuf_include_path -I ${CMAKE_CURRENT_SOURCE_DIR})
    endif()

    if(DEFINED PROTOBUF_IMPORT_DIRS AND NOT DEFINED Protobuf_IMPORT_DIRS)
        set(Protobuf_IMPORT_DIRS "${PROTOBUF_IMPORT_DIRS}")
    endif()
    if(DEFINED PROTOBUF_IMPORT_DIRS AND NOT DEFINED Protobuf_IMPORT_DIRS)
        set(Protobuf_IMPORT_DIRS "${PROTOBUF_IMPORT_DIRS}")
    endif()

    if(DEFINED Protobuf_IMPORT_DIRS)
        foreach(DIR ${Protobuf_IMPORT_DIRS})
            get_filename_component(ABS_PATH ${DIR} ABSOLUTE)
            list(FIND _protobuf_include_path ${ABS_PATH} _contains_already)
            if(${_contains_already} EQUAL -1)
                list(APPEND _protobuf_include_path -I ${ABS_PATH})
            endif()
        endforeach()
    endif()

    set(${SRCS})
    set(${HDRS})
    foreach(FIL ${ARGN})
        get_filename_component(ABS_FIL ${FIL} ABSOLUTE)
        get_filename_component(FIL_WE ${FIL} NAME_WE)
        if(NOT PROTOBUF_GENERATE_CPP_APPEND_PATH)
            get_filename_component(FIL_DIR ${FIL} DIRECTORY)
            if(FIL_DIR)
                set(FIL_WE "${FIL_DIR}/${FIL_WE}")
            endif()
        endif()

        list(APPEND ${SRCS} "${CMAKE_CURRENT_BINARY_DIR}/protobuf/${FIL_WE}.pb-c.c")
        list(APPEND ${HDRS} "${CMAKE_CURRENT_BINARY_DIR}/protobuf/${FIL_WE}.pb-c.h")

        add_custom_command(
                PRE_BUILD COMMAND ${CMAKE_COMMAND} -E make_directory protobuf/
                OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/protobuf/${FIL_WE}.pb-c.c"
                "${CMAKE_CURRENT_BINARY_DIR}/protobuf/${FIL_WE}.pb-c.h"
                COMMAND  ${Protobuf_PROTOC-C_EXECUTABLE}
                ARGS --c_out  ${CMAKE_CURRENT_BINARY_DIR}/protobuf/ ${_protobuf_include_path} ${ABS_FIL}
                DEPENDS ${ABS_FIL} ${Protobuf_PROTOC-C_EXECUTABLE}
                COMMENT "Running C protocol buffer compiler on ${FIL}"
                VERBATIM )
    endforeach()

    set_source_files_properties(${${SRCS}} ${${HDRS}} PROPERTIES GENERATED TRUE)
    set(${SRCS} ${${SRCS}} PARENT_SCOPE)
    set(${HDRS} ${${HDRS}} PARENT_SCOPE)
endfunction()

# Find the protoc Executable
find_program(Protobuf_PROTOC-C_EXECUTABLE
        NAMES protoc-c
        DOC "The Google Protocol Buffers Compiler C"
        )

find_package(PkgConfig QUIET)
if(PKG_CONFIG_FOUND)
    pkg_check_modules(PC_PROTOBUF-C QUIET protobuf-c)
    set(PROTOBUF-C_DEFINITIONS ${PC_PROTOBUF-C_CFLAGS_OTHER})
endif()

find_path(PROTOBUF-C_INCLUDE_DIR protobuf-c/protobuf-c.h
        HINTS ${PC_PROTOBUF-C_INCLUDEDIR} ${PC_PROTOBUF-C_INCLUDE_DIRS}
        PATH_SUFFIXES protobuf-c)

find_library(PROTOBUF-C_LIBRARY NAMES protobuf-c
        HINTS ${PC_PROTOBUF-C_LIBDIR} ${PC_PROTOBUF-C_LIBRARY_DIRS})

set(PROTOBUF-C_LIBRARIES ${PROTOBUF-C_LIBRARY} )
set(PROTOBUF-C_INCLUDE_DIRS ${PROTOBUF-C_INCLUDE_DIR})

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Protobuf-c  DEFAULT_MSG
        PROTOBUF-C_LIBRARY PROTOBUF-C_INCLUDE_DIR)

mark_as_advanced(PROTOBUF-C_INCLUDE_DIR)