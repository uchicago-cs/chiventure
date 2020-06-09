# Test game for chiventure - meant to be used with spring2020-demo,
# which takes this game and adds attribute conditions, inventory conditions,
# end conditions, and conditional connections between rooms,
# all of which are currently not yet supported by WDL


GAME:
 - start: "dining room" 
   intro: "Welcome home! You just got back from a long day of work at Company X. You're exhausted, and think that it'd be best to just eat some dinner and go to bed. You're currently in your dining room, and dinner is on the table."
   end:
    - in_room: "bedroom" 
    # end condition: dinner eaten


ROOMS:
 - id: "living room"
   short_desc: "A living room."
   long_desc: "The room is sensibly decorated."
   connections:
    - to: "dining room"
      direction: "NORTH"
    - to: "bedroom"
      direction: "EAST"
      # condition: door is open
    - to: "bathroom"
      direction: "WEST"

 - id: "kitchen"
   short_desc: "A kitchen."
   long_desc: "You see various eating utensils scattered everywhere."
   connections:
    - to: "dining room"
      direction: "WEST"

 - id: "dining room"
   short_desc: "A dining room."
   long_desc: "You see dinner on the table."
   connections:
    - to: "living room"
      direction: "SOUTH"
    - to: "kitchen"
      direction: "EAST"

 - id: "bedroom"
   short_desc: "A bedroom."
   long_desc: "Your bed looks quite exhausting to someone as tired as you."
   connections:
    - to: "living room"
      direction: "WEST"

 - id: "bathroom"
   short_desc: "A bathroom."
   long_desc: "A nice bathroom."
   connections:
    - to: "living room"
      direction: "EAST"


ITEMS:
 - id: "DOOR"
   short_desc: "A door."
   long_desc: "This door leads to your bedroom."
   in: "living room"
   actions:
     - action: "OPEN"
       text_success: "You open the door."
       text_fail: "You can't open the door."

 - id: "SPAGHETTI"
   short_desc: "A plate of spaghetti." 
   long_desc: "A plate of spaghetti with meatballs. It still looks nice and warm."
   in: "dining room"
   actions:
     - action: "CONSUME"
       text_success: "You eat the spaghetti. You feel quite satisfied."
       text_fail: "You cannot eat the spaghetti."
       # inventory condition: fork is in inventory

 - id: "BREAD"
   short_desc: "A piece of garlic bread."
   long_desc: "A piece of garlic bread. The perfect compliment to spaghetti with meatballs."
   in: "dining room"
   actions:
     - action: "CONSUME"
       text_success: "You eat the bread. You feel quite satisfied."
       text_fail: "You cannot eat the bread."

 - id: "SALAD"
   short_desc: "A side salad."
   long_desc: "A side salad. Nothing remarkably special about it."
   in: "dining room"
   actions:
     - action: "CONSUME"
       text_success: "You eat the salad. You feel quite satisfied."
       text_fail: "You cannot eat the salad."
       # inventory condition: fork is in inventory

 - id: "WATER"
   short_desc: "A glass of water."
   long_desc: "A glass of water. There's a few ice cubes floating around inside."
   in: "dining room"
   actions:
     - action: "CONSUME"
       text_success: "You drink the water. You feel quite satisfied."
       text_fail: "You cannot drink the water."
      
 - id: "FORK"
   short_desc: "A fork."
   long_desc: "A fork. There's nothing remarkably special about it."
   in: "kitchen"
   actions:
     - action: "TAKE"
       text_success: "You take a fork."
       text_fail: "You can't take a fork."

 - id: "FORK"
   short_desc: "A fork."
   long_desc: "A fork. There's nothing remarkably special about it."
   in: "kitchen"
   actions:
     - action: "TAKE"
       text_success: "You take a fork."
       text_fail: "You can't take a fork."