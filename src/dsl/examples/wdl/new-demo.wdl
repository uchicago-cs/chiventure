{
  "GAME": {
    "start": "computer lab",
    "end": {
      "in_room": "classroom"
    },
    "intro": "You successfully figured out how to find the DSL file that Professor Borja requested for you to find. You now have to proceed to the classroom to hand deliver the DSL file to Professor Borja. Unfortunately, you are a first-quarter student so you are unfamiliar with the layout of campus. You must now make your way through the treacherous domain that is the University of Chicago campus to find the final boss\u00e2\u0080\u0093TA Jack."
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
        "computer"
      ],
      "npcs": []
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
      "items": [
        "dsl documentation"
      ],
      "npcs": []
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
      "items": [
        "tree"
      ],
      "npcs": []
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
      "items": [
        "desk"
      ],
      "npcs": []
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
      "items": [],
      "npcs": []
    }
  },
  "ITEMS": {
    "COMPUTER": {
      "short_desc": "A computer.",
      "long_desc": "Turn on to see the screen that shows an opened directory with multiple files opened.",
      "actions": [
        {
          "action": "SUBMIT",
          "text_success": "You submitted your code!",
          "text_fail": "You failed to submit your code in time and failed the project."
        }
      ],
      "in": "computer lab"
    },
    "DSL DOCUMENTATION": {
      "short_desc": "A dsl documentation caked in dust.",
      "long_desc": "The dsl documentation gives you everything you need to know about DSL.",
      "actions": [
        {
          "action": "CONSUME",
          "text_success": "You are now a master at DSL like your TA Jack.",
          "text_fail": "You did not understand the documentation at all."
        }
      ],
      "in": "storage room"
    },
    "TREE": {
      "short_desc": "This is Flora",
      "long_desc": "A tree provides great shade in the blistering Chicago summer heat, as you happily code and grind out leetcode.",
      "actions": [
        {
          "action": "SIT",
          "text_success": "I just finished 50 leetcode questions.",
          "text_fail": "You realize you haven\u00e2\u0080\u0099t taken Algorithms and can\u00e2\u0080\u0099t do leetcode yet."
        }
      ],
      "in": "quad"
    },
    "DESK": {
      "short_desc": "A desk in the dorm room",
      "long_desc": "You can use the desk to take notes",
      "actions": [
        {
          "action": "STUDY",
          "text_success": "You successfully taken notes for CS220 class.",
          "text_fail": "You forgot your pencil. You cannot take notes."
        }
      ],
      "in": "dorm room"
    }
  },
  "PLAYERS": {
    "STUDENT": {
      "short desc": "STUDENT",
      "long desc": "This is a STUDENT.",
      "short_desc": "This is a student.",
      "long_desc": "His goal is to get an A in Professor Borja\u00e2\u0080\u0099s class.",
      "attributes": {
        "studious": "TRUE",
        "procrastinator": "FALSE",
        "inquisitive": "TRUE"
      },
      "base_stats": {
        "stat_setting": {
          "id": "grade",
          "state": {
            "CURRENT": "80",
            "MAX": "10"
          }
        }
      }
    }
  },
  "NPCS": {
    "BORJA": {
      "location": "computer lab",
      "short_desc": "This is Professor Borja Sotomayor.",
      "long_desc": "This is the amazing professor who teaches CMSC 22000.",
      "age": "23",
      "gender": "Male",
      "INVENTORY": {
        "item_id1": "CPU",
        "item_id2": "Shirt Designer",
        "item_id3": "Glasses",
        "item_id4": "Power Point"
      }
    },
    "JACK": {
      "location": "classroom",
      "short_desc": "This is TA Jack.",
      "long_desc": "TA Jack is the best TA in the game. He is so helpful with everything and has been leading us to success. His NPC age is reflective of his wisdom.",
      "age": "125",
      "gender": "Male",
      "INVENTORY": {
        "item_id1": "Google SWE Internship",
        "item_id2": "LARK DOCUMENTATION",
        "item_id3": "DSL DOCUMENTATION",
        "item_id4": "Omniscience"
      }
    }
  }
}