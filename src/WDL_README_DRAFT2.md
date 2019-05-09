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
