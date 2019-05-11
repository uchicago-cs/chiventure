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
- NPC has the ability to be interacted with (possibly with specific item)

#### Effects:
- NPC may no longer be accessible/interactable
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


Give [Item] on [NPC] 
------------
Kind 5 Action<br>
### Requirements:
- Item must be in inventory


### Effects:
- Remove Item from player inventory
- New information may be given to the player


Go [direction]
#### Kind 2 Action
---------
### Requirements:
- Room must be in direction and not blocked




### Effects:
- Move player to room in direction
- Print brief description of room




Pick up / Take [Item]
#### Kind 1 Action
--------------


### Requirements:

- Player must have inventory space for Item


### Effects:
- Take Item out of room (changes room description and state)
- Put Item in player inventory
- Decrease player inventory space


Drop [Item]
#### Kind 1 Action
----------
### Requirements:
- Item must be in inventory

### Effects:
- Take Item out of player inventory
- Increase player inventory space
- Put Item in room (changes room description and state)


Use [Item]
#### Kind 1 Action
---------
### Requirements:
- No additional requirements



### Effects:
- No additional effects


Use [Item] on [Item]
#### Kind 5 Action
------------
### Requirements:
- No additional requirements


### Effects:
- No additional effects


Drink [Item] / Consume [Item]
#### Kind 1 Action
---------
### Requirements:

- Item must be liquid




### Effects:
- No additional effects


Eat [Item] / Consume [Item]
#### Kind 1 Action
---------
### Requirements:

- Item must be solid


### Effects:
- No additional effects
