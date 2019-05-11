# Documentation of Action Specifications

## Kinds of Actions:
Kind 1: ACTION `<ITEM>` <br>
Kind 2: ACTION `<DIRECTION>`<br>
Kind 3: ACTION `<NPC>`<br>
Kind 4: ACTION `<ITEM> <NPC>` <br>
Kind 5: ACTION `<ITEM> <ITEM>`<br>


## Items and NPC's:
### `<ITEM>`
#### Requirements:
- Item must be accessible by player
- Item must be able to be affected by action
- Item must be in a state where action can be affective

#### Effects:
- Item may no longer accessible 
- Item may not be able to be affected by current action
- Item position may be changed 
- Other item states may be changed
- New rooms may be accessible or closed off
- Player state may be changed 



### `<NPC>`
#### Requirements:
- NPC must be accessible
- NPC has the ability to be interacted with

#### Effects:
- NPC may no longer be accessible
- NPC position may be changed
- Other item states may be changed
- Player state may be changed


## Actions:

Open [Item] (Kind 1)
------
### Requirements:
- Item must be unlocked
- Item must not be blocked

### Effects:
- A new room may be available 
- New item may be accessible


Close [Item]
------
### Requirements:
- Item must be open
- Item must not be blocked

### Effects:
- A room may no longer be available 


Push [Item]
------
### Requirements:
- Item must not have anything blocking it from being pushed
- Item must not be too heavy

### Effects:
- New items may be accessible



Pull [Item]
------
### Requirements:
- Item must not be too heavy
- Item must not be blocked

### Effects:
- New rooms or items may be unlocked


Look at [Item] / Examine [Item]
------
### Requirements:
- No additional requirements


### Effects:
- New information may be given to the player
- Description of item will be printed


Turn on [Item]
--------------
### Requirements:
- No additional requirements

### Effects:
- No additional effects


Turn off [Item]
----------
### Requirements:
- No additional requirements


### Effects:
- No additional effects


Talk to [NPC]
---------
### Requirements:
- Nothing may be blocking the NPC


### Effects:
- New information may be given to the player


Give [Item1] on [Item2]
------------
### Requirements:
Item1 must be in inventory<br>
Item2 must be an NPC (has own inventory?)<br>
Item2 must be reachable<br>
Item2 must have Item1 in wantItems [list of Item names](?)<br> 


### Effects:
Remove Item1 from player inventory<br>
Put Item1 in Item2 inventory(?)<br>
Remove Item1 from Item2 wantItem list(?)<br>
Item dependent effect on state<br>
Print NPC message<br><br>


Go [direction]
---------
### Requirements:
Reachable room must be in direction<br>




### Effects:
Move player to room in direction<br>
Print brief description of room<br>
Entering room has effect on state(?)<br><br>




Pick up / Take [Item]
--------------


### Requirements:

Item must be takeable<br>
Player must have inventory space for Item (if implemented)


### Effects:
Take Item out of room (changes room description and state)<br>
Put Item in player inventory<br>
Decrease player inventory space(?)<br>
Item is now always reachable to player unless dropped<br><br>


Drop [Item]
----------
### Requirements:
Item must be in inventory<br>
Item must be droppable(if implemented)<br>


### Effects:
Take Item out of player inventory<br>
Increase player inventory space(?)<br>
Put Item in room(changes room description and state)<br><br>


Use [Item]
---------
### Requirements:
Item must be usable<br>



### Effects:
Item dependent effect on state<br>
Print effect of Item use<br>
Item may no longer be usable and/or in inventory or room (changes to Item state)<br><br>


Use [Item1] on [Item2]
------------
### Requirements:

Item2 must be in Item interations [list of Item names] of Item1(if implemented)<br>


### Effects:
Item dependent effect on state<br>
Print effect of use<br>
Items may no longer be usable and/or in inventory or room (changes to Items’ state)<br>


Drink [Item] / Consume [Item]
---------
### Requirements:

Item must be liquid<br>




### Effects:
Item dependent effect on state<br>
Changes to Item state (may no longer be consumable)<br>
May change player state<br>


Eat [Item] / Consume [Item]
---------
### Requirements:

Item must be solid<br>


### Effects:
Item dependent effect on state<br>
Changes to Item state (may no longer be consumable)<br>
May change player state<br>