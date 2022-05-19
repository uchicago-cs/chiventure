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
        item_id: CHARMANDER
        item_id: SQUIRTLE
        item_id: BULBASAUR
        item_id: POKEBALL

