## Documentation for `test_game`

As part of the WDL++ spec, I've written a test game in the new format 
to mock up some of the core functionality such as actions, items, 
rooms, and conditionals. Specifically, actions make full use of the 
custom actions interface, with action sequences taking parameters. 
RPG features are not present as they are very much works in progress.

### Notes on the WDL++ spec

A few notes, not clear from the documentation: while authoring this, 
I am assuming that the `can_enter` attribute of a room, while optional, 
will be a **known** key that chiventure understands as marking the 
player's ability to enter the room. If this attribute is present for
 a certain room, chiventure should ideally check its value 
(a boolean) whenever the player attempts to `GO` to this room.  
To go with `can_enter`, there is also the `text_no_entry` attribute,
which defines a text to display when `can_enter` is `false` yet the player
tries to enter the room. 

I think defining `can_enter` as an optional but parsed attribute, as 
opposed to incorporating conditionals into the room definitions 
themselves, is a reasonable addition to the spec. It will simplify 
the effort needed to define rooms that are never locked, as well 
as incorporate the process of unlocking/locking rooms into the 
attribute-getting and -setting pipeline available through 
custom action sequences.


### The game

The game itself starts in a central room, which connects to 4 other rooms 
colored red, green, blue, and purple in the four cardinal directions, 
and a locked secret room below the central room.

Across the four colored rooms, there are four colored levers. 
The player must pull only the purple and red levers to unlock the 
trapdoor and ability to enter the secret room. 
(The trapdoor doesn't actually do anything except
have something for the player to `LOOK` at. Entry to the secret room is solely defined by the `can_enter` attribute.)

The central room also has a lever, also only pullable when only the 
red and purple levers are pulled. However, this central room lever is a
distraction. If the player pulls this lever, they lose the game.
If, however, the player notices initial text (`two levers must be pulled to open a secret room`),
they will not pull the lever and instead go down to the secret room, where they 
will win the game.
