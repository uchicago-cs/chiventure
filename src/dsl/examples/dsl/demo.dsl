# This is our standard dsl demo


# A game in a tower starting from the ground level. 
# The goal is to pick up the DSL file for Chiventure.


GAME START lobby END computer lab
  intro: "Welcome \"cs student\"! You find yourself in the lobby of an unfamiliar tower. Your CS homework is due tonight, and you need to find the DSL file before the deadline to complete the assignment. Late assignments are not accepted, so you need to go through the rooms hastily in order to get a satisfactory grade. Professor Borja has informed you that the DSL file is within one of the rooms near the top of the tower. Good luck on your search!"

ROOM lobby 
    short desc: "The main lobby in this tower."
    long desc: "Start your search here. Go up to the kitchen. Go south to the bathroom."
    connections: SOUTH TO bathroom
                 UP TO kitchen

ROOM bathroom 
    short desc: "This is the bathroom"
    long desc: "The toilet is broken. You can only use the faucet to wash your hands in this bathroom."
    connections: NORTH TO lobby

    ITEM faucet
       short desc: "A faucet in the bathroom"
       long desc: "Use the faucet to wash your hands"

    action: CONSUME
        CONSUME success: "Your hands are clean."
        CONSUME fail: "You broke the faucet. You cannot wash your hands"

ROOM kitchen
    short desc: "A kitchen."
    long desc: "This is a kitchen south of the movie theatre. You can go up to the storage room from here. There are some apples in the kitchen; they look delicious."
    connections: UP TO storage room
		         NORTH TO movie theatre
		         DOWN TO lobby

    ITEM apples IN kitchen 
      short desc: "Some fresh apples"
      long desc: "An apple a day keeps the doctor away. You can eat the apples if you want."

    action: CONSUME
      CONSUME success: "Those were some delicious apples."
      CONSUME fail: "You realize you’re not hungry and do not want to eat anything."

ROOM movie theatre
    short desc: "A small movie theatre."
    long desc: "There's something playing on the screen. You can't see from this far away, but you don't care because you're running out of time. Go back to the kitchen."
    connections: SOUTH TO kitchen

ROOM storage room
    short desc: "A storage room."
    long desc: "There are various items, including a toolbox, all caked with dust. The door on the west is locked but looks like the lock can be picked."
    connections: WEST TO computer lab
                 DOWN TO kitchen

    ITEM toolbox IN storage room
        short desc: "A toolbox caked in dust."
        long desc: "The toolbox contains a very rusty hammer and screwdriver. There are a lot of tools missing."
    action: CONSUME
        CONSUME success: "The screwdriver looks like a good tool to pick the lock with."
        CONSUME fail: "You can't pick it up."

ROOM computer lab
   short desc: "A computer lab."
   long desc: "A computer lab with only one computer. It has been turned off."
   connections: EAST TO storage room

   ITEM computer IN computer lab
    short desc: "A computer."
    long desc: "Turn on to see the screen that shows an opened directory with multiple files opened."
   action: TURNON
    TURNON success: "You found the DSL file!"
    TURNON fail: "You’re not interested in the contents of the files. It looks boring anyways."