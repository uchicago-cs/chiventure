#include <stdio.h>
#include <stdlib.h>
#include "parser-bison.h"
#include "cli/operations.h"
#include "cli/cmd.h"
#include "cli/parser.h"
#include "common/utlist.h"
#include <criterion/criterion.h>
#include <string.h>
#include <ui/ui.h>
#include "game-state/game.h"
#include "common/ctx.h"

/* Creates a chiventure context with a sample game
 *
 * Parameters: None
 *
 * Returns: a chiventure context
 */
chiventure_ctx_t *create_sample_ctx()
{
    game_t *game = game_new("Welcome to Chiventure!");
    room_t *room1 = room_new("room1", "This is room 1", "Verily, this is the first room.");
    room_t *room2 = room_new("room2", "This is room 2", "Truly, this is the second room.");
    add_room_to_game(game, room1);
    add_room_to_game(game, room2);
    game->curr_room = room1;
    create_connection(game, "room1", "room2", "NORTH");

    /* Create context */
    chiventure_ctx_t *ctx = chiventure_ctx_new(game);

    return ctx;
}


/* create an linked list item of a phrase */
word_ll* start_phrase(char *word) {
    word_ll *head = malloc(sizeof(word_ll));
    head->word = word;
    return head;
}

/* append a word to an existing phrase */
word_ll* append_to_phrase(word_ll *phrase, char *word) {
    word_ll *next = start_phrase(word); // create the linked list item to be appended
    LL_APPEND(phrase, next);
    return phrase;
}

/* this simply prints the phrase associated with the GO command
 * (which is stored as a linked list of words) */
void handle_go_cmd(word_ll *phrase) {
    printf("going to location:");

    if (phrase == NULL) {
        printf(" NULL");
    }
    for (word_ll *p = phrase; p != NULL; p = p->next) {
        /* iterate through list of words */
        printf(" %s", p->word);
    }

    printf("\n");
}

void handle_fight_cmd(word_ll *phrase) {
    printf("starting battle with:");

    if (phrase == NULL) {
        printf(" no one. trying to fight yourself?");
    } 
    for (word_ll *p = phrase; p != NULL; p = p->next) {
        printf(" %s", p->word);
    }
    printf("\n");
}

void handle_credits_cmd(word_ll *phrase) {
    char **tokens = parse(phrase->word);
    chiventure_ctx_t *ctx = create_sample_ctx();
    credits_operation(tokens, ctx);
}
