{
  "GAME": {
    "start": "lab",
    "end": {
      "in_room": "room other"
    },
    "intro": "Welcome!"
  },
  "ROOMS": {
    "house": {
      "short_desc": "Oak's house.",
      "long_desc": "Professor Oak's house in Pallet Town",
      "connections": [
        {
          "direction": "NORTH",
          "to": "gym"
        },
        {
          "direction": "WEST",
          "to": "lab"
        }
      ],
      "items": [
        "CHARMANDER",
        "SQUIRTLE",
        "BULBASAUR",
        "POKEBALL"
      ],
      "npcs": []
    },
    "gym": {
      "short_desc": "Brock's Gym",
      "long_desc": "Gym Leader Brock's gym in Pewter City",
      "connections": [
        {
          "direction": "SOUTH",
          "to": "house"
        }
      ],
      "items": [],
      "npcs": []
    },
    "lab": {
      "short_desc": "Oak's lab.",
      "long_desc": "Professor Oak's lab in Pallet Town",
      "connections": [
        {
          "direction": "EAST",
          "to": "house"
        }
      ],
      "items": [
        "COMPUTER"
      ],
      "npcs": []
    }
  },
  "ITEMS": {
    "POKEBALL": {
      "short_desc": "A pokeball",
      "long_desc": "A pokeball used to capture pokemon",
      "actions": [
        {
          "action": "TAKE",
          "text_success": "You take the pokeball",
          "text_fail": "You cannot take the pokeball"
        }
      ],
      "in": "OAK"
    },
    "BULBASAUR": {
      "short_desc": "A grass Pokemon",
      "long_desc": "It can go for days without eating a single morsel. In the bulb on its back, it stores energy.",
      "in": "OAK",
      "actions": []
    },
    "SQUIRTLE": {
      "short_desc": "A water pokemon",
      "long_desc": "After birth, its back swells and hardens into a shell. Powerfully sprays foam from its mouth.",
      "in": "OAK",
      "actions": []
    },
    "CHARMANDER": {
      "short_desc": "A fire pokemon",
      "long_desc": "Prefers hot places. When it rains, steam is said to spout from the tip of its tail.",
      "in": "OAK",
      "actions": []
    },
    "COMPUTER": {
      "short_desc": "A computer.",
      "long_desc": "A computer in Oak's lab",
      "in": "lab",
      "actions": []
    }
  },
  "NPCS": {
    "RED": {
      "location": "house",
      "short_desc": "Original player",
      "long_desc": "Strongest pokemon player of all time",
      "age": "25",
      "gender": "Male"
    },
    "ASH": {
      "location": "other",
      "short_desc": "Pokemon Master",
      "long_desc": "ASH Ketchum is THE Pokemon Master",
      "age": "10",
      "gender": "Male"
    },
    "OAK": {
      "location": "lab",
      "short_desc": "Kanto's premier Pokemon expert",
      "long_desc": "Enjoys exploring human-Pokemon relationships",
      "age": "80",
      "gender": "Male",
      "INVENTORY": {
        "item_id1": "CHARMANDER",
        "item_id2": "SQUIRTLE",
        "item_id3": "BULBASAUR",
        "item_id4": "POKEBALL"
      }
    }
  }
}