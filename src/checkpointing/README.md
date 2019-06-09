# Checkpointing Library

## Dependencies
This library is dependent on `protobuf-c`. In order to compile, `protobuf-c` must be installed and properly referenced in the Makefile. 

`protobuf-c` also requires `protobuf` to run. For more information, [protobuf-c](https://github.com/protobuf-c/protobuf-cI./src/checkpointing/include).
 
## How to Use
To compile the library, run `make` inside the checkpointing directory. Examples of `protobuf-c` can be found int the checkpointing/examples/protobuf subdirectory. For more information, cosult the README in the subdirectoFor more information, cosult the README in the subdirectoryy
 
## Functions

## Save

    int save(game_t *g_t, char *filename);
+ Parameters:
    - g_t: a pointer to a game struct
    - filename: the name of the file that info will be saved to
+ Returns:
    - 0 if successful, -1 if not

save.c contains code that takes game-states struct implementation and puts them into the game.proto structs, and packs it (aka serializes the structs into a buffer). Then it opens a blank file, whose name is taken from the command line, and writes the buffer/packed structs into
that file.

## Load

    int load(char *filename, game_t *g_t);
+ Parameters:
    - filename: the name of the file with the saved info
    - g_t: a pointer to an empty game struct to load the information into

load.c contains code which takes the text file that has the serialized structs from
the command line, unpacks (aka deserializes) the information into the game.proto
file, and then takes the information from the game.proto file and puts it into the
dummy structs we created. Further, it prints all the struct information to stdout
to ensure that structs were correctly deserialized and put into the game-state structs.
