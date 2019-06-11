# WDL FORMATTING RULES AND EXAMPLES
June 2, 2019


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

##### - Possible Actions:
Please see this document for all possible actions and descriptions: https://github.com/uchicago-cs/chiventure/blob/actions/dev/docs/actions.md 

### Syntax:
- The order that the Objects in a WDL file are written in must follow the order of explanation in specification (See example)
- Short_desc are strings that can have at max 100 characters (including spaces)
- Long_desc are strings that can have at max 500 characters (including spaces)

- Each file object category(ROOM, ITEM, or GAME) must be followed by a colon (:)
- Attributes apply to categories and subcategories, and are followed immediately by a colon(:). The information in the attribute is preceded by a space.
- The first attribute in every category (and subcategory) must be indented with one space
- All other attributes are indented	with three spaces.

#### A WDL file is a YAML file that has at least the three file objects: Game, Room, Item.

## GAME:

##### The Game Object must contain the following attributes:
- start: `<ROOM IDENTIFIER>` used to specify the ID of the room that the game will start in. This value is the string ID of the room that the game will start in  
   ###### NOTE: The given ID must have been assigned to a room defined in the ROOM object (i.e. the room ID must exist, so if the start attribute has value “BEDROOM”, then there must be a room in the ROOM object that has the id “BEDROOM”).

  intro: `<STRING WITH MAX LENGTH 500 CHAR>` which is the introduction statement. A string description that is shown at the beginning of the game.

  end: `<CONDITION>` Only one way to end the game is supported. It specifies the room a player must be in to end the game.
   - in_room: `<ROOM ID>` Specifies the room one must enter to end the game.

### GAME example:
```yaml
 - start: "KITCHEN"
   intro: “Welcome to the virtual house. You have been wandering for quite some time,
   and you need to determine how to return to reality.”
   end:
    - in_room: "LIVING ROOM"
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

   ###### NOTE: a direction must be in all lower case.
   ###### NOTE: a valid connection has to have an ID that exists. 


### ROOM example:
```yaml
- id: "kitchen"

  short_desc: "A well-furnished area for cooking food."

  long_desc: "The room is lit merrily, and a faint glow comes from the oven."

  connections:

    - to: "basement"

      direction: "down"

    - to: "bedroom"

      direction: "north"
```

## ITEM:

- For ITEMs, the indentation format is the same as above, except for actions, the fields are indented with two spaces, followed by a dash.
- This applies to the subcategories in action as well.
- The fields within actions must be indented with a dash(-) as well.
- OPTIONAL fields must be specified for now, but they do not need a value.

##### The Item Object must contain the following attributes:
  - id: `<UNIQUE ID NAME>` which is a unique identifier for the item; one id can only used to identify one item in the entire ITEMS object. (i.e. only one door can have id “door”, the others would have to have “door1”, “door2”, etc. because there must be no repeat ids)

    short_desc: `<STRING DESCRIPTION>` which is a string that is displayed when the player picks up the item

    long_desc: `<STRING DESCRIPTION>` which is a string that is more specific than short_desc, displayed when the player types “look at (insert item name)” into the command line

    in: `<ROOM ID>` which is the id of the room that the item is in when the game starts

    actions: the possible actions that can be performed on the item; each action has the following fields:
      
    - action: `<ACTION FROM BANK>` in the form of a string in ALL UPPER CASE

      text_success: `<STRING>` which is a string that is displayed upon the success of an action (OPTIONAL)

      text_fail: `<STRING>` which is the string that is displayed when an action is not allowed (OPTIONAL)

### ITEM examples:
```yaml
- id: "handle"

  short_desc: "A lever."

  long_desc: "The iron lever is painted gold and rusting in the corner of the palace garden."

  in: "garden"
  
  actions:

    - action: "PUSH"
     
      text_success: "you push the lever"
      
      text_fail: "you can't push it again"

    - action: "PULL"

      text_fail: "you cannot pull it"

- id: "wand"

  short_desc: "A wand"

  long_desc: "It has magical properties"

  in: "bedroom"

  actions:
  
    - action: "TAKE"
     
      text_success: "You take the wand."

    - action: "CONSUME"
    
      text_fail: "You cant eat the wand"
```
