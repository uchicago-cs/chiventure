#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "cli/parser.h"
#include "common/utlist.h"

/*
 * helper function to test parse_r in parse module
 * input: input to be parsed, number of strings tokenized, array of strings
 * 
 * uses criterion to assert if what is in the list in a particular iteration
 * is what we expect by putting what we expect in the expected order in 
 * the array of strings.
 */
void check_comparison(char* str, int size, char** expected_words)
{
    tokenized_cmds* words = parse_r(str);
    tokenized_cmds* temp;
    int i = 0;
    LL_FOREACH(words,temp)
    {
        if (i < size)
        {
            if (temp->cmds == NULL)
            {
                cr_assert_null(temp->cmds, "parse() should point to NULL for empty tokens");
            }
            else
            {
                cr_assert_str_eq(temp->cmds, expected_words[i], "Expected token %i to be '%s', got '%s' instead", i, expected_words[i], temp->cmds);
            } 
        }
        i++;
    }          
}

//Tests the parsing of an empty input, which should return NULL.
Test(parse_r, no_input_r)
{
    char* expecting_words[0];
    check_comparison("", 0, expecting_words);
}
//Tests the parsing of a single input. should return the single input itself.
Test(parse_r, single_input_r)
{
    char* expecting_words[1];
    expecting_words[0] = "LOOK";
    char str[] = "LOOK";
    check_comparison(str, 1, expecting_words);
}

//Tests the parsing of an input of 2 words connected by ; which should return the 2 words.
Test(parse_r, two_words_r)
{
    char* expecting_words[2];
    expecting_words[0] = "LOOK ";
    expecting_words[1] = " PUSH";
    char str[] = "LOOK ; PUSH";
    check_comparison(str, 2, expecting_words);
}

//Tests the parsing of an input of 3 words connected by ; which should return 3 words.
Test(parse_r, three_words_r)
{
    char* expecting_words[3];
    expecting_words[0] = "LOOK ";
    expecting_words[1] = " PUSH ";
    expecting_words[2] = " DESTROY";
    char str[] = "LOOK ; PUSH ; DESTROY";
    check_comparison(str, 3, expecting_words);
}

/*
 * Tests the parsing of an input of 3 words where the first 2 words 
 * are connected by ; to the last word which should return an array of 2 elemets 
 * where the first element has 2 words ; the second just has 1 word.
 */
Test(parse_r, two_three_words)
{
    char* expecting_words[2];
    expecting_words[0] = "LOOK PUSH ";
    expecting_words[1] = " DESTROY";
    char str[] = "LOOK PUSH ; DESTROY";
    check_comparison(str, 2, expecting_words);
}

//Tests the parsing of an input of words more than the TOKEN_LIST_SIZE connected by ;.
Test(parse_r, more_than_four_words)
{
    char* expecting_words[5];
    expecting_words[0] = "LOOK PUSH ";
    expecting_words[1] = " DESTROY ";
    expecting_words[2] = " EAT ";
    expecting_words[3] = " DRINK ";
    expecting_words[4] = " SLEEP";
    char str[] = "LOOK PUSH ; DESTROY ; EAT ; DRINK ; SLEEP";
    check_comparison(str, 5, expecting_words);
}

//Tests the parsing of input with many ";" between each word.
Test(parse_r, multiple_semicolons)
{
    char* expecting_words[5];
    expecting_words[0] = "LOOK PUSH ";
    expecting_words[1] = " DESTROY ";
    expecting_words[2] = " EAT ";
    expecting_words[3] = " DRINK ";
    expecting_words[4] = " SLEEP";
    char str[] = "LOOK PUSH ;; DESTROY ; EAT ; DRINK ;;; SLEEP";
    check_comparison(str, 5, expecting_words);
}


//Tests the parsing of an empty input, which should return NULL.
Test(parse, no_input)
{
    char str[] = "";
    char **words = parse(str);
    cr_assert_null(words, "parser() should return NULL if no input");
}

//Tests the parsing of a single word.
Test(parse, single)
{
    char str[] = "LOOK";
    char **words = parse(str);
    cr_assert_str_eq(words[0],"look", "parse() did not create first token");
    cr_assert_null(words[1], "parse() should point to NULL for empty tokens");
    cr_assert_null(words[2], "parse() should point to NULL for empty tokens");
    cr_assert_null(words[3], "parse() should point to NULL for empty tokens");
}

//Tests that case-insensitive parsing works on an all lowercase word.
Test(parse, insensitivity1)
{
    char str[] = "look";
    char **words = parse(str);
    cr_assert_str_eq(words[0],"look", "parse() did not create first token");
    cr_assert_null(words[1], "parse() should point to NULL for empty tokens");
    cr_assert_null(words[2], "parse() should point to NULL for empty tokens");
    cr_assert_null(words[3], "parse() should point to NULL for empty tokens");
}

//Tests that case-insensitive parsing works on a mixed case word.
Test(parse, insensitivity2)
{
    char str[] = "LoOk";
    char **words = parse(str);
    cr_assert_str_eq(words[0],"look", "parse() did not create first token");
    cr_assert_null(words[1], "parse() should point to NULL for empty tokens");
    cr_assert_null(words[2], "parse() should point to NULL for empty tokens");
    cr_assert_null(words[3], "parse() should point to NULL for empty tokens");
}

