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

//Tests the parsing of an input of 2 words connected by AND which should return the 2 words.
Test(parse_r, two_words_r)
{
    char* expecting_words[2];
    expecting_words[0] = "LOOK ";
    expecting_words[1] = " PUSH";
    char str[] = "LOOK AND PUSH";
    check_comparison(str, 2, expecting_words);
}

//Tests the parsing of an input of 3 words connected by AND which should return 3 words.
Test(parse_r, three_words_r)
{
    char* expecting_words[3];
    expecting_words[0] = "LOOK ";
    expecting_words[1] = " PUSH ";
    expecting_words[2] = " DESTROY";
    char str[] = "LOOK AND PUSH AND DESTROY";
    check_comparison(str, 3, expecting_words);
}

/*
 * Tests the parsing of an input of 3 words where the first 2 words 
 * are connected by AND to the last word which should return an array of 2 elemets 
 * where the first element has 2 words and the second just has 1 word.
 */
Test(parse_r, two_three_words)
{
    char* expecting_words[2];
    expecting_words[0] = "LOOK PUSH ";
    expecting_words[1] = " DESTROY";
    char str[] = "LOOK PUSH AND DESTROY";
    check_comparison(str, 2, expecting_words);
}

//Tests the parsing of an input of words more than the TOKEN_LIST_SIZE connected by AND.
Test(parse_r, more_than_four_words)
{
    char* expecting_words[5];
    expecting_words[0] = "LOOK PUSH ";
    expecting_words[1] = " DESTROY ";
    expecting_words[2] = " EAT ";
    expecting_words[3] = " DRINK ";
    expecting_words[4] = " SLEEP";
    char str[] = "LOOK PUSH AND DESTROY AND EAT AND DRINK AND SLEEP";
    check_comparison(str, 5, expecting_words);
}

