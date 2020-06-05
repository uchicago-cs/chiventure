#include "battle_flow.h"

void read_move(char *move, chiventure_ctx_battle_t *ctx)
{
    int invalid_move = 1;
    while (invalid_move)
    {
        if (strncmp(move, "MOVE USE", 9) == 0)
        {
            //then remove MOVE USE in the string to then get the name of the move
            
            invalid_move = 0;
        }
        else if (strncmp(move, "MOVE LIST", 10) == 0)
        {
            //just print out moves
            invalid_move = 0;
        }
        else if (strncmp(move, "MOVE INFO", 10) == 0)
        {
            // should print out the specific move
        }
        else
        {
            printf("Invalid Move. Please try again... n");
            scanf("%s", &move);
            printf("\n");
        }
    }
}

int main() {
    chiventure_ctx_battle_t *ctx = calloc(1, sizeof(chiventure_ctx_battle_t));
    game_t *g = new_game();
    printf("\nWelcome to the Battle! Let's get this started!\n\n");
    char* move;
    while (battle_over(battle_t * b) == BATTLE_IN_PROGRESS)
    {
        printf("What will you do?\n");
        int i = scanf("%s", move);
        read_move(move, ctx);
        turn_t turn = goes_first(ctx->game->battle);
        printf("\n");
    }
}