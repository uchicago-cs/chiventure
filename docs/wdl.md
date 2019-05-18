# WDL FORMATTING RULES AND EXAMPLES
May 17, 2019

### Definitions:
##### - Component:
Something that is part of the physical environment in a game (a single room, a single object, a single non-player character, etc.)

##### - Object:
A classification category for the components in a game

##### - Attribute: 
A trait that describes or serves to further define a component

##### - Attribute name:
The name of an attribute

##### - Specification:
This document

### Syntax:
- The order that the Objects in a WDL file are written in must follow the order of explanation in specification (See example)
- Must have one space, followed by “-” then followed by one space before an attribute name
- Short_desc are strings that can have at max 100 characters (including spaces)
- Long_desc are strings that can have at max 500 characters (including spaces)

- Each file object category(ROOM, ITEM, or GAME) must be followed by a colon (:)
- Attributes apply to categories and subcategories, and are followed immediately by a colon(:). The information in the attribute is preceded by a space.
- The first attribute in every category (and subcategory) must be indented with one
space, followed by a dash(-), followed by another space, then the attribute.
- All other attributes are indented	with three spaces.

#### A WDL file is a YAML file that has at least the three file objects: Game, Room, Objects.

### Refer to Action Management's file: src/action_management/include/actionmanagement.h on the actions/dev branch for a list of approved actions in a game

## GAME:

##### The Game Object must contain the following attributes:
- start: `<ROOM IDENTIFIER>` used to specify the ID of the room that the game will start in. This value is the string ID of the room that the game will start in  
   ###### NOTE: The given ID must have been assigned to a room defined in the ROOM object (i.e. the room ID must exist, so if the start attribute has value “BEDROOM”, then there must be a room in the ROOM object that has the id “BEDROOM”).

- intro: `<STRING WITH MAX LENGTH 500 CHAR>` which is the introduction statement. A string description that is shown at the beginning of the game.
- end: `<CONDITION>` a condition specification for how the game ends. This must be one of two ways:
   1. The inventory contains a specific item
    - Ex. inventory contains: emerald gem

   2. The number of points that the player has accumulated
    - Ex. num_points = 100

### GAME example:
```yaml
 - start: "KITCHEN"
 - intro: “Welcome to the virtual house. You have been wandering for quite some time,
   and you need to determine how to return to reality.”
 - end:
   - Inventory: "wand"
```

## ROOM:
- Proper indentation and syntax is shown below. Be sure to use colons, tabs, and tick marks as defined below for valid inputs. 

##### The Room Object must contain the following attributes:
- id: `<UNIQUE ID NAME>` which is an identification name that is unique to the room

  short_desc: `<STRING DESCRIPTION>` which is a string that is displayed when the player first enters the room

  long_desc: `<STRING DESCRIPTION>` which is a string that is displayed once player types “look at room” into the command line

  connections: (the following attributes belong to subcategory 'connections')

    - to: `<ROOM  ID>` which lists a valid place the player can reach in one action from this room by ID

      direction: `<CARDINAL DIRECTION>` which states the direction that connection is in. Only six directions are available for use in the game: north, east, south, west, up, down. 

      through: `<ITEM ID>` if applicable, the object that the player must go through to go in that direction

      conditions:

      - id: `<STRING_ITEM>` which is an identification name that is unique to the item

        state: `<STRING_ADJ>` which is the descriptor for the state of the item

        value: `<VAL>` which is the value of the state of the item upon initializaition of the game

    ###### NOTE: a valid connection has to have an ID that exists. 


### ROOM example:
```yaml
ROOM Example:
- id: "kitchen"

  short_desc: "A well-furnished area for cooking food."

  long_desc: "The room is lit merrily, and a faint glow comes from the oven."

  connections:

    - to: "basement"

      direction: "down"

      through: "trapdoor"

      conditions:

      - id: "spoon"

        state: "clean"

        value: "no"

      - id: "apple"

        state: "sliced"

        value: "no"

    - to: "bedroom"

      direction: "north"

      through: "portal"

      conditions:

      - id: "water bottle"

        state: "full"

        value: "no"

      - id: "candy"

        state: "in inventory"

        value: "yes"
```

## ITEM:

- For ITEMs, the indentation format is the same as above, except for actions, the attributes are indented with two spaces, followed by a dash.
- This applies to the subcategories in action as well.
- The attributes within actions must be indented with a dash(-) as well.

##### The Item Object must contain the following attributes:
  - id: `<UNIQUE ID NAME>` which is a unique identifier for the item; one id can only used to identify one item in the entire ITEMS object. (i.e. only one door can have id “door”, the others would have to have “door1”, “door2”, etc. because there must be no repeat ids)

    short_desc: `<STRING DESCRIPTION>` which is a string that is displayed when the player picks up the item

    long_desc: `<STRING DESCRIPTION>` which is a string that is more specific than short_desc, displayed when the player types “look at (insert item name)” into the command line

    in: `<ROOM ID>` which is the id of the room that the item is in when the game starts

    state: `<STRING_ADJ>` which is the descriptor for the state of the item
    
    value: `<VAL>` which is the value of the state of the item upon initializaition of the game

    actions: the possible actions that can be performed on the object; each action has the following attributes:
      
    - action: `<ACTION FROM BANK>`:
        
      allowed: `<NO>` which is a no attribute value to specify that this action can never succeed. (You may want this attribute in order to trigger the text_fail action to notify the player to try something else) By default, actions are allowed, so this field 
      is not necessary if the game designer would like the action to be allowed. (OPTIONAL)

      text_success: `<STRING>` which is a string that is displayed upon the success of an action (OPTIONAL)

      text_fail: `<STRING>` which is the string that is displayed when an action is not allowed

      conditions: (OPTIONAL)

      - id: `<STRING_ITEM>` which is an identification name that is unique to the conditional item

        state: `<STRING_ADJ>` which is the descriptor for the state of the conditional item

        value: `<VAL>` which is the value of the state of the conditional item in order for the action to be completed

      set: changes an attribute of the object’s state upon action (if the door had “locked” as a state attribute, you would change this by writing “locked: no” here to negate that condition) (OPTIONAL)

      - id: `<ITEM ID>`
        
        state: `<ATTRIBUTE>`
         
        val: `<VAL>` which is the value of the state of the item upon completion of the action

### ITEM examples:
```yaml
- id: "handle"

  short_desc: "A lever."

  long_desc: "The iron lever is painted gold and rusting in the corner of the palace garden."

  in: "garden"

  state: "pulled"

  value: "no"

  actions:

    - action: "push"

      allowed: "no"

      text_fail: "You cannot push the lever. You can only pull it."

    - action: "pull"

      text_success: "Congrats! You can now access the underground tunnel. Go find it!"

      text_fail: "You cannot pull the lever. You must be holding the star in order to pull the lever."

      conditions:
      
      - id: "star"

        state: "in inventory"

        value: "no"

      set:

      - id: "lever"

      	state: "pulled"

      	value: "yes"

- id: "wand"

  short_desc: "A wand"

  long_desc: "It has magical properties"

  in: "bedroom"

  actions:
    - action: "take"

      text_success: "Congrats! You got the wand and can perform a spell!"

      text_fail: "You cannot take the wand until you have the top hat"

      conditions:
      
      - id: "top hat"

        state: "in inventory"

        value: "no"

    - action: "consumer"
	
      allowed: "no"

      text_fail: "You cannot consume the wand."
```
