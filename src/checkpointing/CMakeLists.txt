project(checkpointing C)

set(PROTOBUF_DIRS ${CMAKE_CURRENT_BINARY_DIR}/protobuf
        ${CMAKE_CURRENT_BINARY_DIR}/protobuf/src/checkpointing/
        .)

protobuf_generate_c(PROTO_SRCS PROTO_HDRS game.proto)

add_library(checkpointing
            src/save.c
            src/load.c
            src/log_save.c
            ${PROTO_SRCS}
            ${PROTO_HDRS} src/save-int.h)

target_include_directories(checkpointing PRIVATE ${PROTOBUF_DIRS})
target_include_directories(checkpointing PRIVATE src/)

target_link_libraries(checkpointing ${PROTOBUF-C_LIBRARIES})

# TODO: Checkpointing uses a private header file from game-state
#       Whatever structs they use should be moved to their public
#       header files.
target_include_directories(checkpointing PRIVATE ../game-state/src/)

# This is a temporary solution before the directories
# are reorganized
target_include_directories(checkpointing PRIVATE include/)
foreach(module ${CHIVENTURE_MODULES})
    target_include_directories(checkpointing PRIVATE ../${module}/include/)
endforeach(module)





