GAME START room B END room C
    intro: "Welcome!"

ROOM room B
    short desc: "A dungeon room."
    long desc: "The walls are damp and moldy and, yet, the scent of freshly
    cut lavender flowers pervades the air."
    connections: NORTH TO room A
        EAST TO room C


NPC OAK IN room B
  short desc: "Kanto's premier Pokemon expert"
  long desc: "Enjoys exploring human-Pokemon relationships"
  age: "25"
  gender: "Male"
  INVENTORY
    item_id1: "CHARMANDER"
    item_id2: "SQUIRTLE"
    item_id3: "BULBASAUR"
    item_id4: "POKEBALL"


ITEM CHARMANDER IN OAK
  short desc: "A fire pokemon"
  long desc: "Prefers hot places. When it rains, steam is said to spout from the tip of its tail." 

ITEM SQUIRTLE IN OAK
  short desc: "A water pokemon"
  long desc: "After birth, its back swells and hardens into a shell. Powerfully sprays foam from its mouth." 

ITEM BULBASAUR IN OAK
  short desc: "A grass Pokemon"
  long desc: "It can go for days without eating a single morsel. In the bulb on its back, it stores energy."

ITEM POKEBALL IN OAK
  short desc: "A pokeball"
  long desc: "A pokeball used to capture pokemon"
  actions: TAKE
    TAKE success: "You take the pokeball"
    TAKE fail: "You cannot take the pokeball"





