#ifndef CHIVENTURE_TEST_WDL_H
#define CHIVENTURE_TEST_WDL_H

#include "../../include/libobj/obj.h"

/* TODO: This should not be hardcoded here. Find a way to incorporate these
 * files into the CMake-Criterion chain */
#define FILE_PATH_1 "../../../tests/wdl/examples/wdz/connected-rooms/DEFAULT.wdl"
#define FILE_PATH_2 "../../../tests/wdl/examples/wdl/inventory-cond.wdl"
#define TEST_OUT_PATH "./"

/*
 * helper function for parsing a YAML file into an object
 * 
 * Parameters:
 * - name: the name of the file to be parsed
 * - file_path: the path to the file to be parsed
 * Returns:
 * - a pointer to an object for the game doc
 */
void obj_t *__get_doc_obj(char* name, char* file_path);

#endif //CHIVENTURE_TEST_WDL_H
