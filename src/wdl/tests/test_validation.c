#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdbool.h>
#include "validate.h"

/*
 * helper function for parsing a YAML file into an object
 */
obj_t *get_doc_obj()
{
    obj_t *obj = obj_new("doc");
    parse_game(PATH, obj);
    return obj;
}

Test(validate, game_type_check)
{
    obj_t *doc = get_doc_obj();
    
    cr_assert_eq()
}
