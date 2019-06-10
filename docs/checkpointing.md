# Checkpointing Documentation

##### Developed by Sheryl Chin, Christian Fernandes, Jonah Fleishhacker, Jarvis Lam, and Ellyn Liu

Checkpointing is responsible for saving and loading in a Chiventure game. Protocol Buffers is used to serialize/pack/save data in a game struct and again to deserialize/unpack/load the data back into a game struct. 

### Dependencies
* Checkpointing is heavily dependent on game-state's structs and functions. Game-state has provided a list of functions in order for us to access certain data structures in their code, such as hash tables. See GAME-STATE.md in docs for these functions. 
* We are also dependent on action_management, as a few of game-state's structs use action_management's structs.
* CLI calls our save and load functions.
* When CLI calls load, the WDL is loaded in first, then our serialized data is loaded in. Basically, our functions write over the game struct to reflect changes that have been made (see semi-incremental saving under Implementation for more info). An existing game struct MUST BE PROVIDED.

### Protobuf
* Note: This is a general summary of how we used protobuf-c. Please do additional research on protobuf to supplement this explanation.

The player_t struct in player.h inside game-state looks like this:

    /* A player in game */
    typedef struct player {
        /* hh is used for hashtable, as provided in uthash.h*/
        UT_hash_handle hh;
        char *player_id;
        int level;
        int health;
        int xp;
        item_hash_t inventory;
    } player_t;

To serialize a player using protobuf, we design a Player struct in a .proto file. Note that protobuf only supports integers, strings, characters, and arrays. Pointers are not supported by protobuf, so certain workarounds are necessary to save anything that is a pointer in game-state (see Implementation for more information). The Player struct in game.proto is as below:

    message Player {
        required string player_id = 1;
        required int32 level = 2;  
        required int32 health = 3;
        required int32 xp = 4;
        repeated Item inventory = 5; //Array of all object ids in inventory
        optional int32 inventory_len = 6;
    }
    
A repeated field is protobuf's "array." A required field means that some data must be provided for this field during saving, while optional means the field does not need to be filled. You may also notice that the UT_hash_handle hh is left out, as there is no way of saving a hash table with protobuf. Also, as seen above, player_t is game-state's player struct while Player is protobuf's player struct. We follow this naming convention throughout our code, a capital letter for the proto struct and *\_t for game-state's struct.

After deciding upon the structs in the .proto file and running make (instructions for Make are found in README.md inside the checkpointing directory), a .pb-c.h file will be generated that contains functions to be used in save.c and load.c. Such functions include pack and unpack, along with many other functions that come with the protobuf-c library.

### Implementation
The current implementation uses what we coined as "semi-incremental" saving and loading. This means that instead of saving every aspect of a game, including all the game-state structs that are immutable, we only save the mutable aspects of the structs. For example, attributes and attribute values of items are not saved, along with paths in rooms, as they will not change throughout the game. Since we are not saving everything in a game, an existing game struct MUST be loaded in from WDL before load() is called. 

After saving the appropriate data, in order to load back into Chiventure, each load function directly modifies a struct instead of creating or mallocing a new struct. For example, the function  declaration of load_player() in load.c is as follows: 

    int load_player(Player *p, player_t *p_t, item_t **all_items, int all_items_len);

For something simple like loading in the health of the player, we just directly overwrite the health with:

    p_t->health = p->health;
    
Notice that we pass in a protobuf struct, p, that contains the information that has been saved and a player_t struct, p_t, that will be overwritten with the specified information from p.

However, to work with game-state's hash tables, such as the player's inventory, a longer process is needed. Looking at load_player inside load.c, we first free all items in the player's inventory so that we have an empty slate to start adding in items that have been saved (otherwise, you may end up with items in the inventory that are no longer needed). Then, we load in the items that have been saved by looking through all_items, comparing item IDs, and adding the items that have the corresponding item IDs into the inventory. Since the inventory is a hash table, we use the function add_item_to_player provided by game-state to add items into the hash table. In this way, the attributes corresponding to the item do not have to be saved; they will be loaded in with this process. This procedure is also used to load items into rooms. See GAME-STATE.md in docs for more information about functions provided by game-state.

### Modules
There are two main modules in checkpointing: save and load. As the name suggests, save.h and save.c are responsible for saving, or serializing, a game struct into a specified file. The save function:

        int save(game_t *game, char *filename);
        
takes in a game and calls helper functions in order to save all the structs inside a game.

Similarly, load.h and load.c use a similar approach to load in, or deserialize, the data that has been serialized by save(). Calling the function:

        int load(char *filename, game_t *g_t);
        
will in turn call a host of helper functions to unpack all the serialized structs and write the information into a game struct (g_t).
