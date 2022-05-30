# Test DSL file to test player_class grammar

GAME START room B END room C
   intro: "Welcome!"

ROOM room B
    short desc: "A dungeon room."
    connections: WEST TO room C
    ITEM DOOR IN room B
        short desc: "A large wooden door"
        action: OPEN, BREAK
            OPEN condition: "Door is in front of you."
	        OPEN success: "You open the door."
            OPEN fail: "You can't open the door."
            BREAK condition: "Door is in front of you."
		    BREAK success: "You break the door."
            BREAK fail: "You can't break the door."

ROOM room C
    short desc: "library room."
    connections: EAST TO room B
    

# testing: player class with id of knight. Testing if attributes and base_stats are generated correctly
PLAYER_CLASS Knight
    short desc: "Knight's short description"
    long desc: "Knight's long description"
    ATTRIBUTES 
        noble TRUE
        hotheaded TRUE
    BASESTATS
        health 
            CURRENT 100
            MAX 200
        mana
            CURRENT 20
            MAX 100
    effects: null
    skill_tree: null
    starting_skills: null