# README
### The official documentation for the GAME STATE sector of chiventure.
##### Developed by Anant Matai, Lindsey Hsi, Patrick Koopmans, Yifan Liu, and Jessica Xia.


   Game State is responsible for managing the state of the game, such that all data within the game may be returned at any given moment, as the player travels through the world of the game. Due to the nature of this portion of the project, all work serves to provide a foundation for interaction between the work of Action Management, Command-Line Interface, World Description Language, Checkpointing, and User Interface. This entails the implementation of a number of important data structures and accompanying functions that alter these structures as the game progresses. These structures, divided into the modules outlined below, include an overall game struct, which contains a player, room, and item struct. 

## A Visual Overview

![Alt text](https://g.gravizo.com/source/custom_mark10?https%3A%2F%2Fraw.githubusercontent.com%2Fuchicago-cs%2Fchiventure%2Fgame-state%2Fdev%2Fsrc%2Fgame-state%2FREAD_ME.md)
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

## The Game Module

The game module provides functions that offer basic game operations, as follows:

- creating a new game
- moving the player into a new room of the game (i.e. shifting the user's focus within the game world)
- quitting the game
- deleting the game (i.e. freeing all data structures saved in memory)

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

> Written with [StackEdit](https://stackedit.io/).
