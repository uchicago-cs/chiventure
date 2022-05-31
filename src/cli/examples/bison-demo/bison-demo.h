/* This is a linked list of strings, used to store input word-by-word in phrases */
typedef struct _word_ll {
    char *word;
    struct _word_ll *next;
} word_ll;


/* Create a linked list item of a phrase 
 *
 * Parameters: 
 *  - word: a word from the input string (words are separated by spaces)
 *
 * Returns: a single word_ll item. 
 *  - word points to the parameter string 
 *  - next points to NULL
 */
word_ll* start_phrase(char *word);


/* Append a word to the end of an existing phrase 
 * 
 * Parameters:
 *  - phrase: an existing non-null word_ll struct
 *  - word: the word to add
 *
 * Returns: 
 *  - A word_ll struct
 */
word_ll* append_to_phrase(word_ll *phrase, char *word);


/* Takes user input and converts it to an array of strings, like parser.c
 * Also prints each word of input list and each word of output array
 *
 * Parameters:
 *  - phrase: a word_ll struct of strings from input
 *
 * Returns:
 *  - An array of strings, tokenized by word (words are separated by spaces) 
 */
char **handle_cmd(word_ll *phrase);


/* Called when the Bison grammar recognizes a kind 1 action 
 * 
 * Parameters:
 *  - action: A word_ll struct containing just the action word
 *  - phrase: A word_ll struct containing the item to be acted on, word by word,
 *    or NULL if none
 *
 * Returns:
 *  - None
 */
void handle_kind1_cmd(word_ll *action, word_ll *phrase);


/* Called when the Bison grammar recognizes a kind 2 action 
 * 
 * Parameters:
 *  - action: A word_ll struct containing just the action word
 *  - phrase: A word_ll struct containing the intended direction/destination, word by word,
 *    or NULL if none
 *
 * Returns:
 *  - None
 */
void handle_kind2_cmd(word_ll *phrase);


/* Called when the Bison grammar recognizes a kind 3 action 
 * 
 * Parameters:
 *  - action: A word_ll struct containing just the action word
 *  - item1: A word_ll struct containing the first item, word by word, or NULL if none
 *  - item2: A word_ll struct containing the second item, word by word, or NULL if none
 *
 * Returns:
 *  - None
 */
void handle_kind3_cmd(word_ll *action, word_ll *item1, word_ll *item2);


/* Called when the Bison grammar recognizes a kind 4 ation 
 * 
 * Parameters:
 *  - action: A word_ll struct containing just the action word
 *  - phrase: A word_ll struct containing the self attribute to act upon, word by word,
 *    or NULL if none
 *
 * Returns:
 *  - None
 */
void handle_kind4_cmd(word_ll *action, word_ll *phrase);


/* Called when the Bison grammar recognizes an action that does not fit one 
 * of the four action types 
 * 
 * Parameters:
 *  - action: A word_ll struct containing just the action word
 *  - phrase: A word_ll struct containing the target to be acted on, word by word,
 *    or NULL if none
 *
 * Returns:
 *  - None
 */
void handle_misc_cmd(word_ll *action, word_ll *phrase);

