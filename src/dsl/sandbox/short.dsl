GAME START room B END room C
   intro: "Welcome!"


ROOM room B
   short desc: "A dungeon room."
   ITEM Door IN room B
    short desc: "A large wooden door"
    action: OPEN
      OPEN condition: "Door is in front of you."
		OPEN success: "You open the door."
      OPEN fail: "You can't open the door."
   action: BREAK
      OPEN condition: "Door is in front of you."
		OPEN success: "You break the door."
      OPEN fail: "You can't break the door."