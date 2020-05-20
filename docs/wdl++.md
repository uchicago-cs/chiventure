# WDL++ documentation

The official specification documentation for the new WDL++ file format (`.wdz`)

## File format structure

The new WDL++ specification stores game files as an archive (using `libzip`, hence the extension `wdz` as is the convention with zipped formats)

An overview of the directory structure:

<img src="wdz_structure.png" alt="An image of the directory structure of a .wdz file" width="40%" />

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
- Other than those categorized under `...`, a field is mandatory.
- ID fields have a scope within their respective files only; there is no need to worry about name collisions between objects of different types. You can have a room *and* and an item with the same name, for example.

### `player.json`

This file contains attributes for the game's player, as well as any other global game configuration attributes.

The top level is a JSON object with a single `player` key:

```json
{
"player": {
    "start_room": "my_room_id",
    "intro_text": "lorem ipsum dolor sit amet, welcome to the game",
    ...
}
}
```

where

- `start_room`: the ID of the room the game starts in
- `intro_text`: the introduction blurb that is printed above the text input area when the game is loaded.

- other attributes that can go here: max inventory slots, max HP, initial player states or attributes that can be changed later in game, etc.

### `rooms.json`

This file contains attributes for each of the game's rooms.

The top level is a JSON object with a single `rooms` key. Its value is a **list** of objects, where each object is an individual room:

```json
{
"rooms": [
    {
        "id": "my_room_id",
        "short_desc": "This is a room",
        "long_desc": "This is a room long",
        "items": ["my_item_id_1"],
        "action_on_entry": "my_action_id",
        "actions": [
            {"call": "TYPE_ME", "action": "action_id", "params": ""}
        ],
        "connections": [
            {"direction": "my_direction", "to": "next_room_id"}
        ]
        ...
    }
]
}
```

where

- `id`: the ID of the room. 
- `short_desc`: the short description that displays when the player enters the room.
- `long_desc`: the long description that displays when the player looks around the room.
- `items`: a list of item IDs of the items that are in the room.
- `action_on_entry`: the ID of the action to execute when the player enters the room. 
- `actions`: a list of JSON objects, where each object is an individual action call available for the room:
  - `call`: the "command" that the user types to invoke the associated action. The command should be written like `TYPE_ME my_room_id`.
  - `action`: the ID of the action that gets invoked when the player calls the above command.
- `connections`: a list of JSON objects, where each object is a room that the player can reach from this one:
  - `direction`: the direction (`north`/`south`/`east`/`west`/`up`/`down`) that leads to the new room
  - `to`: the ID of the room that this one connects to in this direction.
- other attributes that can go here:  A `can_enter` attribute to determine if player can enter the room, etc.

Note that with a `can_enter` attribute PLUS the functionality of global conditionals (see below), one can
effectively create **room entry conditions** based on states of attributes of other objects, or the state of 
the player inventory, or anything else able to be checked by a conditional predicate.


### `items.json`

This file contains attributes for each of the game's items.

The top level is a JSON object with a single `items` key. Its value is a list of objects, where each object is an individual item:

```json
{
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
}
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

The top level is a JSON object with a single `actions` key. Its value is a list of objects, where each object specifies an action:

```json
{
"actions": [
    {
        "id": "my_action_id",
        "sequence": [
            {"block": "block_here", "args": "args_here"}
        ],
        ...
    }
]
}
```

where
- `id`: the ID of the action.
- `sequence`: The sequence of atomic actions to be carried out (a list of acceptable atomic actions and their syntax can be found on the custom actions wiki page, but an abbreviated version follows)
  - `block`: The name of the atomic action.
  - `args`: The arguments to that atomic action.

Acceptable Atomic Actions:
TODO

Documentation WIP! TODO: Add a list of acceptable atomic actions  and syntax to use when defining action sequences.

### `globalconditions.json`

This file contains definitions for each of the game's "global conditions" (conditions that are checked after every player action and can trigger an action on fulfillment).

The top level is a JSON object with a single `globalconditions` key. Its value is a list of objects, where each object specifies a condition:

Documentation WIP 

```json
{
"globalconditions": [
    {
        "id": "my_condition_id",
        "condition": "my_condition_string",
        "actions": ["action_when_condition_is_met"],
        "trigger_once_only": false
    }
]
}
```

where

- `id` : The condition ID.
- `condition`: The condition string to check globally. **Note** that this condition string has the **same syntax** as the condition strings passed as arguments to `if` blocks in the `actions.json` action block sequences.
- `actions`: The list of actions to be carried out if the condition has been met- can be empty. 
    - `action_id`: The ID of the action.
    - `params`: The parameters to pass into the action (see Custom Actions documentation)
- `trigger_once_only`: a boolean to decide whether this global condition should still be checked once it has been satisfied at least once. `false` means check all the time, regardless of how many times it has been satisfied; `true` means the condition will no longer get checked once the condition has been met once.

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

(WIP)

The interface for other teams and feature branches to access WDL++ data. Our current prototype for the interface includes two functions:


`object_t wdl_get_obj(objFile, objID)`

Params:

- `objFile` : The filename of the file containing the object- e.g. `items.json`

- `objID` : The object ID within the specified file- e.g. `door`

Returns:
- The specified JSON object.

`asset_t wdl_get_asset(assetType, assetName)`

Params:

- `assetType` : The type of the requested asset- e.g. `graphics` or `sounds`
- `assetName` : The filename of the requested asset- e.g `bg_room_A.png`

Returns:
- The requested asset.

These functions would allow other teams to interact with entire JSON objects within their code, adding and changing attributes as they see fit, as well as directly interacting with media assets within the .wdz file.

