add_library(npc
            src/npc.c
            src/rooms-npc.c
            src/dialogue.c)
            
target_link_libraries(npc ${LUA_LIBRARIES})
target_include_directories(npc PRIVATE ${LUA_INCLUDE_DIR})
target_include_directories(npc PRIVATE src/)

# EXAMPLES
add_subdirectory(examples
                 EXCLUDE_FROM_ALL)
                 
