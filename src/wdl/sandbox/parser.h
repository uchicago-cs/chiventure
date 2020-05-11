/*  The header file for the parser code
 *
 */

/* necessary includes to use JSON-C */
#include <json-c/json.h>

/* 
 * parse()
 * 
 * Parameters:
 *  - filename: the path to the file to be parsed
 *
 * Returns:
 *  - a zero for success
 */
json_object *parse(char* filename);

/*
 * main()
 * 
 */
int main(int argc, char **argv);
