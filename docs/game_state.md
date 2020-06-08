# Game-State Documentation
### The official documentation for the GAME STATE sector of chiventure.
##### Developed by Anant Matai, Lindsey Hsi, Patrick Koopmans, Yifan Liu, and Jessica Xia.

   Game State is responsible for managing the state of the game, such that all data within the game may be returned at any given moment, as the player travels through the world of the game. Due to the nature of this portion of the project, all work serves to provide a foundation for interaction between the work of Action Management, Command-Line Interface, World Description Language, Checkpointing, and User Interface. This entails the implementation of a number of important data structures and accompanying functions that alter these structures as the game progresses. These structures, divided into the modules outlined below, include an overall game struct, which contains a player, room, and item struct.

## Intro

Hello and welcome to game-state and the lit times that will follow! We’re responsible for changing, (as the name perhaps hinted) at changing the state of the game and modifying the structs.

The workflow that we’re in charge of looks a bit like this:

WDL -> Game-state (which is then used by Action Management/Checkpointing/UI)

Action Management -> Game-state (once an action is legal, we provide the functionality that modifies the game state. Eg move room, add object to inventory, etc)

Game-state -> Checkpointing (serializing and de-serializing the game-state)

## Updates

Sprint 1 - Designed initial structs/designs

Sprint 2 - Expanded designs/functionality to include directionality, began functions to modify and construct game states.

## Visual Overview
The following is the tenative game structure (we will implement other features like actions in the next sprint). We will specify each part in the next sections.

