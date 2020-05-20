#ifndef BATTLE_MOVES_H
#define BATTLE_MOVES_H

#include "battle_structs.h"

/*
 * Allocates a class in the heap.
 *
 * Parameters:
 *  - cl: enum class name
 *  - info: description of player class
 *  - st: enum stat, which stat gets a bonus according to the enum class variable
 *  - bonus: number added to stat named in class->st
 *
 * Returns:
 *  - A pointer to the class, or NULL if a class
 *    cannot be allocated
 */
 class_t *new_class(class_type_t cl, char* info, stats_t st, int bonus);

/*
 * Initializes a class
 *
 * Parameters:
 *  - class: A class. Must point to already allocated memory.
 *  - cl: enum class name
 *  - info: description of player class
 *  - st: enum stat, which stat gets a bonus according to the enum class variable
 *  - bonus: number added to stat named in class->st
 *
 * Returns:
 *  - 0 on success, 1 if an error occurs.
 */
int init_class(class_t *class, class_type_t cl, char* info, stats_t st, int bonus);


#endif
