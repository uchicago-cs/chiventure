#include <stdio.h>
#include <criterion/criterion.h>
#include "item.h"

Test(item, new)
{
  item_t *new_item = item_new("test_item", "This is a new item",
  "This is a new item to check if memory has been correctly allocated");

  cr_assert_not_null(new_item, "item_new() test 1 has failed!");

}
