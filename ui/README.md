To install ncurses on Linux, run the following command:
	`sudo apt-get install libncurses5-dev libncursesw5-dev`

To create the executables simply run `make` inside the ui directory.
Run `make clean` to remove any executable created.

ncurses_ui.c:

    Creates a simple test TUI using the ncurses library. It includes two windows,
    each one covering half the terminal, one on top of the other. The top window
    is surrounded by a box, the bottom one has no border. The top window
    displays the score and number of moves. The bottom window allows for text to
    be inserted.

    It also contains a create_newwin function that allows to create and display
    a new window.

    Partly based on code from: http://tldp.org/HOWTO/NCURSES-Programming-HOWTO/windows.html
