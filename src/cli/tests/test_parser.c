#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "parser.h"

/*
//Tests the parsing of an empty input.
Test(parse, no_input)
{
    char **words = parse("");
    cr_assert_null(words[0], "parse() should point to NULL for empty tokens");
    cr_assert_null(words[1], "parse() should point to NULL for empty tokens");
    cr_assert_null(words[2], "parse() should point to NULL for empty tokens");
    cr_assert_null(words[3], "parse() should point to NULL for empty tokens");
}
*/

//Tests the parsing of a single word.
Test(parse, single)
{	
    char **words = parse("LOOK");
    cr_assert_str_eq(words[0],"LOOK", "parse() did not create first token");
    cr_assert_null(words[1], "parse() should point to NULL for empty tokens");
    cr_assert_null(words[2], "parse() should point to NULL for empty tokens");
    cr_assert_null(words[3], "parse() should point to NULL for empty tokens");
}

//Tests the parsing of two words.
Test(parse, two_words)
{
    char **words = parse("LOOK AT");
    cr_assert_str_eq(words[0],"LOOK", "parse() did not create first token");
    cr_assert_str_eq(words[1], "AT", "parse() did not create second token");
    cr_assert_null(words[2],"parse() should point to NULL for empty tokens");
    cr_assert_null(words[3],"parse() should point to NULL for empty tokens");
}

//Tests the parsing of three words.
Test(parse, three_words)
{
    char **words = parse("LOOK AT ME");
    cr_assert_str_eq(words[0],"LOOK", "parse() did not create first token");
    cr_assert_str_eq(words[1], "AT", "parse() did not create second token");
    cr_assert_str_eq(words[2], "ME", "parse() did not create third token");
    cr_assert_null(words[3],"parse() should point to NULL for empty tokens");
}

//Tests the parsing of four words.
Test(parse, four_words)
{
    char **words = parse("LOOK AT ME NOT!");
    cr_assert_str_eq(words[0],"LOOK", "parse() did not create first token");
    cr_assert_str_eq(words[1], "AT", "parse() did not create second token");
    cr_assert_str_eq(words[2], "ME", "parse() did not create third token");
    cr_assert_str_eq(words[3], "NOT!", "parse() did not create fourth token");
}

//Tests the parsing of five words. (Adding more words should not break the parsing)
Test(parse, more_words)
{
    char **words = parse("LOOK AT ME NOT! YEAH!");
    cr_assert_str_eq(words[0],"LOOK", "parse() did not create first token");
    cr_assert_str_eq(words[1], "AT", "parse() did not create second token");
    cr_assert_str_eq(words[2], "ME", "parse() did not create third token");
    cr_assert_str_eq(words[3], "NOT!", "parse() did not create fourth token");
}
