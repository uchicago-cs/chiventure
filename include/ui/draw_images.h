#ifndef DRAW_IMAGES_H
#define DRAW_IMAGES_H

#include "game-state/room.h"

/* draw_room_gui
 * Draws a room based on its room id for the split screen in chiventure
 *
 * Parameters:
 *    - width: integer that defines the width of the split screen
 *    - height: integer that defines the height of the split screen
 *    - pos_x: integer that defines the x-coordinate of the center of the image
 *    - pos_y: integer that defines the x-coordinate of the center of the image
 *    - filepath: string that contains the filepath to the directory containing the images
 *    - curr_room: room_t that defines the current room the player is in
 *
 * No value is returned
 */
void draw_room_gui(int width, int height, int pos_x, int pos_y, char *filepath, room_t *curr_room);

/* draw_map
 * Draws the map in the top left corner of the split screen that updates the center room
 * when the player moves rooms
 *
 * Parameters:
 *    - width: integer that defines the width of the split screen
 *    - height: integer that defines the height of the split screen
 *    - curr_room: room_t that defines the current room the player is in
 *
 * No value is returned
 */
void draw_map(int width, int height, room_t *curr_room);

#endif