# WDL++ documentation

The official specification documentation for the new WDL++ file format (`.wdz`)

## File format structure

The new WDL++ specification stores game files as an archive (using `libzip`, hence the extension `wdz` as is the convention with zipped formats)

An overview of the directory structure:

<img src="wdz_structure.png" alt="An image of the directory structure of a .wdz file" style="zoom:40%;" />

Note that the names and file extensions, e.g.`bg_room_A.png`  or `snd_lose.wav` are placeholders for now. The asset file formats to be used will depend on the implementations of the graphics and audio teams down the line.

The top level contains two subdirectories:

- `assets` contains subdirectories which contain multimedia assets for the game.
- `game` contains JSON objects that define objects of various types in the game.

### The `game` subdirectory

This directory contains the JSON objects that define the game's objects.

Currently, WDL++ supports a pre-defined set of JSON files; however, we intend to make it easy for other teams and feature branches to add and read their own files in and out of this directory if the need arises.

The JSON object structures for the pre-defined files are listed below.

**Notes:**

- List entries have one example element each to demonstrate what the type of an element should be.

- An `...` indicates that other attributes (key-value pairs) can be specified for this object. This can be done by either game authors or other teams when implementing new features; these attributes will be carried into the C struct representation when the JSON object is read in (see <a href=#interface>Function interface</a>). For game authors, they will also be visible for referencing and setting in custom action sequences. (See documentation for Custom Actions).
- ID fields have a scope within their respective files only; there is no need to worry about name collisions between objects of different types. You can have a room *and* and an item with the same name, for example.

### `player.json`

This file contains attributes for the game's player, as well as any other global game configuration attributes.

The top level is a JSON object:

```json
"player": {
    start_room: "my_room_id",
    intro_text: "lorem ipsum dolor sit amet, welcome to the game",
    ...
}
```

where

- `start_room`: the ID of the room the game starts in
- `intro_text`: the introduction blurb that is printed above the text input area when the game is loaded.

- other attributes that can go here: max inventory slots, max HP, initial player states or attributes that can be changed later in game, etc.

### `rooms.json`

This file contains attributes for each of the game's rooms.

The top level is a JSON **list** of objects, where each object is an individual room:

```json
"rooms": [
    {
        "id": "my_room_id",
        "short_desc": "This is a room",
        "long_desc": "This is a room long",
        "items": ["my_item_id_1"],
        "action_on_entry": "my_action_id",
        ...
    }
]
```

where

- `id`: the ID of the room. 
- `short_desc`: the short description that displays when the player enters the room.
- `long_desc`: the long description that displays when the player looks around the room.
- `items`: a list of item IDs of the items that are in the room.
- `action_on_entry`: the ID of the action to execute when the player enters the room. 
- other attributes that can go here:  A `can_enter` attribute to determine if player can enter the room, etc.

### `items.json`

This file contains attributes for each of the game's items.

The top level is a JSON list of objects, where each object is an individual item:

```json
"items": [
    {
        "id": "my_item_id",
        "short_desc": "This is an item",
        "long_desc": "This is an item long",
        "actions": [
            {"call": "TYPE_ME", "action": "action_id", "params": ""}
        ],
        ...
    }
]
```

where

- `id`: the ID of the item.
- `short_desc`: the short description of the item.
- `long_desc`: the long description that displays when the player looks at the item.
- `actions`: a list of JSON objects, where each object is an individual action call available for the item:
  - `call`: the "command" that the user types to invoke the associated action. The command should be written like `TYPE_ME my_item_id`.
  - `action`: the ID of the action that gets invoked when the player calls the above command.
  - `params`: parameters to pass into the `action` (See Custom Actions documentation)

### `actions.json`

This file contains definitions for each of the game's "action sequences". (Essentially, functions that compose and sequence a set of atomic actions).

Documentation WIP! TODO: Add JSON obj example, and a list of acceptable atomic actions  and syntax to use when defining action sequences.

### `globalconditions.json`

This file contains definitions for each of the game's "global conditions" (conditions that are checked after every player action and can trigger an action on fulfillment)

Documentation WIP

### `npcs.json`

This file contains attributes for each of the game's NPCs (non-player characters).

Documentation WIP (and dependent on NPC teams!)

### `dialogtree.json`

This file contains attributes for the game's dialog trees.

Documentation WIP (and dependent on NPC teams!)

### `...`

Other files can be added by other teams, if the need arises to store more attributes on game load.



<a name="interface"></a>

## Function interface

The interface for other teams and feature branches to access WDL++ data.

Documentation WIP.

