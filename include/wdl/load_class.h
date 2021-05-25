/*
 * Header file for loading classes game struct
 */

#ifndef INCLUDE_LOAD_CLASS_H
#define INCLUDE_LOAD_CLASS_H

#include "playerclass/class.h"
#include "game-state/game.h"
#include "libobj/obj.h"

/*
 * Loads all of the classes in the CLASSES attribute of the obj_store (if it exists)
 * into the game.
 * 
 * Parameters: 
 *  - obj_store: The object store holding all game information. If it has as 
 *               CLASSES attribute, loading will commence.
 *  - game: The game struct to load classes into.
 * 
 * Returns:
 *  - SUCCESS if classes loaded successfully, or if the game lacks classes altogether.
 *  - FAILURE if classes did not successfully load.
 */
int load_classes(obj_t* obj_store, game_t* game);

#endif /* INCLUDE_LOAD_CLASS_H */
