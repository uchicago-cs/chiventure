project(libobj C)

# chiventure executable
add_library(libobj
        src/obj.c
        src/parser.c
        src/stack.c)

target_include_directories(libobj PRIVATE src/)

# This is a temporary solution before the directories
# are reorganized
target_include_directories(libobj PRIVATE include/)
foreach(module ${CHIVENTURE_MODULES})
    target_include_directories(libobj PRIVATE ../${module}/include/)
endforeach(module)





