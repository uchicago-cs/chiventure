#Checkpointing Library

##Dependencies
This library is dependent on `protobuf-c`. In order to compile, `protobuf-c` must be installed and properly referenced in the Makefile. 

`protobuf-c` also requires `protobuf` to run. For more information, https://github.com/protobuf-c/protobuf-cI./src/checkpointing/include.
  
##Functions

##Save
Save.c contains code that takes a dummy struct implementation we created and takes
those dummy structs, puts them into the game.proto structs, and packs it (aka
serializes the structs into a buffer). Then it opens a blank file, whose name
is taken from the command line, and writes the buffer/packed structs into
that file.

##Load
Load.c contains code which takes the text file that has the serialized structs from
the command line, unpacks (aka deserializes) the information into the game.proto
file, and then takes the information from the game.proto file and puts it into the
dummy structs we created. Further, it prints all the struct information to stdout
to ensure that structs were correctly deserialized and put into the dummy structs.
