GAME START room B END room C
    intro: "Welcome!"

ROOM room B
    short desc: "A dungeon room."
    long desc: "The walls are damp and moldy and, yet, the scent of freshly
    cut lavender flowers pervades the air."
    connections: NORTH TO room A
        EAST TO room C

CLASS KNIGHT
    short desc:
    long desc:
    attributes: “noble” set TRUE
                “hot-headed” set TRUE
    base_stats: “health” CURRENT 20 MAX 100
                “mana” CURRENT 20 MAX 100
# effects: 
# skill_tree: 
# starting_skill: 

