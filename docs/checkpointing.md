# Checkpointing Documentation

##### Developed by Sheryl Chin, Christian Fernandes, Jonah Fleishhacker, Jarvis Lam, and Ellyn Liu

Checkpointing is responsible for saving and loading in a Chiventure game. Protocol Buffers is used to serialize/pack/save data in a game struct and again to deserialize/unpack/load the data back into a game struct. 

### Dependencies
* Checkpointing is heavily dependent on game-state's structs and functions and dependent on action-management.
* CLI calls our save and load functions.
* When CLI calls load, the WDL is loaded in first, then our serialized data is loaded in. Basically, our functions write over the game struct to reflect changes that have been made (see semi-incremental saving for more info).

### Implementation
The current implementation uses what we coined as "semi-incremental" saving and loading. This means that instead of saving every aspect of a game, including all the game-state structs that are immutable, we only save the mutable aspects of the structs. For example, attributes and attribute values of items are not saved, as they will not change throughout the game. Paths in rooms are also not saved.

In order for this to work, each load function directly modifies a struct instead of creating a new struct. For example, load_player inside load.c first frees all items in the player's inventory so we have an empty slate to start adding in items that have been saved. Then, we load in the items that have been saved by looking through an array of all items (this array is passed in as an input to the function), comparing item IDs, and adding the items that have the same item IDs as those that have been saved by our save function. In this way, the attributes corresponding to the item do not have to be saved; they will be loaded in with WDL. This procedure is also used to load items into rooms.
