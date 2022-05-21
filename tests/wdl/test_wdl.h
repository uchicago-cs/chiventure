#ifndef CHIVENTURE_TEST_WDL_H
#define CHIVENTURE_TEST_WDL_H

/* TODO: This should not be hardcoded here. Find a way to incorporate these
 * files into the CMake-Criterion chain */
#define FILE_PATH "../../../tests/wdl/examples/wdz/connected-rooms/DEFAULT.wdl"
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
static obj_t *__get_doc_obj(char* name, char* file_path);

#endif //CHIVENTURE_TEST_WDL_H
