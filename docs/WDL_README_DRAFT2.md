# WDL FORMATTING RULES AND EXAMPLES
May 13, 2019

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
 - **start**: KITCHEN
 - **intro**: “Welcome to the virtual house. You have been wandering for quite some time,
   and you need to determine how to return to reality.”
 - **end**:
   - Inventory: wand

## ROOM:
##### The Room Object must contain the following attributes:
 - id: `<UNIQUE ID NAME>` which is an identification name that is unique to the room

   short_desc: `<STRING DESCRIPTION>` which is a string that is displayed when the player first enters the room

   long_desc: `<STRING DESCRIPTION>` which is a string that is displayed once player types “look at room” into the command line


   connections:
   (the	following attributes belong	to subcategory 'connections')
  - to: `<ROOM	ID>` which lists a valid place the player can reach in one action from this room by ID

    direction: `<CARDINAL DIRECTION>` which states the direction that connection is in. Only six directions are available for use in the game: north, east, south, west, up, down.

    through: `<OBJECT ID>` if applicable, the object that the player must go through to go in that direction

    ###### NOTE: a valid connection has to have an ID that exists


### ROOM example:
 - **id**: KITCHEN

   **short_desc**: "A well-furnished area for cooking food."

   **long_desc**: "The room is lit merrily, and a faint glow comes from the oven."

   **connections**:
    - to: BASEMENT

      direction: DOWN

      through: trapdoor

## ITEM:

- For ITEMs, the indentation format is the same as above, except for actions, the attributes are indented with two spaces, followed by a dash.
- This applies to the subcategories in action as well.
- The attributes within actions must be indented with a dash(-) as well.

##### The Item Object must contain the following attributes:
  - id: `<UNIQUE ID NAME>` which is a unique identifier for the item; one id can only used to identify one item in the entire ITEMS object. (i.e. only one door can have id “door”, the others would have to have “door1”, “door2”, etc. because there must be no repeat ids)

    short_desc: `<STRING DESCRIPTION>` which is a string that is displayed when the player picks up the item

    long_desc: `<STRING DESCRIPTION>` which is a string that is more specific than short_desc, displayed when the player types “look at (insert item name)” into the command line

    in: `<ROOM ID>` which is the id of the room that the item is in when the game starts

    state: `<ATTRIBUTE>` which is the attribute of the item (e.g. locked, closed, open) when the game starts

    actions: the possible actions that can be performed on the object; each action has the following attributes:
      - `<ACTION FROM BANK>`:
        - allowed: `<YES/NO>` which is a no attribute value to specify that this action can never succeed. (You may want this attribute in order to trigger the text_fail action to notify the player to try something else)

        - text_fail: `<STRING>` which is the string that is displayed when an action is not allowed

    - `<ACTION FROM BANK>`:
      - condition: `<ATTRIBUTE: YES/NO>` which is prerequisite states for the given action to be performed, written as “state_attribute : yes/no” (e.g. to specify that a door must be unlocked to open, write “locked: no” in conditions)

      - text_success: `<STRING>` which is a string that is displayed upon the success of an action

      - text_fail: `<STRING>` which is a string that is displayed upon the failure of an action
      - set: changes an attribute of the object’s state upon action (if the door had “locked” as a state attribute, you would change this by writing “locked: no” here to negate that condition)

          - item: `<ITEM ID>`
          - state: `<ATTRIBUTE>`
          - value: `<YES/NO>`

### ITEM examples:
 - **id**: door

   **short_desc**: "a wooden door."

   **long_desc**: "A very ancient and gnarled looking thing."

   **in**: KITCHEN

   **state**: locked: YES

   **actions**:
     - consumer
         - allowed: no
         - text_fail: "you cannot consume a door."
     - open
         - condition: locked: NO
         - text_success: "you open the door."
         - text_fail: "you fail to open the door, it is locked."
         - set:
             - item: door
             - state: locked
             - value: NO

- **id**: wand

  **short_desc**: "A wand"

  **long_desc**: "It has magical properties"

  **in**: BEDROOM

  **actions**:  
  - take
    - condition: in_inventory: top_hat
    - text_success: "You got the wand!"
    - text_fail: "You cannot take the wand until you have the top hat"
  - consume:
    - allowed: no
    - text_fail: "you cannot consume a wand."
