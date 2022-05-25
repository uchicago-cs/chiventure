/* 
 * Functions to help demo the playerclass struct in pc_demo.c
 */

#ifndef DEMO_FUNCTIONS_H
#define DEMO_FUNCTIONS_H
#include <stdio.h>
#include "playerclass/class.h"
#include "playerclass/class_item.h"
#include "playerclass/class_structs.h"
#include "class-list.h"

/* Displays basic information about a move_list_t of classes and sills. 
 * Currently only displays the name, description, and special skill
 * of each class in the list. 
 * 
 * Parameters:
 * - m: a list of classes with their special skills. 
 * 
 * Returns:
 * - void, but prints out information to console
 */ 
void list_class_show(move_list_t* m);

/* Displays basic information about a class. 
 * Currently only displays the name and descriptions. 
 * 
 * Parameters:
 * - c: a class
 * 
 * Returns:
 * - void, but prints out information to console
 */ 
void class_show(class_t* c);

#endif /* DEMO_FUNCTIONS_H */