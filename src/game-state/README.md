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


## Game module
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
     - 1 if successful, 0 if failed

 Frees everything in the game struct safely.


    void game_quit(game_t *game);
+ Parameters:
     - game struct
+ Returns:
     - none

Exits game safely (frees all memory before exits).

    void move_to_room(game_t *game, room_t *new_room);
+ Parameters:
     - game struct
     - room that we're changing to
+ Returns:
     - none

Given the pointer to another room, changes the current room in game-state. This function does NOT check if the move is legal.

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

## The Item Module

The item module implements a data structure for items within the game. Each item struct stores a unique item ID, a short and long description, and a container of attributes. These attributes are represented by string keys, whose values can be represented by a variety of types, specifically int, double, char, bool, and string. These attributes signify particular aspects of the item pertinent to the game, i.e. if a door is locked, if the item can be picked up by the player, etc. Functions in the module allow authors to:

- create items + attributes
- modify + replace attributes