#include <stdio.h>
#include <stdlib.h>
#include "bison-demo.h"
#include "cli/operations.h"
#include "cli/cmd.h"
#include "cli/parser.h"
#include "common/utlist.h"

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
void handle_kind2_cmd(word_ll *phrase) {
    printf("this is a kind 2 action: ACTION <path>\n");
    printf("going to location:");

    if (phrase == NULL) {
        printf(" NULL");
    }
    for (word_ll *p = phrase; p != NULL; p = p->next) {
        /* iterate through list of words */
        printf(" %s", p->word);
    }

    printf("\n\n");
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

void handle_view_cmd(word_ll *phrase){
    printf("viewing");
}

void handle_kind1_cmd(word_ll *action, word_ll *phrase){
    printf("this is a kind 1 action: ACTION <item>\n");
    char *a = action->word;
    word_ll *p = phrase;
    if (a == NULL) {
        printf("Theres nothing there! \n");
    } else {
        printf("the action is: %s\n", a);
    }
    if (p != NULL) {
        printf("the item is: %s", p->word);
        p = p->next;
    }
    while (p != NULL) {
        printf(" %s", p->word);
        p = p->next;
    }    
    printf("\n\n");
}

void handle_kind3_cmd(word_ll *action, word_ll *item1, word_ll *item2) {
    printf("this is a kind 3 action: ACTION <item> <item>\n");
    char *a = action->word;
    word_ll *p1 = item1;
    word_ll *p2 = item2;
    if (a == NULL) {
        printf("Theres nothing there! \n");
    } else {
        printf("the action is: %s\n", a);
    }
    if (p1 != NULL) {
        printf("item 1 is: %s", p1->word);
        p1 = p1->next;
    }
    while (p1 != NULL) {
        printf(" %s", p1->word);
        p1 = p1->next;
    }
    printf("\n");
    if (p2 != NULL) {
        printf("item 2 is: %s", p2->word);
        p2 = p2->next;
    }
    while (p2 != NULL) {
        printf(" %s", p2->word);
        p2 = p2->next;
    }
    printf("\n\n");
}

void handle_kind4_cmd(word_ll *action, word_ll *phrase) {
    printf("this is a kind 4 action: ACTION <self>\n");   
    char *a = action->word;
    word_ll *p = phrase;
    if (a == NULL) {
        printf("Theres nothing there! \n");
    } else {
        printf("the action is: %s\n", a);
    }
    if (p != NULL) {
        printf("the self attribute is: %s", p->word);
        p = p->next;
    }
    while (p != NULL) {
        printf(" %s", p->word);
        p = p->next;
    }    
    printf("\n\n");
}

void handle_misc_cmd(word_ll *action, word_ll *phrase) {
    printf("this is an action that is not of the 4 action kinds\n");
    char *a = action->word;
    word_ll *p = phrase;
    if (a == NULL) {
        printf("There's nothing there! \n");
    } else {
        printf("the action is: %s", a);
    }
    if (p != NULL) {
        printf("\nthe target is: %s", p->word);
        p = p->next;
    }
    while (p != NULL) {
        printf(" %s", p->word);
        p = p->next;
    }
    printf("\n\n");
}

