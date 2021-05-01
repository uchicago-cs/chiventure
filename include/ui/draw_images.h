#ifndef DRAW_IMAGES_H
#define DRAW_IMAGES_H

#include "common/ctx.h"
#include "ui/ui_ctx.h"

/* draw_room
 * Draws a room based on its room number for the split screen in chiventure
 *
 * Parameters:
 *    - room_number: integer that defines the room
 *
 * No value is returned
 */
void draw_room(int room_number);

/* draw_object
 * Draws an object based on its item ID
 *
 * Parameters:
 *    - item_id: a string that defines each item
 *
 * No value is returned
 */
void draw_object(char *item_id);

#endif