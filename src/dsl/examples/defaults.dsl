GAME START point a END point c

    ROOM point a 
        connections: NORTH TO point b 
        ITEM fork
            actions: EAT WITH, SING ABOUT

    ROOM point b
        connections: SOUTH TO point a, NORTH TO point c

    ROOM point c
        connections: SOUTH TO point b
        ITEM trophy
            actions: ADMIRE, HOIST, CELEBRATE WITH