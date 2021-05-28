# Test DSL file to emphasize functionality of intermediate-to-WDL phase

# testing: game ends in unattainable (nonexistent) location
GAME START alcatraz cell END san francisco
   intro: "It's dusk in San Francisco, but not the cool part of the city. You're on an island with views of the Bay, which would be dope if the island didn't have a prison on top of it that you lived in. For what seems like the millionth time, you stare out into the distance, the faint light of the neon sign from the world-famous Ghirardelli factory — yet another place you can't go — shining through your tiny barred window. You resolve to get yourself out of here, as soon as possible."

# testing: generating room long description by default, connections to nonexistent rooms
ROOM alcatraz cell
    short desc: "You're in a prison cell."
    connections: SOUTH TO secret tunnel, NORTH TO prison hallway

    # testing: Unicode characters (suits), declaring item within room, 'failure' synonym for 'fail'
    ITEM deck of cards
        long desc: "You have a deck of cards. It's a full deck, if you're willing to forget the fact that it was missing the 7♣ when you got it and also that your former cellmate tore the J♦ in half as part of a 'magic trick' that didn't work at all."
        actions: SHUFFLE
            SHUFFLE success: "You shuffle the cards."
            SHUFFLE failure: "You fail to shuffle the cards! They spectacularly spray all over your cell, and what's worse, the K♠ landed in your neighbor's cell. You are no longer able to maintain the lie you've told yourself that your deck of cards is perfectly good. It's not — it's ruined. You can't have good things, it seems."

# testing: actions without success or fail parameters, generating item short description by default
ITEM toilet IN alcatraz cell
    long desc: "Your cell's got a toilet. It's the first thing you see when you wake up every day and the last thing you see each night. Nobody inside likes you all that much, so you figue the toilet's gotta be your best friend in all this world. A few years ago, you decided to name it Barbara, and you've grown attatched to the name."
    actions: LIFT, FLUSH, SING ABOUT
        LIFT success: "You lift the toilet."
        LIFT fail: "The toilet is too heavy for you to lift!"
        FLUSH success: "You flush the toilet."
        FLUSH fail: "You can't flush the toilet! It's quiet hour, idiot."
    
# testing: generating room short description by default, 'long description' synonym
ROOM prison hallway
    long description: "The prison hallway is dark and foreboding, but hell, you knew that already, you live here. Honestly, you're kind of a fan of Hallway B (that's its official name): even though it's dark and brutalist and home to a rat colony, it isn't Hallway C. Everyone knows Hallway C is haunted, and you'd sooner die than have to live there. Not that it matters, rumor has it, if you move there you'll be dead within a week. Or was it 'undead'? Nevermind, that seems like an unimportant distinction. You don't have time to contemplate it. You're in Hallway B after hours, without permission. Better keep both eyes open."

                                        # testing: generating both item descriptions by default, screwy indentation and line breaks
                                        ITEM guard badge IN prison hallway
                                            actions: THROW LIKE FRISBEE




                                            
                                                THROW LIKE FRISBEE success: "You throw the guard badge across the room like a Frisbee."
                                                THROW LIKE FRISBEE fail: "You try to throw the guard badge across the room like a Frisbee, but you realize you can't. You've never seen a Frisbee in your life; you've only read about them. You think they were invented after you got locked up here, but you don't know that for sure."