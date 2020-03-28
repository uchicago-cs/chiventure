#
# A two-room game. The goal is to pick up the Orb of Enlightment.
# You cannot pick it up unless you have the Talisman of Wilfrax the Wise
#

GAME:
 - start: "room A"
   intro: "Welcome adventurer! You find yourself in the castle of Throxar the Terrible, who has stolen the Orb of Enlightment from the Wizards' Guild. You must retrieve it!"
   end:
    - in_room: "room B" #inventory: orb

# ROOMS:
#  - id: "room A"
#    short_desc: "The entrance hall of Throxar the Terrible's castle."
#    long_desc: "The walls are damp and moldy and, yet, the scent of freshly cut lavender flowers pervades the air."
#    connections:
#     - to: "room B"
#       direction: "EAST"
#       # through: door

#  - id: "room B"
#    short_desc: "A dungeon room."
#    long_desc: "You shudder to think of the unspeakable horrors that have taken place in these dungeons. You wouldn't want to be fly on the wall here, but mostly because of how damp and moldy the walls are."
#    connections:
#     - to: "room A"
#       direction: "WEST"

ROOMS:
 - id: "room A"
   short_desc: "The entrance hall of Throxar the Terrible's castle."
   long_desc: "You are surprised to see no soldiers guarding the entrance. Maybe they're taking a break?"
   connections:
    - to: "room B"
      direction: "EAST"
      # type: door
      # state: open

 - id: "room B"
   short_desc: "A magnificent hall."
   long_desc: "Magnificent columns line the walls, which are themselves quite magnificent. The paintings on the ceiling are breathtaking and, yes, rather magnificent. Say what you will about Throxar the Terrible: he may have slaughtered entire nations, but at least he's got good taste in interior decorating."
   connections:
    - to: "room A"
      direction: "WEST"

ITEMS:
 - id: "TABLE"
   short_desc: "A table"
   long_desc: "It is rather unremarkable."
   in: "room A"
   actions:
    - action: "PUSH"
      text_success: "You push the table."
      text_fail: "You cannot push the table"


 - id: "PEDESTAL"
   short_desc: "A pedestal"
   long_desc: "This is the most magnificent pedestal you have ever seen. Come to think of it, it's the first pedestal you've ever seen."
   in: "room B"
   actions:
    - action: "PUSH"
      text_success: "You push the pedestal."
      text_fail: "You cannot push the pedestal."


 - id: "ORB"
   short_desc: "The Orb of Enlightment"
   long_desc: "It shines with an alluring glare. You can't believe the object of your quest is right here in the entrance hall."
   in: "room A"
   actions:
    - action: "TAKE"
      text_success: "You take the Orb."
      text_fail: "As you touch the Orb, a bolt of searing pain courses through your body. How could you have forgotten? The Wizardmaster warned you that only someone in posession of a magical artifact can pick up the Orb."
  #  on: table
  #  pickable: conditional
  #  pick_conditions:
  #   - in_inventory: talisman
  #  pick_rejection:
  #   - message: "As you touch the Orb, a bolt of searing pain courses through your body. How could you have forgotten? The Wizardmaster warned you that only someone in posession of a magical artifact can pick up the Orb."

 - id: "TALISMAN"
   short_desc: "The Talisman of Wilfrax the Wise"
   long_desc: "You may not know much about talismans, but you know a magical artifact when you see one."
   in: "room B"
   actions:
    - action: "TAKE"
      text_success: "You take the Talisman."
      text_fail: "You cannot take the Talisman."
