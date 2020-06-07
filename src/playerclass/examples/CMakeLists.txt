add_library(playerclass_examples
            class-list.c  
            )

target_include_directories(playerclass_examples PRIVATE src/)

set(PLAYERCLASS_EXAMPLES playerclass_example)

add_executable(playerclass_example
               pc_demo.c)

# Link with chiventure libraries
foreach(example ${PLAYERCLASS_EXAMPLES})
  foreach(module ${CHIVENTURE_MODULES})
    target_link_libraries(${example} ${module})
  endforeach(module)
endforeach(example)

add_custom_target(playerclass-examples
          DEPENDS ${PLAYERCLASS_EXAMPLES})
