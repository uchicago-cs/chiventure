#include "wdl/load_openworld.h"

/* load_itemspecs
 * takes in wdl object and load loads itemspecs into itemspec struct to be used by openworld 
*module
 *
 * parameters:
 * - dialogue_obj: the itemspec object
 * - itemspecs: the itemspec struct it is being loaded into
 *
 * returns;
 * - SUCCESS for successful parse
 * - FAILURE for unsuccessful parse
 */
int load_itemspecs( obj_t  *doc,  itemspec_t* itemspec)
{
    return 0;
}


/*takes in wdl format and populates room_specs, returns success if successful*/
int load_roomspec( obj_t  *doc,  roomspec_t* roomspec )
{
    return 0;
}


/*takes in wdl format and loads gencontext into gen context struct.*/
int load_gen_context( obj_t  *doc,  gencontext_t* gencontext )
{
    return 0;
}



/*takes in wdl format and loads room_level into room_level struct.*/
int load_roomlevel ( obj_t  *doc,  roomlevel_t* roomlevel )
{
    return 0;
}



int load_levelspecs( obj_t  *doc,  levelspec_t* levelspec)
{
    return 0;
}



