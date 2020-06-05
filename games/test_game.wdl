# This is a test game for chiventure!
# It contains 6 rooms - a central room, surrounded by 4 rooms on each cardinal side and one 
# "secret" room underneath.
# The game can currently only be won by going down from the central room, as the item
# interaction functionality does not exist yet.


GAME:
 - start: "white room" 
   intro: "Welcome to the Test Dungeon!"
   end:
    - in_room: "secret room" 
      through: "TRAPDOOR"  
ROOMS:
 - id: "white room"
   short_desc: "A white room."
   long_desc: "A pristine and plain white room with a lever in its center. A locked trapdoor rests in the floor next to a sign."
   connections:
    - to: "green room"
      direction: "NORTH"
    - to: "red room"
      direction: "SOUTH"
    - to: "blue room"
      direction: "EAST"
    - to: "purple room"
      direction: "WEST"
    - to: "secret room"
      direction: "DOWN"

 - id: "green room"
   short_desc: "A green room."
   long_desc: "A green room with a green lever in its center. A green sign sits on the wall."
   connections:
    - to: "white room"
      direction: "SOUTH"
    
   
 - id: "red room"
   short_desc: "A red room."
   long_desc: "A red room with a red lever in its center. A red sign sits on the wall."
   connections:
    - to: "white room"
      direction: "NORTH"
   
 - id: "blue room"
   short_desc: "A blue room."
   long_desc: "A blue room with a blue lever in its center. A blue sign sits on the wall."
   connections:
    - to: "white room"
      direction: "WEST"
  
 - id: "purple room"
   short_desc: "A purple room."
   long_desc: "A purple room with a purple lever in its center. A purple sign sits on the wall."
   connections:
    - to: "white room"
      direction: "EAST"
   
 - id: "secret room"
   short_desc: "An endless dark chamber."
   long_desc: "You can't see anything in the abyss."
   connections:
    - to: "white room"
      direction: "UP"
 
