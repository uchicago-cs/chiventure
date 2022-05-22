#include <stdio.h>
#include <stdlib.h>
#include "parser-bison.h"

/* use utlist for linked list operations (see docs 
   https://troydhanson.github.io/uthash/utlist.html) */
#include "../../../include/common/utlist.h"

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
