How to use Save and Load modules
1. Run make, it will create 2 binary files called save and load
2. run ./save [filename] and it will save the example game struct
written in the save.c file
3. run ./load [filename] and it will print to stdout in order:
size of the 2D array, all the elements in the array, a description of
the game, and the current player turn (0 for black, 1 for white).
