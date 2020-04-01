# chiventure Documentation

chiventure is a text adventure game engine. In other words, chiventure is not an individual game but, rather, a platform that allows game authors to develop text adventure games using WDL (World Description Language) files.

## Building chiventure

chiventure uses CMake. To build, run
```
mkdir build
cd build
cmake ..
```

#### Dependencies

chiventure depends on `protobuf-c`, `LibYAML` (Yaml), `Curses`, and `criterion`. CMake will warn if any of these are not installed with an error of the form "Could NOT find `<library>`"

If you are missing any of the libraries, see [dependencies.md](dependencies.md) for information on how to install them

## Running chiventure

To run run chiventure, build chiventure and then run
```
./chiventure
```

Once inside chiventure, you can type `HELP` for the list of available commands. In the future, you can load a game from inside chiventure with `LOAD <path_to_wdl_file>`

To run chiventure with a given wdl file preloaded, run
```
./chiventure <path_to_wdl_file>
``` 

To try a sample game, from inside the build directory, run 
```
./chiventure ../tests/wdl/examples/connected_rooms.yaml
```

## (For Game Makers) Making a Chiventure Game

To make a game in chiventure, see [wdl.md](wdl.md) for information on building individual components

Example games can be found in /tests/wdl/examples/, such as [test.yaml](/tests/wdl/examples/test.yaml)

## (For Developers) Component Overview

In-depth documentation for each component can be found in the `/docs` directory. Below is a high-level description of each major component.

#### WDL 

chiventure has a “World Description Language” format that provides the specification of a single game. The WDL component is responsible for defining this language, and for parsing it. Files use the extension `<filename>.wdl`

#### Game State

A game will have some state that chiventure needs to keep track of: rooms, objects in rooms, players, non-player characters, etc. This component models this state, and provides interfaces for simple manipulations of the state of the game (e.g., placing an object in the player’s inventory)

#### Action Management

During the game, a player will be able to perform actions (pushing, pulling, opening, closing, etc.) that will usually affect the state of the game in some way. This component is responsible for processing actions like “take the orb” (and checking whether it is possible to perform that action)

#### Checkpointing

As the state of the game changes, chiventure checkpoints the game so we can resume it at a later time. This component is responsible for defining a file format for saving the state of the game, and providing interfaces for saving/loading this state

#### CLI 

This component will be responsible for providing a command prompt, and parsing the commands entered by the user, and using the game state to validate some commands

#### UI

This component is responsible for any non-CLI elements of the user interface, such as visualizing a map of the game or displaying graphics associated with individual rooms

## Miscellaneous

* [Developer Guidelines](developer.md)
* [Actions Specification](actions.md)
