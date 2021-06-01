# This is a dsl version of the distaff game. 


# A three-room game. The goal is to pick up the Distaff of Knowledge.
# It is inside a room with a locked door, so you must first figure out
# how to unlock the door.
#
# This file showcases a general-purpose way of specifying actions.


GAME START room B END room C
   intro: "Welcome \"adventurer\"! You have made your way to the dungeons of the Lavender Palace. Don't be fooled by the cute name! This is one of Throxar the Terrible's most fearsome strongholds... and also his best scented one. Queen Vanadia has tasked you with recovering the Distaff of Knowledge, which her spies assure you is somewhere in these dungeons."


ROOM room A
   short desc: "A dungeon room."
   long desc: "You shudder to think of the unspeakable horrors that have taken place in these dungeons. You wouldn't want to be fly on the wall here, but mostly because of how damp and moldy the walls are."
   connections: SOUTH TO room B
   extra property: "value"

   ITEM sconce
      short desc: "A sconce holding a candle"
      # intentionally bad indentation
long desc: "It looks a bit loose."

ROOM room B
   short desc: "A dungeon room."
   long desc: "The walls are damp and moldy and, yet, the scent of freshly
   cut lavender flowers pervades the air."
   connections: NORTH TO room A
                 EAST TO room C
   ITEM Door IN room B
    short desc: "A large wooden door"
    long desc: "It looks very heavy, and it doesn't have a keyhole."


ROOM room C
   short desc: "A dungeon room."
   long desc: "The walls are neither damp nor moldy. It looks like they do get around to cleaning them once in a while."
   connections: WEST TO room B

   ITEM Distaff
    short desc: "The Distaff of Knowledge"
    long desc: "The Distaff of Knowledge is an ancient magical artifact that can be used to weave knowledge itself. It will come in very handy at dinner parties."


