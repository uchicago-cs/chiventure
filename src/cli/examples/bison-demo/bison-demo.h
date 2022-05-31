
typedef struct _word_ll {
    char *word;
    struct _word_ll *next;
} word_ll;

word_ll* start_phrase(char *word);

word_ll* append_to_phrase(word_ll *phrase, char *word);

void handle_kind2_cmd(word_ll *phrase);

void handle_fight_cmd(word_ll *phrase);

void handle_credits_cmd(word_ll *phrase);

char **handle_cmd(word_ll *phrase);

void handle_put_cmd(word_ll *phrase);

void handle_use_cmd(word_ll *phrase);

void handle_view_cmd(word_ll *phrase);

void handle_kind1_cmd(word_ll *action, word_ll *phrase);

void handle_kind3_cmd(word_ll *action, word_ll *item1, word_ll *item2);

void handle_kind4_cmd(word_ll *action, word_ll *phrase);

void handle_misc_cmd(word_ll *action, word_ll *phrase);
