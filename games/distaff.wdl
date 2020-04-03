# A three-room game. The goal is to pick up the Distaff of Knowledge.
# It is inside a room with a locked door, so you must first figure out
# how to unlock the door.
#
# This file showcases a general-purpose way of specifying actions.

GAME:
 - start: "room B"
   intro: "Welcome adventurer! You have made your way to the dungeons of the Lavender Palace. Don't be fooled by the cute name! This is one of Throxar the Terrible's most fearsome strongholds... and also his best scented one. Queen Vanadia has tasked you with recovering the Distaff of Knowledge, which her spies assure you is somewhere in these dungeons."
   end:
    - in_room: "room C"
  #  - inventory: "distaff"

ROOMS:
 - id: "room B"
   short_desc: "A dungeon room."
   long_desc: "The walls are damp and moldy and, yet, the scent of freshly cut lavender flowers pervades the air."
   connections:
    - to: "room A"
      direction: "NORTH"
    - to: "room C"
      direction: "EAST"
      # through: door

 - id: "room A"
   short_desc: "A dungeon room."
   long_desc: "You shudder to think of the unspeakable horrors that have taken place in these dungeons. You wouldn't want to be fly on the wall here, but mostly because of how damp and moldy the walls are."
   connections:
    - to: "room B"
      direction: "SOUTH"

 - id: "room C"
   short_desc: "A dungeon room."
   long_desc: "The walls are neither damp nor moldy. It looks like they do get around to cleaning them once in a while."
   connections:
    - to: "room B"
      direction: "WEST"

ITEMS:
  - id: "DOOR"
    short_desc: "A large wooden door"
    long_desc: "It looks very heavy, and it doesn't have a keyhole."
    in: "room B"
    # locked: yes
    # open: no
    actions:
      - action: "OPEN"
        text_success: "You open the door."
        text_fail: "You can't open the door. It seems to be locked."
      - action: "GO"
        text_success: "You walk through the door."
        text_fail: "You can't do that, the door is closed."
      # - open:
      #     - conditions:
      #        - locked: no
      #     - text_fail: "You can't open the door. It seems to be locked."
      #     - text_success: "You open the door."
      # - walk:
      #     - conditions:
      #         - open: yes
      #     - text_fail: "You can't do that, the door is closed."

  - id: "SCONCE"
    short_desc: "A sconce holding a candle"
    long_desc: "It looks a bit loose."
    in: "room A"
    # pulled: no
    actions:
      - action: "TAKE"
          # - allowed: no
          text_success: "You take the sconce."
          text_fail: "You can't do that. The sconce is loose, but still firmly attached to the wall."
      - action: "PULL"
          # - conditions:
          #     - pulled: no
          # - set:
          #     - object: door
          #       attribute: locked
          #       value: no
          #     - object: sconce
          #       attribute: pulled
          #       value: yes
          text_success: "You pull on the sconce. You hear the sound of a door unlocking in a nearby room."
          text_fail: "Pulling on the sconce again doesn't seem to do anything."

 - id: "DISTAFF"
   short_desc: "The Distaff of Knowledge"
   long_desc: "The Distaff of Knowledge is an ancient magical artifact that can be used to weave knowledge itself. It will come in very handy at dinner parties."
   in: "room C"
   actions:
    - action: "TAKE"
      text_success: "You take the distaff."
      text_fail: "You cannot take the distaff."
  

