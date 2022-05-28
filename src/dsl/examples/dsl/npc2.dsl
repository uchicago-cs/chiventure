GAME START lab END room other
    intro: "Welcome!"

ROOM lab
    short desc: "Oak's lab."
    long desc: "Professor Oak's lab in Pallet Town"
    connections: EAST TO house
    
    ITEM COMPUTER IN lab
    short desc: "A computer."
    long desc: "A computer in Oak's lab"

ROOM gym
    short desc: "Brock's Gym"
    long desc: "Gym Leader Brock's gym in Pewter City"
    connections: SOUTH TO house

ROOM house
    short desc: "Oak's house."
    long desc: "Professor Oak's house in Pallet Town"
    connections: NORTH TO gym
        WEST TO lab
    

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

NPC OAK IN lab
  short desc: "Kanto's premier Pokemon expert"
  long desc: "Enjoys exploring human-Pokemon relationships"
  age: "80"
  gender: "Male"
  INVENTORY
    item_id1: "CHARMANDER"
    item_id2: "SQUIRTLE"
    item_id3: "BULBASAUR"
    item_id4: "POKEBALL"

NPC ASH IN other
  short desc: "Pokemon Master"
  long desc: "ASH Ketchum is THE Pokemon Master"
  age: "10"
  gender: "Male"

NPC RED IN house
  short desc: "Original player"
  long desc: "Strongest pokemon player of all time"
  age: "25"
  gender: "Male"




