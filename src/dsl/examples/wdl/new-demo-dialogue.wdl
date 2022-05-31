{
  "GAME": {
    "start": "dorm room",
    "end": {
      "in_room": "classroom"
    },
    "intro": "You successfully figured out how to find the DSL file that Professor Borja requested for you to find. You now have to proceed to the classroom to hand deliver the DSL file to Professor Borja. Unfortunately, you are a first-quarter student so you are unfamiliar with the layout of campus. You must now make your way through the treacherous domain that is the University of Chicago campus to find the final boss\u00e2\u0080\u0093TA Jack in the quad."
  },
  "CLASSES": {
    "STUDENT": {
      "short_desc": "This is a student.",
      "long_desc": "His goal is to get an A in class.",
      "attributes": {
        "studious": true,
        "procrastinator": true,
        "inquisitive": true
      },
      "base_stats": {
        "grade": {
          "current": 80,
          "max": 100
        }
      },
      "effects": null,
      "skill_tree": null,
      "starting_skills": null
    }
  },
  "ROOMS": {
    "classroom": {
      "short_desc": "A computer lab.",
      "long_desc": "A computer lab with only one computer. It has been turned off.",
      "connections": [
        {
          "direction": "NORTH",
          "to": "quad"
        }
      ],
      "items": [
        "Shirt Designer",
        "Google SWE Internship"
      ]
    },
    "storage room": {
      "short_desc": "This is a storage room.",
      "long_desc": "The storage room has many things in it but only one thing seems to be useful: the dsl documentation. From the storage room, head east to the quad.",
      "connections": [
        {
          "direction": "EAST",
          "to": "quad"
        }
      ],
      "items": []
    },
    "quad": {
      "short_desc": "University of Chicago Quad.",
      "long_desc": "This is the main quad. This is where all the main classrooms and libraries are centered on. Head west to the storage room, north to the computer lab, and south to the classroom",
      "connections": [
        {
          "direction": "WEST",
          "to": "storage room"
        },
        {
          "direction": "NORTH",
          "to": "computer lab"
        },
        {
          "direction": "SOUTH",
          "to": "classroom"
        }
      ],
      "items": []
    },
    "dorm room": {
      "short_desc": "This is your dorm room",
      "long_desc": "This is your dorm room in Campus North Residential Commons. Room 996. From here you can head south to the computer lab.",
      "connections": [
        {
          "direction": "SOUTH",
          "to": "computer lab"
        }
      ],
      "items": []
    },
    "computer lab": {
      "short_desc": "The computer lab is located in Crerar library",
      "long_desc": "This is the computer lab located in Crerar Library where you have your weekly team meetings. From here you can go north to the dorm room and south to the quad.",
      "connections": [
        {
          "direction": "NORTH",
          "to": "dorm room"
        },
        {
          "direction": "SOUTH",
          "to": "quad"
        }
      ],
      "items": []
    }
  },
  "ITEMS": {
    "GOOGLE SWE INTERNSHIP": {
      "short_desc": "The most coveted off all internships.",
      "long_desc": "Leetcode Hard questions guaranteed.",
      "actions": [
        {
          "action": "OPEN",
          "text_success": "You finish the program.",
          "text_fail": "You can't finish the program."
        },
        {
          "action": "GO",
          "text_success": "You push your code.",
          "text_fail": "You have merge conflicts"
        }
      ],
      "in": "classroom"
    },
    "SHIRT DESIGNER": {
      "short_desc": "Design Software.",
      "long_desc": "Complex SaaS company software you helped build.",
      "actions": [
        {
          "action": "OPEN",
          "text_success": "You design a sick shirt.",
          "text_fail": "You're software breaks"
        },
        {
          "action": "GO",
          "text_success": "You print out the sick shirt.",
          "text_fail": "You run out of material to print shirts."
        }
      ],
      "in": "classroom"
    }
  },
  "NPCS": {
    "BORJA": {
      "in": "computer lab",
      "short_desc": "This is Professor Borja Sotomayor.",
      "long_desc": "This is the amazing professor who teaches CMSC 22000.",
      "inventory": [
        {
          "item_id": "SHIRT DESIGNER"
        }
      ],
      "dialogue": {
            "nodes": [
                {
                    "id": "1",
                    "npc_dialogue": "Hi Student, How are you?"
                },
                {
                    "id": "2",
                    "npc_dialogue": "Have a nice day!"
                },
                {
                    "id": "3",
                    "npc_dialogue": "Oh! I already gave you the file. Go find JACK."
                }
            ],                    
            "edges": [
                {
                    "quip": "Can I have the DSL file?",
                    "from_id": "1",
                    "to_id": "3"
                }
            ]
        }
    },
    "JACK": {
      "in": "quad",
      "short_desc": "This is TA Jack.",
      "long_desc": "TA Jack is the best TA in the game. He is so helpful with everything and has been leading us to success. His NPC age is reflective of his wisdom.",
      "inventory": [
        {
          "item_id": "Google SWE Internship"
        }
      ],
      "dialogue": {
                "nodes": [
                    {
                        "id": "1",
                        "npc_dialogue": "Hi Student, How are you?"
                    },
                    {
                        "id": "2",
                        "npc_dialogue": "Have a nice day!"
                    },
                    {
                        "id": "3",
                        "npc_dialogue": "Oh! Thank you. You've completed your task. Head to finish!"
                    }
                ],                    
                "edges": [
                    {
                        "quip": "I have the DSL File Professor Borja Wanted",
                        "from_id": "1",
                        "to_id": "3"
                    }
                ]
            }
        }
    }
}