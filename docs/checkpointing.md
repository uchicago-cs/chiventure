# Checkpointing Documentation

##### Developed by Sheryl Chin, Christian Fernandes, Jonah Fleishhacker, Jarvis Lam, and Ellyn Liu

Checkpointing is responsible for saving and loading in a Chiventure game. 

### Dependencies
* Checkpointing is heavily dependent on game-state's structs and functions and dependent on action-management.
* CLI calls our save and load functions.
* When CLI calls load, the WDL is loaded in first, then our serialized data is loaded in. Basically, our functions write over the game struct to reflect changes that have been made.


### Implementation
The current implementation uses what we coined as "semi-incremental" saving and loading. This means that instead of saving every aspect of a game, including all the game-state structs that are immutable, we only save the mutable aspects of the structs. For example, attributes and attribute values of items are not saved, as they will not change throughout the game. Paths in rooms are also not saved.
