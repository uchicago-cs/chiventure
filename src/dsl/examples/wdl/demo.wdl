{
  "GAME": {
    "start": "lobby",
    "end": {
      "in_room": "computer lab"
    },
    "intro": "Welcome \"cs student\"! You find yourself in the lobby of an unfamiliar tower. Your CS homework is due tonight, and you need to find the DSL file before the deadline to complete the assignment. Late assignments are not accepted, so you need to go through the rooms hastily in order to get a satisfactory grade. Professor Borja has informed you that the DSL file is within one of the rooms near the top of the tower. Good luck on your search!"
  },
  "ROOMS": {
    "computer lab": {
      "short_desc": "A computer lab.",
      "long_desc": "A computer lab with only one computer. It has been turned off.",
      "connections": [
        {
          "direction": "EAST",
          "to": "storage room"
        }
      ],
      "items": [
        "computer"
      ]
    },
    "storage room": {
      "short_desc": "A storage room.",
      "long_desc": "There are various items, including a toolbox, all caked with dust. The door on the west is locked but looks like the lock can be picked.",
      "connections": [
        {
          "direction": "WEST",
          "to": "computer lab"
        },
        {
          "direction": "DOWN",
          "to": "kitchen"
        }
      ],
      "items": [
        "toolbox"
      ]
    },
    "movie theatre": {
      "short_desc": "A small movie theatre.",
      "long_desc": "There's something playing on the screen. You can't see from this far away, but you don't care because you're running out of time. Go back to the kitchen.",
      "connections": [
        {
          "direction": "SOUTH",
          "to": "kitchen"
        }
      ],
      "items": []
    },
    "kitchen": {
      "short_desc": "A kitchen.",
      "long_desc": "This is a kitchen south of the movie theatre. You can go up to the storage room from here. There are some apples in the kitchen; they look delicious.",
      "connections": [
        {
          "direction": "UP",
          "to": "storage room"
        },
        {
          "direction": "NORTH",
          "to": "movie theatre"
        },
        {
          "direction": "DOWN",
          "to": "lobby"
        }
      ],
      "items": [
        "apples"
      ]
    },
    "bathroom": {
      "short_desc": "This is the bathroom",
      "long_desc": "The toilet is broken. You can only use the faucet to wash your hands in this bathroom.",
      "connections": [
        {
          "direction": "NORTH",
          "to": "lobby"
        }
      ],
      "items": [
        "faucet"
      ]
    },
    "lobby": {
      "short_desc": "The main lobby in this tower.",
      "long_desc": "Start your search here. Go up to the kitchen. Go south to the bathroom.",
      "connections": [
        {
          "direction": "SOUTH",
          "to": "bathroom"
        },
        {
          "direction": "UP",
          "to": "kitchen"
        }
      ],
      "items": []
    }
  },
  "ITEMS": {
    "COMPUTER": {
      "short_desc": "A computer.",
      "long_desc": "Turn on to see the screen that shows an opened directory with multiple files opened.",
      "actions": [
        {
          "action": "TURNON",
          "text_success": "You found the DSL file!",
          "text_fail": "You\u00e2\u0080\u0099re not interested in the contents of the files. It looks boring anyways."
        }
      ],
      "in": "computer lab"
    },
    "TOOLBOX": {
      "short_desc": "A toolbox caked in dust.",
      "long_desc": "The toolbox contains a very rusty hammer and screwdriver. There are a lot of tools missing.",
      "actions": [
        {
          "action": "CONSUME",
          "text_success": "The screwdriver looks like a good tool to pick the lock with.",
          "text_fail": "You can't pick it up."
        }
      ],
      "in": "storage room"
    },
    "APPLES": {
      "short_desc": "Some fresh apples",
      "long_desc": "An apple a day keeps the doctor away. You can eat the apples if you want.",
      "actions": [
        {
          "action": "CONSUME",
          "text_success": "Those were some delicious apples.",
          "text_fail": "You realize you\u00e2\u0080\u0099re not hungry and do not want to eat anything."
        }
      ],
      "in": "kitchen"
    },
    "FAUCET": {
      "short_desc": "A faucet in the bathroom",
      "long_desc": "Use the faucet to wash your hands",
      "actions": [
        {
          "action": "CONSUME",
          "text_success": "Your hands are clean.",
          "text_fail": "You broke the faucet. You cannot wash your hands"
        }
      ],
      "in": "bathroom"
    }
  }
}