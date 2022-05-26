GAME START room B END room C
    intro: "Welcome!"

ROOM lab
    short desc: "Oak's lab."
    long desc: "Professor Oak's lab in Pallet Town"
    connections: NORTH TO room A
        EAST TO room C
    
    ITEM COMPUTER IN lab
    short desc: "A computer."
    long desc: "A computer in Oak's lab"

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

NPC OAK IN room B
  short desc: "Kanto’s premier Pokemon expert"
  long desc: "Enjoys exploring human-Pokemon relationships"
	age: "25"
	gender: "Male"

  INVENTORY
    item_id1: "CHARMANDER"
    item_id2: "SQUIRTLE"
    item_id3: "BULBASAUR"
    item_id4: "POKEBALL"
      
  DIALOGUE
    NODE A
        EDGE 1 TO 2 
          desc: "Good" 
        EDGE 1 TO 3 
          desc: "I have an ENCYCLOPEDIA that belongs to you."
        EDGE 1 TO 4 
          desc: "I’ve caught the PIDGEY you asked for!"
        desc: "Hello ASH. How are you?"

    NODE 2 
      desc: "Have a nice day!"
    NODE 3
        EDGE 3 TO 6.1
          desc: "I’ll take Bulbasaur."
        EDGE 3 TO 6.2
          desc: "I’ll take Squirtle"
        EDGE 3 TO 6.3
          desc: "I’ll take Charmander"
        desc: ". . . Would you like a Bulbasaur, Squirtle, or Charmander?"

    NODE 4
      desc: "Wonderful, you’re on your way . . . to complete your journey."
    NODE 6.1
      desc: "Here is your Bulbasaur. . ."
    NODE 6.2
      desc: "Here is your Squirtle. . ."
    NODE 6.3
      desc: "Here is your Charmander. . ."




