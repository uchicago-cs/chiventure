#include "npc_graphics.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    
    /* This will use the npc_line_t list/struct */
    npc_line_t *test_line;
    char *lines_name = "Greeting";
    char *line_content = "Hello traveler!";
    test_line = LineNew(lines_name, line_content);
    test_line->next = NULL;

    printf("%s\n", test_line->line_name);
    printf("%s\n", test_line->line);

    LineFree(test_line);

    /* This will use the npc_action list/struct */
    npc_action_t *test_action;
    char *actions_name = "Starting";
    char *actions_path = "/Users/urunnaanyanwu/chiventure/graphics_sandbox/npc_graphics/testimages/dhirpal/action";
    unsigned int action_frames = 3;
    double action_frequency = 2.0;
    test_action = ActionNew(actions_name,actions_path,action_frames,
                            action_frequency);
    test_action->next = NULL;

    printf("%s\n", test_action->action_name);
    printf("%d\n", test_action->frame_number);

    ActionFree(test_action);

}


    