![Alt text](https://g.gravizo.com/source/custom_mark10?https%3A%2F%2Fraw.githubusercontent.com%2Fuchicago-cs%2Fchiventure%2Fgame-state%2Fdev%2Fsrc%2Fgame-state%2FREADME.md)
<details>
<summary></summary>
custom_mark10
  digraph G {
    game -> players -> items -> attributes;
    game -> rooms -> items;
    rooms -> paths -> conditions;
  }
custom_mark10
</details>


## The Game module
### Structs
The game module contains a hashtable of **players** and a hashtable of **rooms** (that being said, other teams do not need to know it is implemented with hashtable; it is just a iteratable list of players; other teams do not even need to type and words containing "hash" in their programs; same for all the subsequent modules).

In this sense, everything related to the current game should be stored in this game struct in memory, and is accessible with functions we provided, but other teams should be responsible for checking if each operation they make is legal.

There is also a time_start field, but it does not have specific functionalily right now, so we commented it out.

    typedef struct game {
        /* an iteratable hashtable of players */
        /* using the macros provided in uthash.h */
        /* the expected size is 1 for single player games but this can change */
        player_hash_t all_players;

        /* an iteratable hashtable of rooms */
        /* using the macros provided in uthash.h */
        room_hash_t all_rooms;

        /* pointer to current room struct */
        room_t *curr_room;

        /* pointer to room that, when entered, ends the game */
        room_t *final_room;
        
        /* list of end conditions that, when all are met, ends the game */
        action_condition_list_t *end_conditions;

        /* pointer to current player struct */
        room_t *curr_player;

        /* time when game started */
        //int time_start;
    } game_t;

### Functions

    game_t *game_new();
+ Parameters:
    - none
+ Returns:
    - a new game struct

This functions mallocs space for a new game struct. It does not take any arguments but only creates a new game without rooms and players.

    int game_free(game_t *game);

+ Parameters:
     - game struct that needs to be freed
+ Returns:
     - 0 if successful, 1 if failed

 Frees everything in the game struct safely.

    void game_quit(game_t *game);
+ Parameters:
     - game struct
+ Returns:
     - none

Exits game safely (frees all memory before exits).

    void move_room(game_t *game, room_t *new_room);
+ Parameters:
     - game struct
     - pointer to room that we're changing to
+ Returns:
     - 0 if successful, 1 if failed, 2 if game NULL, 3 if new_room NULL, 4 if new_room is final room

Given the pointer to another room, changes the current room in game-state. 

    int add_final_room_to_game(game_t *game, room_t *final_room)
+  Parameters:
    - game struct
    - pointer to final room
+ Returns: 
    - SUCCESS if successful, FAILURE if failed

 Adds the final_room field to the given game struct
 
    int add_end_condition_to_game(game_t *game, game_action_condition_t *end_condition);
+  Parameters:
    - game struct
    - pointer to end condition
+  Returns:
    - SUCCESS if successful, FAILURE if failed

Adds an end condition to the list end_conditions in the given game struct

    bool end_conditions_met(game_t *game);
+  Parameters:
    - game struct
+  Returns:
    - true if either all end conditions have attributes with expected values or if no end conditions exist
    - false if the attribute of at least one end condition is not expected value

Checks if all end conditions in a given game struct have been met





## The Player Module

In the game, a player is represented by a unique player ID, their chosen username, current level of the game, health, and experience. Further, the player struct contains storage for their inventory and attire. The player module provides functions that allow game authors to:

- create new players
- access and modify player attire + inventory
- access and modify player traits such as health + game level

## The Room Module
The room module provides the framework for a data representation of the physical world of the game. Each room struct stores a unique room ID, a short and long description of the room, an inventory of the items it holds, and a hash table storing the paths into and out of the room alongside their directions. In this documentation, we use the term 'path' to refer to any way a player may move from one room to another (e.g. doors, windows, stairs, portals, etc) On a larger scope, all rooms are also stored in a hash data structure. The functions fleshed out in this module allow authors to:

- create new rooms
- add rooms to the struct containing all the rooms in the game
- access + modify the inventory of the room
- access traits of the room such as its descriptions and possible paths

## The Path Module
The path module deals specifically with the connections among rooms. Each path struct stores a direction, which is used to identify the direction from the starting room, a path destination, which stores the id of the ending room, and a linked list of conditions. All the path connected to each room will be stored in a hash table data structure in that specific room. Functions in the path module allow authors to:

- create new paths
- add paths to the struct containing all the paths or to a room
- access the conditions that have to be satisfied to go through the path

## The Item Module

The item module implements a data structure for items within the game. Each item struct stores a unique item ID, a short and long description, and a container of attributes. These attributes are represented by string keys, whose values can be represented by a variety of types, specifically int, double, char, bool, and string. These attributes signify particular aspects of the item pertinent to the game, i.e. if a door is locked, if the item can be picked up by the player, etc. Functions in the module allow authors to:

- create items + attributes
- modify + replace attributes
- modify items

## Guide of Loading and Saving Game

### Retrieving Game Contents

Macros provided below can help you iterate the game contents like a "for" loop, they take 2 arguments, the first being the parent-level struct, the second being the iterator that you can use in the loop:

- ITER_ALL_PLAYERS(game, curr_player)
- ITER_ALL_ROOMS(game, curr_room)
- ITER_ALL_PATHS(room, curr_path)
- ITER_ALL_CONDITIONS(path, curr_condi)
- ITER_ALL_ITEMS_IN_ROOM(room, curr_item)
- ITER_ALL_ITEMS_IN_INVENTORY(player, curr_item)
- ITER_ALL_ATTRIBUTES(item, curr_attr)

Notice: do not nest 2 same macros, this may cause errors. (2 different is OK.)
Notice: for ITER_ALL_ITEMS_IN_ROOM and ITER_ALL_ITEMS_IN_INVENTORY, curr_item is an item_list_t* and not an item_t*

Here's an example:

    game_t *my_game = game_new();
    ...
    // User playing game
    ...
    // User wants to save the game
    room_t *room_i;
    ITER_ALL_ROOMS(my_game, room_i) {
        printf("%s", room_i->short_desc);
        // Technically it should be frpintf if it should be written to a file
        // Other operations
        ITER_ALL_ITEMS_IN_ROOM(room_i, item_i) {
            printf("%s", item_i->short_desc);
            // other operations
        }
        // Other operations
    }

These macros may help you save the game more conveniently.

### Building Game Contents

Functions provided below can help you add game contents parsed from files to the game struct efficiently. The usage of these functions is very intuitive and the details are described in their corresponding header files.

- int add_player_to_game(game_t \*game, player_t \*player);
- int add_room_to_game(game_t \*game, room_t \*room);
- int add_item_to_player(player_t \*player, item_t \*item);
- int add_item_to_room(room_t \*room, item_t \*item);
- int add_path_to_room(room_t \*room, path_t \*path);
- int add_condition_to_path(path_t \*path, condition_t \*condition);
- int create_new_str_attr(item_t\* item, char\* attr_name, char\* value);
- int create_new_char_attr(item_t\* item, char\* attr_name, char value);
- int create_new_boole_attr(item_t\* item, char\* attr_name, bool value);
- int create_new_double_attr(item_t\* item, char\* attr_name, double value);
- int create_new_int_attr(item_t\* item, char\* attr_name, int value);

Note that the last several create_xxx functions create the attribute and add it to the item at the same time.

Therefore, suppose game-building related teams (wdl/checkpointing) have already parsed the files in their own data structures, they are able to put everything into the game-state structs like this:

    game_t *my_game = game_new();
    for (/* each room */) { // This line depends on how you store the parsed data
        room_t *room = room_new(/* room_params */);
        add_room_to_game(my_game, room);
        for (/* each item in this room */) { // This line also depends on you
            item_t *item = item_new(/* item_params */)
            add_item_to_room(room, item);
            /* ... */
            /* add attributes */
            /* ... */
        }
    }
    /* ... */
    /* add player in the same way */
    /* ... */

