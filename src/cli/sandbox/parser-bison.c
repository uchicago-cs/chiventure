#include <stdio.h>
#include <stdlib.h>
#include "parser-bison.h"
#include "cli/operations.h"
#include "cli/cmd.h"
#include "cli/parser.h"
#include "common/utlist.h"
/*#include <criterion/criterion.h>
#include <string.h>
#include <ui/ui.h>
#include "game-state/game.h"
#include "common/ctx.h"
*/
/* Creates a chiventure context with a sample game
 *
 * Parameters: None
 *
 * Returns: a chiventure context
 */
/*
chiventure_ctx_t *create_sample_ctx()
{
    game_t *game = game_new("Welcome to Chiventure!");
    room_t *room1 = room_new("room1", "This is room 1", "Verily, this is the first room.");
    room_t *room2 = room_new("room2", "This is room 2", "Truly, this is the second room.");
    add_room_to_game(game, room1);
    add_room_to_game(game, room2);
    game->curr_room = room1;
    create_connection(game, "room1", "room2", "NORTH");
*/
    /* Create context */
/*    chiventure_ctx_t *ctx = chiventure_ctx_new(game);

    return ctx;
}
*/

/* create an linked list item of a phrase */
word_ll* start_phrase(char *word) {
    word_ll *head = malloc(sizeof(word_ll));
    head->word = word;
    head->next = NULL;
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
//    tokens = parse(phrase->word);
    printf("Class of CMSC 22000 Spring 2019\n"
           "Class of CMSC 22000 Spring 2020\n"
           "Class of CMSC 22000 Spring 2021\n"
           "Class of CMSC 22000 Spring 2022\n");
    /*chiventure_ctx_t *ctx = create_sample_ctx();
    credits_operation(tokens, ctx);
    */
}

void print_ll(word_ll *phrase)
{
    for(int i = 0; phrase!=NULL;phrase=phrase->next,i++) {
        printf("%d'th term = [%s]\n",i,phrase->word);
		
	} 
}
char **handle_cmd(word_ll *p) {
    int LL_MAX_SIZE = 100;
    print_ll(p);
    if (p == NULL) {
        return NULL;
    }
    char **words;
    words = (char**)calloc(LL_MAX_SIZE,sizeof(char*));
    int i = 0;
    while(p != NULL && i < LL_MAX_SIZE) {
        words[i] = p->word;
        p = p->next;
        i++;
    }

    /*
    if (p != NULL && i == LL_MAX_SIZE) {
        return NULL;
    }
    */
    for(int j = 0; j<LL_MAX_SIZE && words[j] != NULL; j++) {
	    printf("%d'th term in array = [%s]\n",j,words[j]);	
	}
    
    return words;
}

void handle_put_cmd(word_ll *phrase) {
    printf("putting:");

    if (phrase == NULL) {
        printf(" nothing there");
    } 
    for (word_ll *p = phrase; p != NULL; p = p->next) {
        printf("%s ", p->word);
        p = p->next;
        if (phrase == NULL) {
            printf("where are you putting this?");
        } 
        for (word_ll *p = phrase; p != NULL; p = p->next) {
            p = p->next;
            printf("%s", p->word);
        }
    }
    printf("\n");
}

void handle_use_cmd(word_ll *phrase) {
    printf("using:");

    if (phrase == NULL) {
        printf(" nothing there");
    } 
    for (word_ll *p = phrase; p != NULL; p = p->next) {
        printf("%s ", p->word);
        p = p->next;
        if (phrase == NULL) {
            printf("where are you putting this?");
        } 
        for (word_ll *p = phrase; p != NULL; p = p->next) {
            p = p->next;
            printf("on %s", p->word);
        }
    }
    printf("\n");
}


