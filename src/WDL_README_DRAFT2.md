The Game Object must contain the following fields:
 - start: <ROOM IDENTIFIER> used to specify the ID of the room that the game will start in.   
   The given ID must have been assigned to a room defined below in the ROOM 
   object (i.e. the room ID must exist, so if the start field has value 
   “BEDROOM”, then there must be a room in the ROOM object that has the id “BEDROOM”).
    - ex. A, BEDROOM, etc
 - intro: <STATEMENT WITH MAX LENGTH 500 CHAR> Introduction statement. A string description that is shown at the 
   beginning of the game.
 - end: <CONDITION> a condition specification for how the game ends. This must be one of two ways:
   1. The inventory contains a specific item
   - Ex. inventory contains: emerald gem
   2. The number of points that the player has accumulated
   - Ex. num_points = 100


EXAMPLE GAME:
 - start: KITCHEN
 - intro: “Welcome to the virtual house. You have been wandering for quite some time, 
   and you need to determine how to return to reality.”
 - end:
   - Inventory: red ruby

ROOM file object:

- Each FILE OBJECT CATEGORY(ROOM,ITEM,or GAME) must be followed by a colon (:)
- Fields apply to categories and subcategories, and are followed immediately bya colon(:). The information in the field is preceded by a space.
- The first field in every category (and subcategory) must be indented with one
space, followed by a dash(-), followed by another space, then the field.

- All other fields are indented	with three spaces.

Format_ROOM:

<FILE OBJECT CATEGORY>
(the following fields belong to the above category)
 - id: <UNIQUE ID NAME>
   short_desc: <STRING DESCRIPTION>
   long_desc: <STRING DESCRIPTION>
   connections:
   (the	following fields belong	to subcategory 'connections')
    - to: <ROOM	  ID>
      direction: <CARDINAL DIRECTION>
      through: <OBJECT ID>

ROOMS:
 - id: KITCHEN
   short_desc: "A well-furnished area for cooking food."
   long_desc: "The room is lit merrily, and a faint glow comes from the oven."
   connections:
    - to: BASEMENT
      direction: DOWN
      through: trapdoor

Format_ITEM:

<FILE OBJECT CATEGORY>
(the      following fields belong    to the above category)
  - id: <UNIQUE ID NAME>
    short_desc: <STRING DESCRIPTION>
    long_desc: <STRING DESCRIPTION>
    in: <ROOM ID>
    state: <ATTRIBUTE>
    actions:
      - <ACTION FROM BANK>:
          - allowed: <YES/NO>
          - text_fail: <STRING>
      - <ACTION FROM BANK>
           - condition: <ATTRIBUTE: YES/NO>
           - text_success: <STRING>
           - text_fail: <STRING>
           - set:
               - item: <ITEM ID>
               - state: <ATTRIBUTE>
               - value: <YES/NO>

ITEMS:
 - id: door
   short_desc: "a wooden door."
   long_desc: "A very ancient and gnarled looking thing."
   in: KITCHEN
   state: locked: YES
   actions:
     - eat
         - allowed: no
         - text_fail: "you cannot eat a door."
     - open
         - condition: locked: NO
         - text_success: "you open the door."
         - text_fail: "you fail to open the door, it is locked."
         - set:
             - item: door
             - state: locked
             - value: NO
Example ITEM:
 - id: wand
   short_desc: "A wand"
   long_desc: "It has magical properties"
   in: BEDROOM
   take: conditional
   take_conditions:
    - in_inventory: top_hat
   take_success: "You got the wand!"
   take_fail: "You cannot take the wand until you have the top hat"
   consume: no								    
