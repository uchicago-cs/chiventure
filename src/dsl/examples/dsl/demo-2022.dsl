GAME START dorm room END classroom
	intro: "You successfully figured out how to find the DSL file that Professor Borja requested for you to find. You now have to proceed to the classroom to hand deliver the DSL file to Professor Borja. Unfortunately, you are a first-quarter student so you are unfamiliar with the layout of campus. You must now make your way through the treacherous domain that is the University of Chicago campus to find the final boss–TA Jack in the quad."

ROOM computer lab 
    short desc: "The computer lab is located in Crerar library"
    long desc: "This is the computer lab located in Crerar Library where you have your weekly team meetings. From here you can go north to the dorm room and south to the quad."
    connections: NORTH TO dorm room
                 SOUTH TO quad

ROOM dorm room 
    short desc: "This is your dorm room"
    long desc: "This is your dorm room in Campus North Residential Commons. Room 996. From here you can head south to the computer lab."
    connections: SOUTH TO computer lab

ROOM quad
    short desc: "University of Chicago Quad."
    long desc: "This is the main quad. This is where all the main classrooms and libraries are centered on. Head west to the storage room, north to the computer lab, and south to the classroom"
    connections: WEST TO storage room
		         NORTH TO computer lab
		         SOUTH TO classroom 


ROOM storage room
    short desc: "This is a storage room."
    long desc: "The storage room has many things in it but only one thing seems to be useful: the dsl documentation. From the storage room, head east to the quad."
    connections: EAST TO quad

ROOM classroom
    short desc: "A computer lab."
    long desc: "A computer lab with only one computer. It has been turned off."
    connections: NORTH TO quad

ITEM Shirt Designer
  short desc: "Design Software."
  long desc: "Complex SaaS company software you helped build."
  actions: OPEN, GO
    OPEN success: "You design a sick shirt."
    OPEN fail: "You're software breaks"
    GO success: "You print out the sick shirt."
    GO fail: "You run out of material to print shirts."

ITEM Google SWE Internship
  short desc: "The most coveted off all internships."
  long desc: "Leetcode Hard questions guaranteed."
  actions: OPEN, GO
    OPEN success: "You finish the program."
    OPEN fail: "You can't finish the program."
    GO success: "You push your code."
    GO fail: "You have merge conflicts"


NPC JACK IN quad
    short desc: "This is TA Jack."
    long desc: "TA Jack is the best TA in the game. He is so helpful with everything and has been leading us to success. His NPC age is reflective of his wisdom."
    INVENTORY
        item_id1: "Google SWE Internship"

NPC BORJA IN computer lab
    short desc: "This is Professor Borja Sotomayor."
    long desc: "This is the amazing professor who teaches CMSC 22000."
    INVENTORY
        item_id1: "SHIRT DESIGNER"

PLAYER_CLASS STUDENT
    short desc: "This is a student."
    long desc: "His goal is to get an A in class."
    ATTRIBUTES
        studious TRUE
        procrastinator FALSE
        inquisitive TRUE
    BASESTATS
        grade
	        CURRENT 80
	        MAX 100
    effects: null
    skill_tree: null
    starting_skills: null
