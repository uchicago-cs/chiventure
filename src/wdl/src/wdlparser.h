#include <json-c/json.h>
#include <zip.h>
#include <wdl/objstore.h>


void makejsonobj(struct json_object *jobject, const char* filename, zip_t* dir);

objtype_t get_objtype(const char* name);

int parse_wdz(const char *zipdirname);

