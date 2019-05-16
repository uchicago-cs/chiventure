# UI library

Contains all modules necessary to run the UI of a game.

The modules contained are the following:
* window
* print_functions
* ui
* map
* coordinate
* DFS

# window
Contains a new window_t struct that has a ncurses WINDOW field and a print function
field. It contains the functions necessary to declare window_t structs as well as
to free them.

# print_functions
Contains functions that serve as the print function field for different window_t
structs.

# ui
Contains a single function, start_ui, which can be called from a main function
to run the UI. It creates three window_t structs, two of which are displayed
at the same time, one on top of the other. Alt+s can be used to switch the
position of the windows. Alt+m can be used to toggle between the 'map' and the
'main' (the one that displays the score and number of moves).

# map

# coordinate

# DFS


To create the library, run `make` inside the ui directory. Example files can be
found in the ui/examples subdirectory. You can create the binaries for these files
by running `make examples` to create the executables for all the examples or
`make examples/file_name` to create a specific executable.
