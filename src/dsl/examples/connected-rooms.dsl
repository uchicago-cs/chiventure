GAME START room A END room C
  intro: "This is the intro"

  ROOM room A
    short desc: "This is room A"
    long desc: "This is room A. There's a chair and an exit to the south."
    connections: SOUTH TO room B

  ROOM room B
    short desc: "This is room B"
    long desc: "This is room B. There's a table and an exit to the west."
    connections: WEST TO room C

  ROOM room C
    short desc: "This is room C"
    long desc: "This is room C, the final room in the game"
    connections: NORTH TO room A

ITEM DOOR IN room A
  short desc: "A large wooden door"
  long desc: "It looks very heavy, and it doesn't have a keyhole"
  actions: OPEN, GO
    OPEN success: "You open the door."
    OPEN fail: "You can't open the door. It seems to be locked."
    GO success: "You walk through the door"
    GO fail: "You can't do that, the door is closed"
    property: "value"