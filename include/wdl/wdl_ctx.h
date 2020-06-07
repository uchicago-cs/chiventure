#include "wdl/common.h"
#include "wdl/objstore.h"

typedef struct wdl_ctx
{
    //a hashtable of objstores containing all parsed objects from a wdl file
    objstore_t *ht;

} wdl_ctx_t;