//Tests the parsing of input with many "AND" between each word.
Test(parse_r, multiple_ands)
{
    char* expecting_words[5];
    expecting_words[0] = "LOOK PUSH ";
    expecting_words[1] = " DESTROY ";
    expecting_words[2] = " EAT ";
    expecting_words[3] = " DRINK ";
    expecting_words[4] = " SLEEP";
    char str[] = "LOOK PUSH ANDAND DESTROY AND EAT AND DRINK ANDANDAND SLEEP";
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

//Tests that case-insensitive parsing works on a mixed case word.
Test(parse, insensitivity3)
{
    char str[] = "LoOK";
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
 * Tests the parsing of an input with one token,  a single word surrounded by quotes
 */
Test(parse_r, one_word_quote)
{
    char str[] = "\"South\"";
    char **words = parse(str);
    cr_assert_str_eq(words[0],"south", "parse() did not create first token");
}

/*
 * Tests the parsing of an input with one token, a single word in uppercase surrounded by quotes
 */
Test(parse_r, upper_quote)
{
    char str[] = "\"SOUTH\"";
    char **words = parse(str);
    cr_assert_str_eq(words[0],"south", "parse() did not create first token");
}

/*
 * Tests the parsing of an input with one token, a single word in lowercase surrounded by quotes
 */
Test(parse_r, lower_quote)
{
    char str[] = "\"south\"";
    char **words = parse(str);
    cr_assert_str_eq(words[0],"south", "parse() did not create first token");
}


//Tests the parsing of input which is fully lowercase.
Test(parse, lower)
{
    char str[] = "look at me";
    char **words = parse(str);
    cr_assert_str_eq(words[0],"look", "parse() did not create first token");
    cr_assert_str_eq(words[1], "at", "parse() did not create second token");
    cr_assert_str_eq(words[2], "me", "parse() did not create third token");
    cr_assert_null(words[3],"parse() should point to NULL for empty tokens");
}

//Tests the parsing of input which is just and.
Test(parse, and)
{
    char str[] = "AND";
    char **words = parse(str);
    cr_assert_str_eq(words[0],"and", "parse() did not create first token");
}

//Tests the parsing of input with spaces at the end.
Test(parse, end_spaces)
{
    char str[] ="LOOK AT ME  ";
    char **words = parse(str);
    cr_assert_str_eq(words[0],"look", "parse() did not create first token");
    cr_assert_str_eq(words[1], "at", "parse() did not create second token");
    cr_assert_str_eq(words[2], "me", "parse() did not create third token");
    cr_assert_null(words[3],"parse() should point to NULL for empty tokens");
}

//Tests the parsing of input with spaces at the start.
Test(parse, start_spaces)
{
    char str[] = "   LOOK AT ME";
    char **words = parse(str);
    cr_assert_str_eq(words[0],"look", "parse() did not create first token");
    cr_assert_str_eq(words[1], "at", "parse() did not create second token");
    cr_assert_str_eq(words[2], "me", "parse() did not create third token");
    cr_assert_null(words[3],"parse() should point to NULL for empty tokens");
}

// Tests whether more than 4 words returns NULL as expected
Test(parse, too_many_words)
{
    char str[] = "LOOK LOOK LOOK LOOK LOOK";
    cr_assert_null(parse(str), "parse() did not create first token");
}

// Tests whether more than 4 words in quotes are treated as one token
Test(parse, too_many_words_in_quotes)
{
    char str[] = "\"LOOK LOOK LOOK LOOK LOOK\"";
    char** words = parse(str);
    cr_assert_str_eq("look look look look look", words[0], "parse() did not create first token");
}

//Tests the parsing of an input of 2 words connected by AND which should return the 2 words.
// The ending word is quotes
Test(parse_r, two_words_end)
{
    char* expecting_words[1];
    expecting_words[0] = "LOOK ";
    char str[] = "LOOK AND";
    check_comparison(str, 1, expecting_words);
}

//Tests input in which the and is before any command
Test(parse_r, start_and)
{
    char* expecting_words[1];
    expecting_words[0] = " PUSH";
    char str[] = "AND PUSH";
    check_comparison(str, 1, expecting_words);
}

//Tests input in which the and is before any command
Test(parse_r, and_sandwhich)
{
    char* expecting_words[1];
    expecting_words[0] = " PUSH ";
    char str[] = "AND PUSH AND";
    check_comparison(str, 1, expecting_words);
}

//Tests input filler words at start
Test(parse, fillers_start) 
{
    char str[] = "to to the look";
    char **words = parse(str);
    cr_assert_str_eq("look", words[0], "parse() did not create first token");
}

//Tests input of filler words at end
Test(parse, fillers_end) 
{
    char str[] = "look to to the";
    char **words = parse(str);
    cr_assert_str_eq("look", words[0], "parse() did not create first token");
}

//Tests input of all filler words
Test(parse, all_fillers) 
{
    char str[] = "to the to into";
    char **words = parse(str);
    cr_assert_null(words[0],"parse() should point to NULL for empty tokens");
    cr_assert_null(words[1],"parse() should point to NULL for empty tokens");
    cr_assert_null(words[2],"parse() should point to NULL for empty tokens");
    cr_assert_null(words[3],"parse() should point to NULL for empty tokens");
}

//Tests input of all filler words with random spacing and tabs
Test(parse, all_fillers_with_spaces) 
{
    char str[] = "to     the    to into  ";
    char **words = parse(str);
    cr_assert_null(words[0],"parse() should point to NULL for empty tokens");
    cr_assert_null(words[1],"parse() should point to NULL for empty tokens");
    cr_assert_null(words[2],"parse() should point to NULL for empty tokens");
    cr_assert_null(words[3],"parse() should point to NULL for empty tokens");
}

//Tests input when there are fillers, but the input is too long
Test(parse, fillers_too_long) 
{
    char str[] = "pickup   to the to to into chair";
    char **words = parse(str);
    cr_assert_eq("pickup",words[0],"parse() did not create first token");
    cr_assert_eq("chair",words[1],"parse() did not create second token");
    cr_assert_null(words[2],"parse() should point to NULL for empty tokens");
}


