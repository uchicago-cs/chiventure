# This is our standard dsl demo


# A game in a tower starting from the ground level. 
# The goal is to pick up the DSL file for Chiventure.
# You are currently inside a room with a locked door, so you must first figure out
# how to unlock the door first. 


GAME START lobby END computer lab
  intro: "Welcome \"cs student\"! You find yourself in the lobby of an unfamiliar tower. Your CS homework is due tonight, and you need to find the DSL file before the deadline to complete the assignment. Late assignments are not accepted, so you need to go through the rooms hastily in order to get a satisfactory grade. Professor Borja has informed you that the DSL file is within one of the rooms near the top of the tower. Good luck on your search!"

ROOM lobby 
    short desc: "The main lobby in this tower."
    long desc: "You look around, but you can't see anything. The lobby is dark, so you must find a way to light up the room and get out of the lobby in order to find your DSL file. There is a candle!"
    connections: SOUTH TO bathroom
                 UP TO kitchen

    ITEM candle IN lobby
        short desc: "A candle"
        long desc: "It has not been lit up"

   action: TAKE
        TAKE success: "You light the candle."
        TAKE fail: "You broke the candle. Now you have to go on without a light source."

ROOM bathroom 
    short desc: "This is the bathroom"
    long desc: "The toilet is broken. You can only wash your hands in this bathroom"
    connections: NORTH TO lobby

    ITEM faucet
       short desc: "A faucet in the bathroom"
       long desc: "Use the faucet to wash your hands"

    action: USE
        USE success: "Your hands are clean."
        USE fail: "You broke the faucet. You cannot wash your hands"

ROOM kitchen
    short desc: "A kitchen."
    long desc: "The dishes are piled up in the sink, still yet to be washed. The kitchen reeks of rotten food, and you can see rodents scurrying across the floor."
    connections: UP TO storage room
		             NORTH TO movie theatre
		             DOWN TO lobby

    ITEM apples IN kitchen 
      short desc: "Some fresh apples"
      long desc: "An apple a day keeps the doctor away. You can eat the apples if you want."

    action: EAT
      EAT success: "Those were some delicious apples."
      EAT fail: "You realize you’re not hungry and do not want to eat anything."

ROOM movie theatre
    short desc: "A small movie theatre."
    long desc: "There’s something playing on the screen. You can’t see from this far away, but you don't care because you're running out of time. Go back to the kitchen."
    connections: SOUTH TO kitchen

ROOM storage room
    short desc: "A storage room."
    long desc: "There are various items, including a toolbox, all caked with dust. The door on the west is locked but looks like the lock can be picked."
    connections: WEST TO computer lab

    ITEM toolbox IN storage room
        short desc: "A toolbox caked in dust."
        long desc: "The toolbox contains a very rusty hammer and screwdriver. There are a lot of tools missing."
    action: USE
        USE success: "The screwdriver looks like a good tool to pick the lock with."
        USE fail: "You can’t pick it up."

ROOM computer lab
   short desc: "A computer lab."
   long desc: "A computer lab with a row of computers that are all turned off except the last one on the right. It seems like someone was here recently."
   connections: EAST TO storage room

   ITEM computer IN computer lab
    short desc: "A computer."
    long desc: "Turn on to see the screen that shows an opened directory with multiple files opened."
   action: TURNON
    TURNON success: "The folder that is opened is called “DSL”. Among the files opened, there is a standard-demo.dsl file that includes all the code needed for the homework. It seems like the files have been loaded on through a device in the port"
    TURNON fail: "You’re not interested in the contents of the files. It looks boring anyways."
    

   ITEM usb IN computer lab
    short desc: "A usb containing a DSL file"
    long desc: "It was still plugged in the monitor, and it seems like someone has edited the file recently. Congrats! You found the DSL file!"















