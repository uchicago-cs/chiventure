GAME START computer lab END classroom
	Intro: “You successfully figured out how to find the DSL file that Professor Borja requested for you to find. You now have to proceed to the classroom to hand deliver the DSL file to Professor Borja. Unfortunately, you are a first-quarter student so you are unfamiliar with the layout of campus. You must now make your way through the treacherous domain that is the University of Chicago campus to find the final boss–TA Jack.”

ROOM computer lab 
    short desc: "The computer lab is located in Crerar library"
    long desc: "This is the computer lab located in Crerar Library where you have your weekly team meetings. From here you can go north to the dorm room and south to the quad."
    connections: NORTH TO dorm room
                 SOUTH TO quad

ROOM dorm room 
    short desc: "This is your dorm room"
    long desc: "This is your dorm room in Campus North Residential Commons. Room 996. From here you can head south to the computer lab.”
    connections: SOUTH TO computer lab

    ITEM desk in dorm room
       short desc: "A desk in the dorm room"
       long desc: "You can use the desk to take notes"

    action: STUDY
        STUDY success: "You successfully taken notes for CS220 class."
        STUDY fail: "You forgot your pencil. You cannot take notes."

ROOM quad
    short desc: “University of Chicago Quad."
    long desc: "This is the main quad. This is where all the main classrooms and libraries are centered on. Head west to the storage room, north to the computer lab, and south to the classroom"
    connections: WEST TO storage room
		         NORTH TO computer lab
		         SOUTH TO classroom 

    ITEM tree IN quad
        short desc: "This is Flora"
        long desc: "A tree provides great shade in the blistering Chicago summer heat, as you happily code and grind out leetcode."

    action: SIT
        SIT success: "I just finished 50 leetcode questions."
        SIT fail: "You realize you haven’t taken Algorithms and can’t do leetcode yet."

ROOM storage room
    short desc: "This is a storage room."
    long desc: "The storage room has many things in it but only one thing seems to be useful: the dsl documentation. From the storage room, head east to the quad."
    connections: EAST TO quad
                 
    ITEM dsl documentation IN storage room
        short desc: "A dsl documentation caked in dust."
        long desc: "The dsl documentation gives you everything you need to know about DSL.”
    action: CONSUME
        CONSUME success: "You are now a master at DSL like your TA Jack."
        CONSUME fail: "You did not understand the documentation at all."

ROOM classroom
    short desc: "A computer lab."
    long desc: "A computer lab with only one computer. It has been turned off."
    connections: NORTH TO quad

    ITEM computer IN computer lab
    short desc: "A computer."
    long desc: "Turn on to see the screen that shows an opened directory with multiple files opened."
    action: SUBMIT
        SUBMIT success: "You submitted your code!"
        SUBMIT fail: "You failed to submit your code in time and failed the project."

PLAYER_CLASS STUDENT
    short desc: "This is a student."
    long desc: "His goal is to get an A in Professor Borja’s class."
    ATTRIBUTES
        studious TRUE
        procrastinator FALSE
        inquisitive TRUE
    BASESTATS
        grade
	        CURRENT 80
	        MAX 100

NPC TAJACK IN classroom
    short desc: "This is TA Jack."
    long desc: "TA Jack is the best TA in the game. He is so helpful with everything and has been leading us to success. It is crazy that he is the same age as us, which really helps with his empathy for us. Specifically, his empathy in how he grades us. He knows and wants to give us all A’s in this class. His NPC age is reflective of his wisdom."
    age: "125"
    gender: "Male"
    INVENTORY
        item_id: "Google SWE Internship"
        item_id: "LARK DOCUMENTATION"
        item_id: "DSL DOCUMENTATION"
        item_id: "Omniscience"

NPC PROFESSORBORJA IN computer lab
    short desc: "This is Professor Borja Sotomayor."
    long desc: "This is the amazing professor who teaches CMSC 22000. His NPC age reflects how youthful he looks."
    age: "23"
    gender: "Male"
    INVENTORY
        item_id: "CPU"
        item_id: "Shirt Designer"
        item_id: "Glasses"
        item_id: "Power Point"
