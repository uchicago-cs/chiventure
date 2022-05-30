/*
Main CMAKE file lines 14-15:

# EXAMPLES
add_subdirectory(examples
                 EXCLUDE_FROM_ALL)

/*
Openworld 2021 demo makefile

set(OPENWORLD_EXAMPLES openworld-demo-2022)

add_executable(openworld-demo-2022
               openworld-demo-2022.c)

# Link with chiventure libraries
foreach(example ${OPENWORLD_EXAMPLES})
    foreach(module ${CHIVENTURE_MODULES})
        target_link_libraries(${example} ${module})
    endforeach(module)
endforeach(example)

add_custom_target(openworld-examples
        DEPENDS ${OPENWORLD_EXAMPLES})
*/        


/*
 * This example program runs a full instance of chiventure with an in-memory game.
 * The CLI is monkey-patched to accept functions that serve to showcase room generation.
 * 
 *  - LEVELGEN: This is a CLI-level operation that triggers level-oriented generation. 
 *              Someday, we hope chiventure will internally use this functionality 
 *              to allow rooms to be automatically generated in a level-oriented way.
 *  - RECURGEN: This is a CLI-level operation that triggers recursive generation. 
 *              Someday, we hope chiventure will internally use this functionality 
 *              to allow rooms within a radius to be generated.
 */

#include <stdio.h>
#include <cli/operations.h>
#include "common/ctx.h"
#include "ui/ui.h"
#include "openworld/autogenerate.h"
#include "game-state/path.h"


#define OUTPUT_BUFFER_SIZE 100


const char *banner = "THIS IS AN OPENWORLD EXAMPLE PROGRAM";

int main(int argc, char **argv)
{   
    return 0;
}
