GAME:
 - start: "KITCHEN"
   intro: “Welcome to the virtual house. You have been wandering for quite some time,
   and you need to determine how to return to reality.”
   end:
    - in_room: "LIVING ROOM"

ROOMS:
- id: "kitchen"
  short_desc: "A well-furnished area for cooking food."
  long_desc: "The room is lit merrily, and a faint glow comes from the oven."
  connections:
    - to: "basement"
      direction: "down"
    - to: "bedroom"
      direction: "north"

ITEMS:
 - id: "CHAIR"
   short_desc: "This is a chair"
   long_desc: "This is a chair long"
   in: "KITCHEN"
   actions: 
    - action: "PUSH"
      text_success: "You push the chair"
      text_fail: "You cannot push this chair"
    - action: "PULL" 
      text_success: "You pull the chair"
      text_fail: "You cannot pull this chair"
    - action: "TAKE"
      text_success: "You take the chair"
      text_fail: "You cannot take this chair"