ITEMS:
 - id: "SIGN"
   short_desc: "A sign."
   long_desc: "The sign reads: 'To leave this place, two levers must be pulled..' (or, for now, just go down!)"
   in: "white room"
   actions:
     - action: "TAKE"
       text_success: "you weren't supposed to pick this up"
       text_fail: "you can't do that"

 - id: "BLUESIGN"
   short_desc: "A blue sign."
   long_desc: "The sign reads: 'Don't pull this lever.'"
   in: "blue room"
   actions:
     - action: "TAKE"
       text_success: "you weren't supposed to pick this up"
       text_fail: "you can't do that"

    
 - id: "GREENSIGN"
   short_desc: "A green sign."
   long_desc: "The sign reads: 'Don't pull this lever.'"
   in: "green room"
   actions:
     - action: "TAKE"
       text_success: "you weren't supposed to pick this up"
       text_fail: "you can't do that"

 - id: "PURPLESIGN"
   short_desc: "A purple sign."
   long_desc: "The sign reads: 'Pull this lever if you want to escape.'"
   in: "purple room"
   actions:
     - action: "TAKE"
       text_success: "you weren't supposed to pick this up"
       text_fail: "you can't do that"

 - id: "REDSIGN"
   short_desc: "A red sign."
   long_desc: "The sign reads: 'Pull this lever if you want to escape.'"
   in: "red room"
   actions:
     - action: "TAKE"
       text_success: "you weren't supposed to pick this up"
       text_fail: "you can't do that"

 - id: "LEVER"
   short_desc: "A lever."
   long_desc: "A plain-looking lever."
   in: "white room"
   actions:
     - action: "PULL"
       # - conditions:
       #     - blue_lever_pulled: no
       #     - green_lever_pulled: no
       #     - purple_lever_pulled: yes
       #     - red_lever_pulled: yes
       # - set:
       #     - object: "TRAPDOOR"
       #       attribute: locked
       #       value: no
       text_success: "You pull the lever, and the trapdoor lock clicks open."
       text_fail: "The lever is locked in place.."
     - action: "PUSH"
       text_success: "You should try pulling it instead."
       text_fail: "You should try pulling it instead."
  
  
 - id: "BLUELEVER"
   short_desc: "A blue lever."
   long_desc: "A plain-looking blue lever."
   in: "blue room"
   actions:
     - action: "PULL"
       # - conditions:
       #     - pulled: no
       # - set:
       #     - object: "LEVER"
       #       attribute: blue_lever_pulled
       #       value: yes
       #     - object: "BLUELEVER"
       #       attribute: pulled
       #       value: yes
       #     - object: "BLUELEVER"
       #       attribute: pushed
       #       value: no
       text_success: "You pull the lever."
       text_fail: "You have already pulled the lever."
     - action: "PUSH"
       # - conditions:
       #     - pushed: no
       # - set:
       #     - object: "LEVER"
       #       attribute: blue_lever_pulled
       #       value: no
       #     - object: "BLUELEVER"
       #       attribute: pushed
       #       value: yes
       #     - object: "BLUELEVER"
       #       attribute: pulled
       #       value: no
       text_success: "You push the lever back to its original position."
       text_fail: "You have already pushed the lever."
 - id: "GREENLEVER"
   short_desc: "A green lever."
   long_desc: "A plain-looking green lever."
   in: "green room"
   actions:
     - action: "PULL"
       # - conditions:
       #     - pulled: no
       # - set:
       #     - object: "LEVER"
       #       attribute: green_lever_pulled
       #       value: yes
       #     - object: "GREENLEVER"
       #       attribute: pulled
       #       value: yes
       #     - object: "GREENLEVER"
       #       attribute: pushed
       #       value: no
       text_success: "You pull the lever."
       text_fail: "You have already pulled the lever."
     - action: "PUSH"
       # - conditions:
       #     - pushed: no
       # - set:
       #     - object: "LEVER"
       #       attribute: green_lever_pulled
       #       value: no
       #     - object: "GREENLEVER"
       #       attribute: pushed
       #       value: yes
       #     - object: "GREENLEVER"
       #       attribute: pulled
       #       value: no
       text_success: "You push the lever back to its original position."
       text_fail: "You have already pushed the lever."
  
 - id: "PURPLELEVER"
   short_desc: "A purple lever."
   long_desc: "A plain-looking purple lever."
   in: "purple room"
   actions:
     - action: "PULL"
         # - conditions:
         #     - pulled: no
         # - set:
         #     - object: "LEVER"
         #       attribute: purple_lever_pulled
         #       value: yes
         #     - object: "PURPLELEVER"
         #       attribute: pulled
         #       value: yes
         #     - object: "PURPLELEVER"
         #       attribute: pushed
         #       value: no
       text_success: "You pull the lever."
       text_fail: "You have already pulled the lever."
     - action: "PUSH"
         # - conditions:
         #     - pushed: no
         # - set:
         #     - object: "LEVER"
         #       attribute: purple_lever_pulled
         #       value: no
         #     - object: "PURPLELEVER"
         #       attribute: pushed
         #       value: yes
         #     - object: "PURPLELEVER"
         #       attribute: pulled
         #       value: no
       text_success: "You push the lever back to its original position."
       text_fail: "You have already pushed the lever."
  
 - id: "REDLEVER"
   short_desc: "A red lever."
   long_desc: "A plain-looking red lever."
   in: "red room"
   actions:
     - action: "PULL"
         # - conditions:
         #     - pulled: no
         # - set:
         #     - object: "LEVER"
         #       attribute: red_lever_pulled
         #       value: yes
         #     - object: "REDLEVER"
         #       attribute: pulled
         #       value: yes
         #     - object: "REDLEVER"
         #       attribute: pushed
         #       value: no
       text_success: "You pull the lever."
       text_fail: "You have already pulled the lever."
     - action: "PUSH"
         # - conditions:
         #     - pushed: no
         # - set:
         #     - object: "LEVER"
         #       attribute: red_lever_pulled
         #       value: no
         #     - object: "REDLEVER"
         #       attribute: pushed
         #       value: yes
         #     - object: "REDLEVER"
         #       attribute: pulled
         #       value: no
       text_success: "You push the lever back to its original position."
       text_fail: "You have already pushed the lever."
  
 - id: "TRAPDOOR"
   short_desc: "A trapdoor."
   long_desc: "A strangely rustic and dusty trapdoor."
   in: "white room"
   actions:
     - action: "GO"
         # - conditions:
         #     - locked: no
       text_success: "You descend down the trapdoor.."
       text_fail: "The trapdoor is locked."
    
##note- update wdl.md to reflect updated language features/investigate discrepancies.
