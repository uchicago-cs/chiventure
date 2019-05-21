Description of our code
Save.c contains code that takes a dummy struct implementation we created and takes
those dummy structs, puts them into the game.proto structs, and packs it (aka
serializes the structs into a buffer). Then it opens a blank text file, whose
name is taken from the command line, and writes the buffer/packed structs into
that file.

Load.c contains code which takes the text file that has the serialized structs from
the command line, unpacks (aka deserializes) the information into the game.proto
file, and then takes the information from the game.proto file and puts it into the
dummy structs we created. Further, it prints all the struct information to stdout
to ensure that structs were correctly deserialized and put into the dummy structs.

How to test our dummy implementation
1. Run make. This will produce 2 binary files in the src folder
named save and load.

2. Use cd to move into the src directory. Then run ./save [filename], where
filename is a blank, arbritrarily chosen empty filename that save will consume, create
the file, and into which it will write the serialized game. The file will then
appear in the src directory.

3. Then to load the game we run ./load [filename], which will take that file that
save had created and put it back into the dummy game structs. This will also print
to stdout the contents of the file, showing our dummy implementation.

