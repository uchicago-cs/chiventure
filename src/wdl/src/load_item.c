#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "parse.h"
#include "item.h"



item_t* load_item(wdl_item_t* item)
{
    item_t* ret_item = item_new(item->id, item->short_desc, item->long_desc);

    return ret_item;
}
