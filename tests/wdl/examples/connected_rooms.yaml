#
# Sample proof-of-concept yaml file
#

GAME:
 - start: "room A"
   intro: "This is the intro"
   end:
     - in_room: "room C"

ROOMS:
 - id: "room A"
   short_desc: "This is room A"
   long_desc: "This is room A long"
   connections:
    - to: "room B"
      direction: "NORTH"

 - id: "room B"
   short_desc: "This is room B"
   long_desc: "This is room B long"
   connections:
    - to: "room C"
      direction: "NORTH"

 - id: "room C"
   short_desc: "This is room C"
   long_desc: "This is room C long"
   connections:
    - to: "room A"
      direction: "NORTH"

ITEMS:
 - id: "CHAIR"
   short_desc: "This is a chair"
   long_desc: "This is a chair long"
   in: "room A"
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
   state: "still"
   value: "no"

 - id: "TABLE"
   short_desc: "This is a table"
   long_desc: "This is a table long"
   in: "room B"
   actions: 
    - action: "PUSH"
      text_success: "You push the table"
      text_fail: "You cannot push this table"
    - action: "PULL" 
      text_success: "You pull the table"
      text_fail: "You cannot pull this table"
    - action: "TAKE"
      text_success: "You take the table"
      text_fail: "You cannot take this table"
   state: "solid"
   value: "no"

 - id: "CANDLE"
   short_desc: "This is a candle"
   long_desc: "This is a candle long"
   in: "room C"
   actions: 
    - action: "TAKE"
      text_success: "You take the candle"
      text_fail: "You cannot take this candle"
   state: "hot"
   value: "no"
