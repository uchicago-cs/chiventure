GAME START room B END room C
    intro: "Welcome!"

ROOM room B
    short desc: "A dungeon room."
    long desc: "The walls are damp and moldy and, yet, the scent of freshly
    cut lavender flowers pervades the air."
    connections: NORTH TO room A
        EAST TO room C

PLAYER_CLASS Knight
    short desc: "short desc"
    long desc: "long desc"
    attributes: noble, hot-headed
    stats:
        health: 
            current: 20
            max: 100
        mana:
            current: 20
            max: 100

PLAYER_CLASS Bishop
    short desc: "Bishop"
    long desc: "This is a bishop"
    attributes: noble, hot-headed
    stats:
        health: 
            current: 20
            max: 100
        mana:
            current: 20
            max: 100

