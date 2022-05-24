GAME START room B END room C
    intro: "Welcome!"

ROOM room B
    short desc: "A dungeon room."
    long desc: "The walls are damp and moldy and, yet, the scent of freshly
    cut lavender flowers pervades the air."
    connections: NORTH TO room A
        EAST TO room C

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
            DIALOGUE: 
                NODE 1
                    EDGE 1 TO 2 desc: “Good” 
                    EDGE 1 TO 3 desc: “I have an ENCYCLOPEDIA that belongs to you.” 	
                    EDGE 1 TO 4 desc: “I’ve caught the PIDGEY you asked for!” 
                    desc: “Hello ASH. How are you?”

                NODE 2 “Have a nice day!”
                NODE 3
                    EDGE 3 TO 6a desc: “I’ll take Bulbasaur.”
                    EDGE 3 TO 6b desc: “I’ll take Squirtle”
                    EDGE 3 TO 6c desc: “I’ll take Charmander”
                    desc: ”. . . Would you like a Bulbasaur, Squirtle, or Charmander?”

                NODE 4 desc: “ Wonderful, you’re on your way . . . to complete your journey.”
                NODE 6a desc: “Here is your Bulbasaur. . .”
                NODE 6b desc: “Here is your Squirtle. . .”
                NODE 6c desc: “Here is your Charmander. . .”


