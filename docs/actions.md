# Documentation of Action Specifications

#### Definitions
**Conditions**: <br>
When an action is requested on an item or NPC, these conditions<br>
must be met in order for an action to be successful. When the action is successful<br>
there are potential effects that can occur. <br>

**Effects**:<br>
When an action is completed successful, there are multiple types of effects<br>
that can occur, depending on which action is committed on a certain item.<br>


## Kinds of Actions:
Kind 1: ACTION `<ITEM>` <br>
A **Kind 1** action is an action that makes the player do something to an item.<br>
Examples: EAT apple, OPEN door, PUSH box, etc.<br>

Kind 2: ACTION `<DIRECTION>`<br>
A **Kind 2** action is an action that makes the player walk in a certain direction, most likely into a new area/room.<br>
Examples: GO west, WALK east, GO left, etc.<br>

Kind 3: ACTION `<NPC>`<br>
A **Kind 3** action is an action that makes the player interact with an NPC in some way. This action does not include<br>
any physical interaction with the NPC.<br>
Examples: TALK TO NPC, LOOK AT NPC, etc.

Kind 4: ACTION `<ITEM> <NPC>` <br>
A **Kind 4** action is an action that makes the player interact with an item and an NPC.<br>
Examples: TAKE apple from NPC, GIVE apple to NPC, etc.<br>

Kind 5: ACTION `<ITEM> <ITEM>`<br>
A **Kind 5** action is an action that makes the player interact with two items. <br>
Examples: PUT apple on table, PUSH box on button, USE key on door, etc<br>


## Items and NPC's:

These are the general conditions and requirements for NPC's.

### `<ITEM>`
#### Conditions:
- Item must be accessible by player
- Item must be able to be affected by action
- Item must be in a state where action can be affective
- Item may need a certain attribute to be a certain value before action can be affective


#### Effects:
- Item may no longer accessible 
- Item may not be able to be affected by current action
- Item position may be changed 
- Other item states may be changed
- New rooms may be accessible or closed off
- Player state may be changed 
- Item may change another item's attribute value



### `<NPC>`
#### Conditions:
- NPC must be accessible
- NPC has the ability to be interacted with (possibly with specific item)

#### Effects:
- NPC may no longer be accessible/interactable
- NPC position may be changed
- Other item states may be changed
- Player state may be changed


## Actions:

These are specific conditions and effects that are affiliated with certain actions. This means that along with the general<br>
conditions and effects listed above, there are special conditions and effects tha can also be included with specific actions.<br>
If items have "No additional ..." listed, they follow the only follow the determined general conditions/requirements listed above, and <br>
have no excpetions.<br>

## WDL:
    - actions:
        - [name of action]:
            - conditions:
            - set:
                - object:
                  attribute:
                  value:
            - text_fail:
            - text_success: 

## Default:

The action's behavior when called on an `<ITEM>` or [NPC] that does not support the action.

K1 - Open `<ITEM>`
------
### Conditions:
- No additional conditions

### Effects:
- A new room may be available

### WDL:
        - open:

### Default:
"I can't open the `<ITEM>`"

K1 - Close `<ITEM>`
------
### Conditions:
- No additional requirements

### Effects:
- A room may no longer be available 

### WDL:
         - close:

### Default:
"I can't close the `<ITEM>`"


K1 - Push `<ITEM>`
------
### Conditions:
- Item must not be too heavy

### Effects:
- No additional effects

### WDL:
        - push:
            - conditions:
                - weight:

### Default:
"I push the `<ITEM>` to no effect"

K1 - Pull `<ITEM>`
------
### Conditions:
- Item must not be too heavy

### Effects:
- No additional effects

### WDL:
        - pull:
            - conditions:
                - weight:

### Default:
"I pull the `<ITEM>` to no effect"

K1 - Look at `<ITEM>` / Examine `<ITEM>`
------
### Conditions:
- No additional Conditions


### Effects:
- Long description of item will be printed

### WDL:
        - examine:

### Default:
"I examine the `<ITEM>` but find nothing of interest"

K1 - Turn on `<ITEM>`
--------------
### Conditions:
- No additional Conditions

### Effects:
- No additional effects

### WDL:
        - turn_on:

### Default:
"I am unable to turn on the `<ITEM>`"

K1 - Turn off `<ITEM>`
----------
### Conditions:
- No additional Conditions

### Effects:
- No additional effects

### WDL:
        - turn_off:

### Default:
"I am unable to turn off the `<ITEM>`"

K3 - Talk to [NPC]
---------
### Conditions:
- No additional requirements


### Effects:
- Dialogue from NPC will be printed

### WDL:
        - talk_to:

### Default:
"I talk to [NPC] but get no response"

K5 - Give `<ITEM>` to [NPC] 
------------
### Conditions:
- Item must be in inventory


### Effects:
- Remove Item from player inventory
- Dialogue from NPC may be printed

### WDL:
        - give_to:

### Default:
"It is clear [NPC] does not want my `<ITEM>`"

K2 - Go [direction]
---------
### Conditions:
- A direction must be given.


### Effects:
- Move player to room in direction
- Brief description of room will be printed

### WDL:
        - go:

### Default:
"I can't find a way to go [direction]"

K1 - Pick up / Take `<ITEM>`
--------------
### Conditions:
- Player must have inventory space for Item


### Effects:
- Take Item out of room (changes room description and state)
- Put Item in player inventory
- Decrease player inventory space

### WDL:
        - take:

### Default:
"I can't take the `<ITEM>`"

K1 - Drop `<ITEM>`
----------
### Conditions:
- Item must be in inventory

### Effects:
- Take Item out of player inventory
- Increase player inventory space
- Put Item in room (changes room description and state)

### WDL:
        - drop:

### Default:
"I drop the `<ITEM>`"

K1 - Use `<ITEM>`
---------
### Conditions:
- No additional Conditions


### Effects:
- No additional effects

### WDL:
        - use:

### Default:
"I can't figure out how to use the `<ITEM>`"

K5 - Use `<ITEM>` on `<ITEM>`
------------
### Conditions:
- No additional Conditions


### Effects:
- No additional effects

### WDL:
        - use_on:

### Default:
"I can't figure out how to use the `<ITEM>` on the `<ITEM>`"

K1 - Drink `<ITEM>` / Consume `<ITEM>`
---------
### Conditions:
- Item must be liquid

### Effects:
- No additional effects

### WDL:
        - drink:

### Default:
"I do not want to drink the `<ITEM>`"

K1 - Eat `<ITEM>` / Consume `<ITEM>`
---------
### Conditions:
- Item must be solid


### Effects:
- No additional effects

### WDL:
        - eat:

### Default:
"I do not want to eat the `<ITEM>`"