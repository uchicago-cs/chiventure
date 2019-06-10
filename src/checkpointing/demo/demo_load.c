#include <stdio.h>
#include <stdlib.h>
#include "load.h"

int main()
{
    game_t *g_t_load = malloc(sizeof(game_t));
    load("save.txt", g_t_load);
    printf("curr_player->player_id: %s\n", g_t_load->curr_player->player_id);
    return 0;
}
