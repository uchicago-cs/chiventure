# This is our standard dsl demo


# A game in a tower starting from the ground level. 
# The goal is to pick up the DSL file for Chiventure.
# You are currently inside a room with a locked door, so you must first figure out
# how to unlock the door first. 
#
# This file showcases a general-purpose way of specifying actions.


GAME START lobby END computer lab
intro: "Welcome \"cs student\"! You find yourself in the lobby of an unfamiliar tower. Your CS homework is due tonight, and you need to find the DSL file before the deadline to complete the assignment. Late assignments are not accepted, so you need to go through the rooms hastily in order to get a satisfactory grade. Professor Borja has informed you that the DSL file is within one of the rooms near the top of the tower. Good luck on your search!”


ROOM lobby 
    short desc: "The main lobby in this tower."
    long desc: "You look around, but you can’t see anything. The lobby is dark, so you must find a way to light up the room and get out of the lobby in order to find your DSL file."
    connections: SOUTH TO bathroom
  UP TO kitchen

    ITEM candle IN lobby
        short desc: "A candle"
        long desc: "It has not been lit up"

   ITEM match 
        short desc: "A match"
        long desc: "You can use it to light up the candle"
   action: LIGHT CANDLE
        LIGHT CANDLE success: "You light the candle."
        LIGHT CANDLE fail: "You broke the match. Now you have to go on without a light source."

ROOM bathroom 
    short desc: "This is the bathroom"
    long desc: "The toilet is broken. You can only wash your hands in this bathroom"
    connections: NORTH TO lobby
    action: WASH
        WASH success: "Your hands are clean."
        WASH fail: "You broke the faucet. You cannot wash your hands"
ROOM kitchen
    short desc: "A kitchen."
    long desc: "The dishes are piled up in the sink, still yet to be washed. The kitchen reeks of rotten food, and you can see rodents scurrying across the floor."
    connections: UP TO storage room
		  NORTH TO movie theatre
		  DOWN TO lobby

   ITEM dishes 
      short desc: "Dirty dishes"
      long desc: "You can wash the dishes for us."
    action: WASH
      WASH success: "Thank you for washing the dishes."
      WASH fail: "There’s no dish soap; you cannot wash the dishes"

   ITEM apples IN kitchen 
      short desc: "Some fresh apples"
      long desc: "An apple a day keeps the doctor away. You can eat the apples if you want”
    action: EAT
      EAT success: "Those were some delicious apples."
      EAT fail: "You realize you’re not hungry and do not want to eat anything."
      
ROOM movie theatre
    short desc: “A small movie theatre.”
    long desc: “There’s something playing on the screen. You can’t see from this far away, so you may need to go closer.”
    connections: SOUTH TO kitchen
    
    action: GO CLOSER
        GO CLOSER success: “You take a couple strides to the front. You can see that a film is being played over and over again that says “The 3rd floor has the key”.”
        GO CLOSER fail: “You stay where you are.”
		  
ROOM storage room
    short desc: “A storage room.”
    long desc: “There are various items, including a toolbox, all caked with dust. The door on the west is locked but looks like the lock can be picked.”
    connections: WEST TO computer lab
    
    ITEM toolbox IN storage room
        short desc: “A toolbox caked in dust.”
        long desc: “The toolbox contains a very rusty hammer and screwdriver. There are a lot of tools missing.”
        action: TAKE SCREWDRIVER, TAKE HAMMER
            TAKE SCREWDRIVER success: “The screwdriver looks like a good tool to pick the lock with”
            TAKE SCREWDRIVER fail: “You can’t pick it up.”
            TAKE HAMMER success: “The hammer is picked up. It doesn’t look like a good lock-picking tool.”
            TAKE HAMMER fail: “You can’t pick it up.”

ROOM computer lab
   short desc: "A computer lab."
   long desc: "A computer lab with a row of computers that are all turned off except the last one on the right.

   
   It seems like someone was here recently."
   connections: EAST TO storage room

   ITEM computer IN computer lab
    short desc: “A computer that is turned on.”
    long desc: “The screen shows an opened directory with multiple files opened.”
   action: READ, CHECK PORT
    READ success: “The folder that is opened is called “DSL”. Among the files opened, there is a standard-demo.dsl file that includes all the code needed for the homework. It seems like the files have been loaded on through a device in the port”
    READ fail: “You’re not interested in the contents of the files. It looks boring anyways.”
    CHECK PORT success: “You realize that there is a USB plugged in. You take the USB that contains the files needed for the assignment.”
    CHECK PORT fail: “It doesn’t matter to you where the file is stored. You’ve come to terms with failing the assignment.”

   ITEM usb IN computer lab
    short desc: "A usb containing a DSL file"
    long desc: "It was still plugged in the monitor, and it seems like someone has edited the file recently."
