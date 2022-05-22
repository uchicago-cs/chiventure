
typedef struct _word_ll {
    char *word;
    struct _word_ll *next;
} word_ll;

word_ll* start_phrase(char *word);

word_ll* append_to_phrase(word_ll *phrase, char *word);

void handle_go_cmd(word_ll *phrase);

void handle_fight_cmd(word_ll *phrase);
