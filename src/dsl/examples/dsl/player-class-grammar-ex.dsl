# Test DSL file to test player_class grammar

# testing: game has default settings starting in room B and ending in room C
GAME START room B END room C
    intro: "Welcome!"

# testing: room B with connection to room C
ROOM room B
    short desc: "A dungeon room."
    long desc: "The walls are damp and moldy and, yet, the scent of freshly cut lavender flowers pervades the air."
    connections: "SOUTH TO room C"

# testing: room C, where the game ends.
ROOM room C
    short desc: "A Library."
    long desc: "The shelves filled with books from all over the world, containing vast amounts of knowledge"
    connections: " "

# testing: player class with id of knight. Testing if attributes and base_stats are generated correctly
PLAYER_CLASS KNIGHT
    short desc: "this a knight"
    long desc: "he is out to save the world"
    attributes: 
        noble set TRUE
    base stats: 
        health 
            CURRENT 20 
            MAX 100
