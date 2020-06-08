add_library(playerclass_examples
            class-list.c  
            demo-functions.c
            )

target_include_directories(playerclass_examples PRIVATE src/)

set(PLAYERCLASS_EXAMPLES pc_demo)

add_executable(pc_demo
               pc_demo.c
               demo-functions.c
               class-list.c )

# Link with chiventure libraries
foreach(example ${PLAYERCLASS_EXAMPLES})
  foreach(module ${CHIVENTURE_MODULES})
    target_link_libraries(${example} ${module})
  endforeach(module)
endforeach(example)

add_custom_target(playerclass-examples
          DEPENDS ${PLAYERCLASS_EXAMPLES})
