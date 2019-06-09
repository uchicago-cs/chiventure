#include "sample_game.h"
#include "actionmanagement.h"
#include "game.h"

int main()
{
    game_t *g = create_sample_game();
    printf("%s", g->start_desc);
    printf("%s", g->curr_room->short_desc);

    lookup_t **action_lookup = lookup_t_new();
    add_action_entries(action_lookup);

    game_free(g);
}
