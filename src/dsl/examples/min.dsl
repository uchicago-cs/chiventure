GAME START room A END room C

ROOM room A
  connections: SOUTH TO room B, EAST TO room C
  ITEM item_A
  ITEM item_B
    actions: OPEN,CLOSE

ROOM room B
  connections: SOUTH TO room A, EAST TO room C
  ITEM item_B
    action: OPEN, CLOSE

ROOM room C
  connections: NORTH TO room A