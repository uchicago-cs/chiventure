#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "../../include/battle/moves.h"
//#include "../../include/battle/battle_structs.h"

Test(moves, new)
{
    char *test_str;
    test_str = "Test description";
    
    class_t* class;
    class = new_class(0, test_str, 1, 3.0);
    
    cr_assert_not_null(class, "new_class() failed");

    cr_assert_eq(class->info, test_str, "new_class() didn't set info");
}


Test(moves, init)
{
    class_t class;
    int rc; 
  
    char *test_str;
    test_str = "Test description";

    rc = init_class(&class, 0, test_str, 1, 3.0);

    cr_assert_eq(rc, 0, "init_class() failed");

    cr_assert_eq(class.info, test_str, "init_class() didn't set info");
}
