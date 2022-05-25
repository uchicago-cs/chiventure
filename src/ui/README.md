# UI library

Contains all modules necessary to run the UI of the game.

# How to use
The UI can right now be run with one function, start_ui(). Calling this function
initializes the UI and begins a game loop. While this function is running, there
are a few currently enabled commands.
* 'Alt-m': Toggles between "main" info screen view and map view
* 'Alt-s': Toggles between layouts with the CLI on the top or bottom half of the
screen.
* 'Ctrl-D': Exits the loop. The function will end and the UI will close.

To compile the ui library, run make inside the chiventure/build directory. Example
files can be found in the src/ui/examples subdirectory from build. You can create
the binaries for all of these files by running `make` inside the examples 
subdirectory or using `make file_name` for a specific example. Use `./file_name`
to run the executable.

Current available examples:
* split_screen_example - sample screen with command line on bottom and graphic
			 on top
* map_raylib_example   - sample map built using raylib

# Included Modules

The UI Library consists of the following modules:
* window
* print_functions
* ui
* map
* coordinate

## window
Contains a new window_t struct that has a ncurses WINDOW field and a print function
field. It contains the functions necessary to declare window_t structs as well as
to free them. It also contains a window_print function that takes in a window_t
as a parameter and calls on the struct's print function

## print_functions
Contains functions that serve as the print function field for different window_t
structs.

## ui
Contains a single function, start_ui, which can be called from a main function
to run the UI. It creates three window_t structs, two of which are displayed
at the same time, one on top of the other. Alt+s can be used to switch the
position of the windows. Alt+m can be used to toggle between the 'map' and the
'main' (the one that displays the score and number of moves).

## map
The map interface consists of a 4 important map control functions
1. map_init initializes a new map_t * and draws rooms inside it
2. map_set_displaywin takes row,column coordinates for the upper left and lower right corners of the window that the map will occupy.
3. map_refresh updates the map to show all of the rooms with the given row/col number of the map aligned to the top left corner of the map's display window
4. map_center_on updates the map to show the room at room coords (x,y,z) at the center of the map. The z coordinate indicates current "floor number". This function will be the primary refresh function for adjusting map position to player location.

## coordinate
Contains a new coord_t struct and a coord_record_t struct that has key, room and 
hash handle. It contains the functions necessary to declare coord_t structs as well as
to free them. It also contains 5 important coordinate functions:
1. find_coord checks if a coordinates are in a room and if they have been marked.
2. try_add_coord tries to add a set of coords to a coordmap, but checks if it
is able to assign a valid coord system.
3. create_valid_map assigns a valid coordinate system creating a pointer to 
a hashmap, if it is successful.
4. get_test_coord_hash gives a pointer to a  hashmap that is utilized in testing.
5. set_player_loc sets a players position to a given coords.
