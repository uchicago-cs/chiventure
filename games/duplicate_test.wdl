# Test game for chiventure - meant to be used with spring2020-demo,
# which takes this game and dump some more things in it that are
# currently not specified by WDL


GAME:
 - start: "kitchen" 
   intro: "You are currently in a kitchen with an insane amount of forks. Perhaps you can try to perform various actions just to see what happens?"
   end:
    - in_room: "dining room" 


ROOMS:
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
    - to: "kitchen"
      direction: "EAST"


ITEMS:
 - id: "FORK"
   short_desc: "A fork."
   long_desc: "A fork. There's nothing remarkably special about it."
   in: "kitchen"
   actions:
     - action: "TAKE"
       text_success: "You take the fork."
       text_fail: "You can't take the fork."

 - id: "FORK"
   short_desc: "A fork."
   long_desc: "A fork. There's nothing remarkably special about it."
   in: "kitchen"
   actions:
     - action: "TAKE"
       text_success: "You take the fork."
       text_fail: "You can't take the fork."

 - id: "FORK"
   short_desc: "A fork."
   long_desc: "A fork. There's nothing remarkably special about it."
   in: "kitchen"
   actions:
     - action: "OPEN"
       text_success: "You open the fork."
       text_fail: "You can't open the fork."

 - id: "FORK"
   short_desc: "A fork."
   long_desc: "A fork. There's nothing remarkably special about it."
   in: "kitchen"
   actions:
     - action: "CLOSE"
       text_success: "You close the fork."
       text_fail: "You can't close the fork."

 - id: "FORK"
   short_desc: "A fork."
   long_desc: "A fork. There's nothing remarkably special about it."
   in: "kitchen"
   actions:
     - action: "DROP"
       text_success: "You drop the fork."
       text_fail: "You can't drop the fork."

 - id: "FORK"
   short_desc: "A fork."
   long_desc: "A fork. There's nothing remarkably special about it."
   in: "kitchen"
   actions:
     - action: "PUSH"
       text_success: "You push the fork."
       text_fail: "You can't push the fork."

 - id: "FORK"
   short_desc: "A fork."
   long_desc: "A fork. There's nothing remarkably special about it."
   in: "kitchen"
   actions:
     - action: "PULL"
       text_success: "You pull the fork."
       text_fail: "You can't pull the fork."

 - id: "FORK"
   short_desc: "A fork."
   long_desc: "A fork. There's nothing remarkably special about it."
   in: "kitchen"
   actions:
     - action: "CONSUME"
       text_success: "You consume the fork."
       text_fail: "You can't cpnsume the fork."

 - id: "FORK"
   short_desc: "A fork."
   long_desc: "A fork. There's nothing remarkably special about it."
   in: "kitchen"
   actions:
     - action: "TURNON"
       text_success: "You turn on the fork."
       text_fail: "You can't turn on the fork."
     - action: "TAKE"
       text_success: "You take the fork."
       text_fail: "You can't take the fork."

 - id: "FORK"
   short_desc: "A fork."
   long_desc: "A fork. There's nothing remarkably special about it."
   in: "kitchen"
   actions:
     - action: "TURNOFF"
       text_success: "You turn off the fork."
       text_fail: "You can't turn off the fork."
     - action: "TAKE"
       text_success: "You take the fork."
       text_fail: "You can't take the fork."

 - id: "TABLE"
   short_desc: "A table."
   long_desc: "A table. There's nothing remarkably special about it."
   in: "kitchen"
   actions:
     - action: "PUSH"
       text_success: "You push the table."
       text_fail: "You can't push the table."
