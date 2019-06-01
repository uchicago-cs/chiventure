#
# A two-room game. The goal is to pick up the Orb of Enlightment.
# You cannot pick it up unless you have the Talisman of Wilfrax the Wise
#

GAME:
 - start: A
 - intro: "Welcome adventurer! You find yourself in the castle of Throxar the Terrible, who has stolen the Orb of Enlightment from the Wizards' Guild. You must retrieve it!"
 - end:
   - inventory: orb

ROOMS:
 - id: A
   short_desc: "The entrance hall of the castle of Throxar the Terrible."
   long_desc: "You are surprised to see no soldiers guarding the entrance. Maybe they're taking a break?"
   connections:
    - to: B
      direction: east
      type: door
      state: open

 - id: B
   description: "A magnificent hall."
   long_desc: "Magnificent columns line the walls, which are themselves quite magnificent. The paintings on the ceiling are breathtaking and, yes, rather magnificent. Say what you will about Throxar the Terrible: he may have slaughtered entire nations, but at least he's got good taste in interior decorating."

OBJECTS:
 - id: table
   short_desc: "A table"
   long_desc: "It is rather unremarkable."
   in: A
   pickable: no

 - id: pedestal
   short_desc: "A pedestal"
   long_desc: "This is the most magnificent pedestal you have ever seen. Come to think of it, it's the first pedestal you've ever seen."
   in: B
   pickable: no

 - id: orb
   short_desc: "The Orb of Enlightment"
   long_desc: "It shines with an alluring glare. You can't believe the object of your quest is right here in the entrance hall."
   on: table
   pickable: conditional
   pick_conditions:
    - in_inventory: talisman
   pick_rejection:
    - message: "As you touch the Orb, a bolt of searing pain courses through your body. How could you have forgotten? The Wizardmaster warned you that only someone in posession of a magical artifact can pick up the Orb."

 - id: talisman
   short_desc: "The Talisman of Wilfrax the Wise"
   long_desc: "You may not know much about talismans, but you know a magical artifact when you see one."
   pickable: yes
   
