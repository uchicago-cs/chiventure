#include "npc_graphics.h"
#include "raylib.h"
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

    printf("\n");

    /* This will use the npc_action list/struct */
    npc_action_t *test_action;
    char *actions_name = "Starting";
    char *actions_path = "testimages/dhirpal/action/default.png";
    unsigned int action_frames = 3;
    double action_frequency = 2.0;
    test_action = ActionNew(actions_name,actions_path,action_frames,
                            action_frequency);
    test_action->next = NULL;

    printf("%s\n", test_action->action_name);
    printf("%d\n", test_action->frame_number);
    printf("%s\n", test_action->action_image_path);
    printf("%f\n", test_action->switch_frequency);
    printf("%s\n", test_info->head_line->line_name);

    ActionFree(test_action);

    printf("\n");

    /* This will use and test the npc_info_t list/struct */
    npc_info_t *test_info;
    test_info->npc_name = "Dhirpal"
    test_info->head_action = test_action;
    test_info->head_line = test_line;
    test_info->next = NULL;

    printf("%s\n", test_info->npc_name);
    printf("%s\n", test_info->head_action->action_image_path);
    printf("%d\n", test_info->head_action->frame_number);
    printf("%f\n", test_info->head_action->switch_frequency);

    printf("\n");

    /* This will use and test the npc_graphics_t struct */
    npc_graphics_t *test_npc;

    test_npc->WindowPos = (Vector2){800,0};
    test_npc->WindowSize = (Vector2){400,400};
    test_npc->textcolor = BLACK;
    test_npc->current_npc = test_info->npc_name;    
    test_npc->current_action = test_action->action_name;
    test_npc->current_line = test_line->line_name;
    test_npc->npc_linkedlist = test_info;

    printf("%s\n", test_npc->current_npc);
    printf("%s\n", test_npc->current_action);
    printf("%s\n", test_npc->current_line);
    
    

}


    