//Tests the parsing of two words.
Test(parse, two_words)
{
    char str[] = "LOOK AT";
    char **words = parse(str);
    cr_assert_str_eq(words[0],"look", "parse() did not create first token");
    cr_assert_str_eq(words[1], "at", "parse() did not create second token");
    cr_assert_null(words[2],"parse() should point to NULL for empty tokens");
    cr_assert_null(words[3],"parse() should point to NULL for empty tokens");
}

//Tests the parsing of three words.
Test(parse, three_words)
{
    char str[] = "LOOK AT ME";
    char **words = parse(str);
    cr_assert_str_eq(words[0],"look", "parse() did not create first token");
    cr_assert_str_eq(words[1], "at", "parse() did not create second token");
    cr_assert_str_eq(words[2], "me", "parse() did not create third token");
    cr_assert_null(words[3],"parse() should point to NULL for empty tokens");
}

//Tests the parsing of four words.
Test(parse, four_words)
{
    char str[] = "LOOK AT ME NOT";
    char **words = parse(str);
    cr_assert_str_eq(words[0],"look", "parse() did not create first token");
    cr_assert_str_eq(words[1], "at", "parse() did not create second token");
    cr_assert_str_eq(words[2], "me", "parse() did not create third token");
    cr_assert_str_eq(words[3], "not", "parse() did not create fourth token");
}

//Tests the parsing of five words. (Having more words than 4 causes the parser to return NULL)
Test(parse, more_words)
{
    char str[] = "LOOK AT ME NOT YEAH";
    char **words = parse(str);
    cr_assert_null(words, "parser() should return NULL if more than 4 words");
}

//Tests the parsing of input with many spaces between each word.
Test(parse, many_spaces)
{
    char str[] = "LOOK    AT        ME              ";
    char **words = parse(str);
    cr_assert_str_eq(words[0],"look", "parse() did not create first token");
    cr_assert_str_eq(words[1], "at", "parse() did not create second token");
    cr_assert_str_eq(words[2], "me", "parse() did not create third token");
    cr_assert_null(words[3],"parse() should point to NULL for empty tokens");
}

Test(parse, rm_multiple_filler_words)
{
    char str[] = "go to the South";
    char **words = parse(str);
    cr_assert_str_eq(words[0],"go", "parse() did not create first token");
    cr_assert_str_eq(words[1], "south", "parse() did not create second token");
    cr_assert_null(words[2], "parse() should point to NULL for empty tokens");
    cr_assert_null(words[3],"parse() should point to NULL for empty tokens");
}

Test(parse, rm_filler_word)
{
    char str[] = "go to South";
    char **words = parse(str);
    cr_assert_str_eq(words[0],"go", "parse() did not create first token");
    cr_assert_str_eq(words[1], "south", "parse() did not create second token");
    cr_assert_null(words[2], "parse() should point to NULL for empty tokens");
    cr_assert_null(words[3],"parse() should point to NULL for empty tokens");
}

Test(parse, rm_no_filler_word)
{
    char str[] = "go South";
    char **words = parse(str);
    cr_assert_str_eq(words[0],"go", "parse() did not create first token");
    cr_assert_str_eq(words[1], "south", "parse() did not create second token");
    cr_assert_null(words[2], "parse() should point to NULL for empty tokens");
    cr_assert_null(words[3],"parse() should point to NULL for empty tokens");
}

Test(parse, two_function_calls)
{
    char str1[] = "go to South";
    char str2[] = "go to South";
    char **words1 = parse(str1);
    char **words2 = parse(str2);

    cr_assert_str_eq(words1[0], words2[0]);
    cr_assert_str_eq(words1[1], words2[1]);
}
/*
 * Tests the parsing of an input with two tokens, one being a single word surrounded by quotes
 */
Test(parse_r, two_words_quote)
{
    char str[] = "GO \"South\"";
    char **words = parse(str);
    cr_assert_str_eq(words[0],"go", "parse() did not create first token");
    cr_assert_str_eq(words[1],"south", "parse() did not create second token");
}

/*
 * Tests the parsing of an input with two tokens, one being multiple words surrounded by quotes
 */
Test(parse_r, double_word_in_quote)
{
    char str[] = "GO \"Dungeon of Death\"";
    char **words = parse(str);
    cr_assert_str_eq(words[0],"go", "parse() did not create first token");
    cr_assert_str_eq(words[1],"dungeon of death", "parse() did not create second token");
}

/*
 * Tests the parsing of an input with three tokens, one being a word surrounded by quotes
 */
Test(parse_r, three_words_quote)
{
    char str[] = "LOOK TO \"EAST\"";
    char **words = parse(str);
    cr_assert_str_eq(words[0],"look", "parse() did not create first token");
    cr_assert_str_eq(words[1],"east", "parse() did not create third token");
}

/*
 * Tests the parsing of an input with two tokens, the first being surrounded by quotes
 */
Test(parse_r, first_quote)
{
    char str[] = "\"GO\" EAST";
    char **words = parse(str);
    cr_assert_str_eq(words[0],"go", "parse() did not create first token");
    cr_assert_str_eq(words[1],"east", "parse() did not create second token");
}

