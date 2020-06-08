# Documentation of Action Specifications

### Definitions

**Conditions**:

When an action is requested on an item, these conditions must be met in

order for an action to be successful. When the action is successful there

are potential effects that can occur. 


**Effects**:

When an action is completed successful, there are multiple types of effects

that can occur, depending on which action is committed on a certain item.


## Kinds of Actions:
Kind 1: ACTION `<ITEM>`

A **Kind 1** action is an action that makes the player do something to an item.

Examples: eat apple, open door, push box, etc.


Kind 2: ACTION `<DIRECTION>`

A **Kind 2** action is an action that makes the player walk in a certain direction, most likely into a new area/room.

Examples: go west, go left, etc.


Kind 3: ACTION `<ITEM>` `<ITEM>`

A **Kind 3** action is an action that makes the player interact with two items.

Examples: put apple on table, push box on button, use key on door, etc



## Items:

These are the general conditions and requirements for items.

### `<ITEM>`
#### Conditions:
- Item must be in the same room as the player
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

## Actions:

These are specific conditions and effects that are affiliated with certain actions. This means that along with the general

conditions and effects listed above, there are special conditions and effects that can also be included with specific actions.

If items have "No additional ..." listed, they only follow the determined general conditions/requirements listed above, and

have no exceptions.


## WDL:
```
    - actions:
        - [name of action]:
            - conditions:
            - set:
                - object:
                  attribute:
                  value:
            - text_fail:
            - text_success: 
```

## Default:

The action's behavior when called on an `<ITEM>` that does not support the action.

K1 - Open `<ITEM>`
------
### Conditions:
- No additional conditions

### Effects:
- A new room may be available

### WDL:
```
        - open:
```

### Default:
"I can't open the `<ITEM>`"

K1 - Close `<ITEM>`
------
### Conditions:
- No additional requirements

### Effects:
- A room may no longer be available 

### WDL:
```
         - close:
```

### Default:
"I can't close the `<ITEM>`"


K1 - Push `<ITEM>`
------
### Conditions:
- Item must not be too heavy

### Effects:
- No additional effects

### WDL:
```
        - push:
            - conditions:
                - weight:
```

### Default:
"I push the `<ITEM>` to no effect"

K1 - Pull `<ITEM>`
------
### Conditions:
- Item must not be too heavy

### Effects:
- No additional effects

### WDL:
```
        - pull:
            - conditions:
                - weight:
```

### Default:
"I pull the `<ITEM>` to no effect"


### Default:
"I examine the `<ITEM>` but find nothing of interest"

K1 - Turn on `<ITEM>`
--------------
### Conditions:
- No additional Conditions

### Effects:
- No additional effects

### WDL:
```
        - turn_on:
```

### Default:
"I am unable to turn on the `<ITEM>`"

K1 - Turn off `<ITEM>`
----------
### Conditions:
- No additional Conditions

### Effects:
- No additional effects

### WDL:
```
        - turn_off:
```

### Default:
"I am unable to turn off the `<ITEM>`"


K2 - Go [direction]
---------
### Conditions:
- A direction must be given.


### Effects:
- Move player to room in direction
- Brief description of room will be printed

### WDL:
```
        - go:
```

### Default:
"I can't find a way to go [direction]"

### Synonyms:
Walk

K1 - Take `<ITEM>`
--------------
### Conditions:
- Player must have inventory space for Item


### Effects:
- Take Item out of room (changes room description and state)
- Put Item in player inventory
- Decrease player inventory space

### WDL:
```
        - take:
```

### Default:
"I can't take the `<ITEM>`"

### Synonyms:
Pickup

K1 - Pick up `<ITEM>`
--------------
### Conditions:
- Player must have inventory space for Item


### Effects:
- Take Item out of room (changes room description and state)
- Put Item in player inventory
- Decrease player inventory space

### WDL:
```
        - pick_up:
```

### Default:
"I can't pick up the `<ITEM>`"

K1 - Drop `<ITEM>`
----------
### Conditions:
- Item must be in inventory

### Effects:
- Take Item out of player inventory
- Increase player inventory space
- Put Item in room (changes room description and state)

### WDL:
```
        - drop:
```

### Default:
"I drop the `<ITEM>`"

K1 - Use `<ITEM>`
---------
### Conditions:
- No additional Conditions


### Effects:
- No additional effects

### WDL:
```
        - use:
```

### Default:
"I can't figure out how to use the `<ITEM>`"

### Synonyms:
Consume, Eat, Drink

K1 - Drink `<ITEM>`
---------
### Conditions:
- Item must be liquid

### Effects:
- No additional effects

### WDL:
```
        - drink:
```

### Default:
"I do not want to drink the `<ITEM>`"

K1 - Eat `<ITEM>`
---------
### Conditions:
- Item must be solid


### Effects:
- No additional effects

### WDL:
```
        - eat:
```

### Default:
"I do not want to eat the `<ITEM>`"

K1 - Consume `<ITEM>`
---------
### Conditions:
- Item must be solid


### Effects:
- No additional effects

### WDL:
```
        - consume:
```

### Default:
"I do not want to consume the `<ITEM>`"

K3 - Use `<ITEM>` on `<ITEM>`
------------
### Conditions:
- No additional Conditions


### Effects:
- No additional effects

### WDL:
```
        - use_on:
```

### Default:
"I can't figure out how to use the `<ITEM>` on the `<ITEM>`"
